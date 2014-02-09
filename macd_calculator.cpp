#include "macd_calculator.h"

MACDCalculator::MACDCalculator(int slowSpeed, int fastSpeed, int signalSpeed):
	slow(slowSpeed), fast(fastSpeed), signal(signalSpeed) {
	gotSome = false;
}

void MACDCalculator::operator<<(OHLC datapoint) {
	slow << datapoint;
	fast << datapoint;

	float s, f;
	if (slow.get(s) && fast.get(f)) {
		signal << f - s;

		if (signal.get(current.signal)) {
			current.macd = f - s;
			current.histogram = current.macd - current.signal;
			gotSome = true;
		} else {
			gotSome = false;
		}
	}
}

bool MACDCalculator::get(Entry& output) {
	output = current;
	return gotSome;
}

QDebug operator<< (QDebug d, const MACDCalculator::Entry &entry) {
	d << "[MACD:" << entry.macd << "Sig:" << entry.signal << "Hist:" << entry.histogram << "]";
    return d;
}
