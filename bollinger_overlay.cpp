#include "bollinger_overlay.h"

#include <QGraphicsScene>
#include <QDateTime>
#include <QPainter>
#include <QDebug>

#include "ohlc_provider.h"

// N-period moving average
// upper: MA + K\sigma (smerodatna odchylka)
// lower: MA - K\sigma (smerodatna odchylka)

BollingerOverlay::BollingerOverlay(int N, int K) {
	this->N = N;
	this->K = K;
}

void BollingerOverlay::timeAxisChanged(TimeAxis timeAxis) {
	axisPair.timeAxis = timeAxis;
}

void BollingerOverlay::numberAxisChanged(NumberAxis numberAxis) {
	axisPair.numberAxis = numberAxis;
}

void BollingerOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

void BollingerOverlay::insertIntoScene(QGraphicsScene* scene) {
	qDebug() << "Rendering bollinger overlay";

	Band* item = new Band(axisPair);
	BollingerCalculator calculator;

	OHLC tick;
	bool gotSomething = false;

	QDateTime start = projection->getInterval()->minus(axisPair.getMinTime(), N + 1);
	qDebug() << "Bollinger overlay start:" << start;
	for (QDateTime i = start; i < axisPair.getMaxTime();
			i = projection->getInterval()->firstAfter(i)) {
		if (projection->tryGetData(i, tick)) {
			gotSomething = true; // to skip empty days
		} else {
			// qDebug() << i << ": got nothing for bollinger calculator";
		}

		if (gotSomething) {
			calculator << tick;
			BollingerEntry entry;
			if (i >= projection->getMinimum() && calculator.get(entry)) {
				item->data.push_back(QPair<QDateTime, BollingerEntry>(i, entry));
			}
		}
	}

	scene->addItem(item);
	qDebug() << "Rendered bollinger overlay";
}

QRectF BollingerOverlay::Band::boundingRect() const {
	return QRectF(0, 0, axisPair.getWidth(), axisPair.getHeight());
}

QPainterPath BollingerOverlay::Band::shape() const {
	// TODO
	QPainterPath path;
	path.addRect(0, 0, axisPair.getWidth(), axisPair.getHeight());
	return path;
}

BollingerOverlay::Band::Band(AxisPair pair): axisPair(pair) {}

void BollingerOverlay::Band::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);

	// light green fill with green border
	painter->setPen(QPen(QColor(108, 205, 32), 1.0f));
	painter->setBrush(QColor(210, 238, 110));

	QPolygonF band;
	for (int i = 0; i < data.size(); i++) {
		band << QPointF(axisPair.getTimeX(data[i].first), axisPair.getPriceY(data[i].second.ceiling));
	}
	for (int i = data.size() - 1; i >= 0; i--) {
		band << QPointF(axisPair.getTimeX(data[i].first), axisPair.getPriceY(data[i].second.floor));
	}
	painter->drawPolygon(band);

	for (int i = 1; i < data.size(); i++) {
		float x1 = axisPair.getTimeX(data[i - 1].first),
			x2 = axisPair.getTimeX(data[i].first);

		painter->setPen(QPen(Qt::blue, 2.0f));
		painter->drawLine(
			QPointF(x1, axisPair.getPriceY(data[i - 1].second.midpoint)),
			QPointF(x2, axisPair.getPriceY(data[i].second.midpoint))
		);
	}

	// Draw lines
	/*
	QVarLengthArray<QLineF, 36> lines;
	for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
		lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
		lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
	}
	painter->drawLines(lines.data(), lines.size());
	*/
}
