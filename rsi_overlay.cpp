#include "rsi_overlay.h"

#include <QGraphicsScene>
#include <QPainter>

#include "ohlc_provider.h"

#include <assert.h>

#include "rsi_calculator.h"

void RSIOverlay::timeAxisChanged(TimeAxis timeAxis) {
	axisPair.timeAxis = timeAxis;
}

void RSIOverlay::numberAxisChanged(NumberAxis numberAxis) {
	axisPair.numberAxis = numberAxis;
}

void RSIOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

RSIOverlay::RSIOverlay() {}

// TODO: settable N
void RSIOverlay::insertIntoScene(QGraphicsScene* scene) {
	// Populate scene
	qDebug() << "Rendering RSI overlay";

	RSICalculator calculator;
	Graphics* item = new Graphics(axisPair);

	OHLC tick;
	bool gotSomething = false;

	int N = 14;
	// hack
	QDateTime start = projection->getInterval()->minus(axisPair.getMinTime(), N + 1);
	qDebug() << "RSI overlay start:" << start;

	for (QDateTime i = start; i < axisPair.getMaxTime();
			i = projection->getInterval()->firstAfter(i)) {
		if (projection->tryGetData(i, tick)) {
			gotSomething = true; // to skip empty days
		}

		if (gotSomething) {
			calculator << tick;
			float entry;
			// hack
			if (i >= projection->getMinimum() && calculator.get(entry)) {
				qDebug() << i << "==>" << entry;
				item->data.push_back(QPair<QDateTime, float>(i, entry));
			}
		}
	}
	scene->addItem(item);

	qDebug() << "Rendered RSI overlay";
}

QRectF RSIOverlay::Graphics::boundingRect() const {
	return QRectF(0, 0, axisPair.getWidth(), axisPair.getHeight());
}

QPainterPath RSIOverlay::Graphics::shape() const {
	// TODO
	QPainterPath path;
	path.addRect(0, 0, axisPair.getWidth(), axisPair.getHeight());
	return path;
}

RSIOverlay::Graphics::Graphics(AxisPair pair): axisPair(pair) {}

void RSIOverlay::Graphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(option);

	painter->setPen(QPen(Qt::red, 1.0f));
	painter->drawLine(
		QPointF(axisPair.getMinTimeX(), axisPair.getPriceY(70.0f)),
		QPointF(axisPair.getMaxTimeX(), axisPair.getPriceY(70.0f))
	);

	painter->setPen(QPen(Qt::blue, 1.0f));
	painter->drawLine(
		QPointF(axisPair.getMinTimeX(), axisPair.getPriceY(30.0f)),
		QPointF(axisPair.getMaxTimeX(), axisPair.getPriceY(30.0f))
	);


	for (int i = 1; i < data.size(); i++) {
		float x1 = axisPair.getTimeX(data[i - 1].first),
			x2 = axisPair.getTimeX(data[i].first);

		painter->setPen(QPen(Qt::black, 1.0f));
		painter->drawLine(
			QPointF(x1, axisPair.getPriceY(data[i - 1].second)),
			QPointF(x2, axisPair.getPriceY(data[i].second))
		);
	}
}
