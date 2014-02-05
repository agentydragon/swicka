#include "ohlc_memory_provider.h"

OHLCMemoryProvider::OHLCMemoryProvider(QDateTime minimum, QDateTime maximum, CandlestickInterval* interval) {
	this->interval = interval;
	this->minimum = interval->lastBefore(minimum);
	this->maximum = interval->firstAfter(maximum);

	length = interval->index(minimum, maximum) + 1;
	data = vector<pair<OHLC, bool> >(length, make_pair(OHLC(), false));
}

long OHLCMemoryProvider::getTimeIndex(QDateTime time) {
	int index = interval->index(minimum, time);
	if (index < 0 || index > length) {
		qDebug() << "OHLC memory provider out of range: minimum=" << minimum << "maximum=" << maximum << "t=" << time;
		throw OHLCProvider::out_of_range();
	}
	return index;
}

void OHLCMemoryProvider::addData(QDateTime start, OHLC tick) {
	data[getTimeIndex(start)] = make_pair(tick, true);
}

QDateTime OHLCMemoryProvider::getMinimum() {
	return minimum;
}

QDateTime OHLCMemoryProvider::getMaximum() {
	return maximum;
}

CandlestickInterval* OHLCMemoryProvider::getInterval() {
	return interval;
}

bool OHLCMemoryProvider::tryGetData(QDateTime start, OHLC& output) {
	try {
		pair<OHLC, bool> tick = data[getTimeIndex(start)];
		output = tick.first;
		return tick.second;
	} catch (OHLCProvider::out_of_range&) {
		qDebug() << "get data for start=" << start << "failed: out of range";
		return false;
	}
}
