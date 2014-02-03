#include "ohlc_shrinker.h"

OHLCShrinker::OHLCShrinker(OHLCProvider* source, QDateTime minimum, QDateTime maximum, int quantumSeconds) {
	this->source = source;
	this->minimum = minimum;
	this->maximum = maximum;
	this->quantumSeconds = quantumSeconds;
}

QDateTime OHLCShrinker::getMinimum() { return minimum; }
QDateTime OHLCShrinker::getMaximum() { return maximum; }
int OHLCShrinker::getQuantumSeconds() { return quantumSeconds; }

bool OHLCShrinker::tryGetData(QDateTime start, OHLC& output) {
	QDateTime now = start;
	bool someCollected = false;

	for (QDateTime now = start; now < start.addSecs(quantumSeconds); now = now.addSecs(source->getQuantumSeconds())) {
		OHLC tick;
		if (!source->tryGetData(now, tick)) continue;

		if (!someCollected) {
			output = tick;
			someCollected = true;
		} else {
			output << tick;
		}
	}

	return someCollected;
}
