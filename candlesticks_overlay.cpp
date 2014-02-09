#include "candlesticks_overlay.h"

#include <QGraphicsScene>

#include "ohlc_provider.h"
#include "candle.h"

#include <assert.h>

void CandlesticksOverlay::numberAxisChanged(NumberAxis numberAxis) {
	axisPair.numberAxis = numberAxis;
}

void CandlesticksOverlay::timeAxisChanged(TimeAxis timeAxis) {
	axisPair.timeAxis = timeAxis;
}

void CandlesticksOverlay::rebuild() {
	qDebug() << "Rebuilding candles...";

	connect(controller, SIGNAL(candleEntered(QDateTime)), this, SLOT(slotCandleEntered(QDateTime)));
	connect(controller, SIGNAL(candleLeft()), this, SLOT(slotCandleLeft()));
}

void CandlesticksOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

CandlesticksOverlay::CandlesticksOverlay() {
	this->controller = new GraphEventController;
	this->controller->setParent(this);
}

void CandlesticksOverlay::insertIntoScene(QGraphicsScene* scene) {
	// Populate scene
	qDebug() << "Rendering candlestick overlay";
	int nitems = 0;
	rebuild();


	for (QDateTime start = projection->getMinimum();
			start < projection->getMaximum();
			start = projection->getInterval()->firstAfter(start)) {
		OHLC tick;
		if (projection->tryGetData(start, tick)) {
			QDateTime next = projection->getInterval()->firstAfter(start);

			Candle *candle = new Candle(start, next, tick, axisPair, controller);
			float x = axisPair.getTimeX(start);
			qDebug() << "candle for" << start << "at X=" << x;
			candle->setPos(QPointF(x, 0));

			scene->addItem(candle);
			nitems++;
		}
	}
	qDebug() << "Rendered" << nitems << "candlesticks";
}

void CandlesticksOverlay::slotCandleEntered(QDateTime start) {
	emit candleEntered(start);
}

void CandlesticksOverlay::slotCandleLeft() {
	emit candleLeft();
}
