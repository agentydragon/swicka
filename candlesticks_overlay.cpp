#include "candlesticks_overlay.h"

#include <QGraphicsScene>

#include "ohlc_provider.h"
#include "candle.h"

#include <assert.h>

CandlesticksOverlay::~CandlesticksOverlay() {
	destroy();
}

void CandlesticksOverlay::rangesChanged(GraphRanges ranges) {
	this->ranges = ranges;
	for (Candle* candle: candles) {
		candle->setRanges(ranges);
		candle->setPos(QPointF(ranges.getTimeX(candle->getStart()), 0));
	}
}

void CandlesticksOverlay::destroy() {
	qDebug() << "Destroying candles...";
	candles.clear(); // TODO: and delete them all...
	assert(candles.size() == 0);
	qDebug() << "Candles destroyed.";
	//
	// It's absolutely unneeded to delete those candles.
	// The scene takes ownership of its items.
}

void CandlesticksOverlay::rebuild() {
	destroy();

	qDebug() << "Rebuilding candles...";

	connect(&controller, SIGNAL(candleEntered(QDateTime)), this, SLOT(slotCandleEntered(QDateTime)));
	connect(&controller, SIGNAL(candleLeft()), this, SLOT(slotCandleLeft()));

	for (QDateTime start = projection->getMinimum();
			start < projection->getMaximum();
			start = projection->getInterval()->firstAfter(start)) {
		OHLC tick;
		if (projection->tryGetData(start, tick)) {
			QDateTime next = projection->getInterval()->firstAfter(start);

			Candle *candle = new Candle(start, next, tick, ranges, &controller);
			candle->setPos(QPointF(ranges.getTimeX(start), 0));

			candles.push_back(candle);
		}
	}

	qDebug() << "Candles rebuilt -- #=" << candles.size();
}

void CandlesticksOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

CandlesticksOverlay::CandlesticksOverlay(GraphViewport* viewport) {
	this->viewport = viewport;
}

void CandlesticksOverlay::insertIntoScene(QGraphicsScene* scene) {
	// Populate scene
	qDebug() << "Rendering candlestick overlay";
	int nitems = 0;
	rebuild();
	for (Candle* candle: candles) {
		// qDebug() << "Adding candle:" << candle;
		scene->addItem(candle);
		nitems++;
	}
	qDebug() << "Rendered" << nitems << "candlesticks";
}

void CandlesticksOverlay::slotCandleEntered(QDateTime start) {
	emit candleEntered(start);
}

void CandlesticksOverlay::slotCandleLeft() {
	emit candleLeft();
}
