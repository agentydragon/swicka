#include "ohlc_shrinker.h"

OHLCShrinker::OHLCShrinker(OHLCProvider* source, QDateTime minimum, QDateTime maximum, CandlestickInterval* interval) {
	this->source = source;
	this->minimum = minimum;
	this->maximum = maximum;
	this->interval = interval;
}

QDateTime OHLCShrinker::getMinimum() { return minimum; }
QDateTime OHLCShrinker::getMaximum() { return maximum; }
CandlestickInterval* OHLCShrinker::getInterval() { return interval; }

bool OHLCShrinker::tryGetData(QDateTime start, OHLC& output) {
	bool someCollected = false;

	for (QDateTime now = interval->lastBefore(start); now < interval->firstAfter(start); now = source->getInterval()->firstAfter(now)) {
		OHLC tick;
		if (!source->tryGetData(now, tick)) {
			continue;
		}
		if (!someCollected) {
			output = tick;
			someCollected = true;
		} else {
			output << tick;
		}
	}

	if (!someCollected) {
		qDebug() << "parent said nothing for" << start;
	}/* else {
		qDebug() << "output: " << output;
	}
	*/

	return someCollected;
}
