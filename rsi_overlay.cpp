#include "rsi_overlay.h"

#include <QGraphicsScene>

#include "ohlc_provider.h"
#include "candle.h"

#include <assert.h>

void RSIOverlay::rangesChanged(GraphRanges ranges) {
	this->ranges = ranges;
}

void RSIOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

RSIOverlay::RSIOverlay(GraphViewport* viewport) {
	this->viewport = viewport;
}

void RSIOverlay::insertIntoScene(QGraphicsScene* scene) {
	// Populate scene
	qDebug() << "Rendering candlestick overlay";
	//int nitems = 0;

	/*
	for (QDateTime start = projection->getMinimum();
			start < projection->getMaximum();
			start = projection->getInterval()->firstAfter(start)) {
		OHLC tick;
		if (projection->tryGetData(start, tick)) {
			QDateTime next = projection->getInterval()->firstAfter(start);

			Candle *candle = new Candle(start, next, tick, ranges, controller);
			candle->setRanges(ranges);
			candle->setPos(QPointF(ranges.getTimeX(start), 0));

			scene->addItem(candle);
			nitems++;
		}
	}
	qDebug() << "Rendered" << nitems << "candlesticks";
	*/
	qDebug() << "TODO: render RSI";
}
