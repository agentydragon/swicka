#include "rsi_overlay.h"

#include <QGraphicsScene>
#include <QPainter>

#include "ohlc_provider.h"
#include "candle.h"

#include <assert.h>

#include "rsi_calculator.h"

void RSIOverlay::rangesChanged(GraphRanges ranges) {
	this->ranges = ranges;
}

void RSIOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

RSIOverlay::RSIOverlay(GraphViewport* viewport) {
	this->viewport = viewport;
}

// TODO: settable N
void RSIOverlay::insertIntoScene(QGraphicsScene* scene) {
	// Populate scene
	qDebug() << "Rendering candlestick overlay";

	RSICalculator calculator;
	Graphics* item = new Graphics(ranges);

	OHLC tick;
	bool gotSomething = false;

	int N = 14;
	QDateTime start = projection->getInterval()->minus(ranges.start, N + 1);
	qDebug() << "RSI overlay start:" << start;

	for (QDateTime i = start; i < ranges.end;
			i = projection->getInterval()->firstAfter(i)) {
		if (projection->tryGetData(i, tick)) {
			gotSomething = true; // to skip empty days
		}

		if (gotSomething) {
			calculator << tick;
			float entry;
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
	return QRectF(0, 0, ranges.width, ranges.height);
}

QPainterPath RSIOverlay::Graphics::shape() const {
	// TODO
	QPainterPath path;
	path.addRect(0, 0, ranges.width, ranges.height);
	return path;
}

RSIOverlay::Graphics::Graphics(GraphRanges ranges) {
	this->ranges = ranges;
}

void RSIOverlay::Graphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);

	// TODO: basic levels
	painter->setPen(QPen(Qt::black, 1.0f));

	for (int i = 1; i < data.size(); i++) {
		float x1 = ranges.getTimeX(data[i - 1].first),
			x2 = ranges.getTimeX(data[i].first);

		painter->setPen(QPen(Qt::blue, 2.0f));
		painter->drawLine(
			QPointF(x1, ranges.getPriceY(data[i - 1].second)),
			QPointF(x2, ranges.getPriceY(data[i].second))
		);
	}
}
