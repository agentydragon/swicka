#include <cmath>
#include <QDebug>
#include "ohlc.h"
#include "ohlc_provider.h"

using namespace std;

void OHLC::operator<<(const OHLC& other) {
	high = fmax(other.high, high);
	low = fmin(other.low, low);
	close = other.close;
}

bool OHLC::isUp() {
	return open <= close;
}

static void standardizeTo(float &x, OHLC general) {
	x = (x - general.low) / (general.high - general.low);
}

void OHLC::standardizeTo(OHLC general) {
	::standardizeTo(open, general);
	::standardizeTo(high, general);
	::standardizeTo(low, general);
	::standardizeTo(close, general);
}

QDebug operator<< (QDebug d, const OHLC &ohlc) {
	d << "[O:" << ohlc.open << "H:" << ohlc.high << "L:" << ohlc.low << "C:" << ohlc.close << "]";
    return d;
}

bool OHLC::span(OHLCProvider* provider, OHLC& result) {
	bool sourceEmpty = true;
	OHLC sourceClosure;
	for (QDateTime start = provider->getMinimum();
			start < provider->getMaximum();
			start = provider->getInterval()->firstAfter(start)) {
		OHLC tick;

		if (!provider->tryGetData(start, tick)) continue;
		if (sourceEmpty) {
			sourceClosure = tick;
			sourceEmpty = false;
		} else {
			sourceClosure << tick;
		}
	}
	if (!sourceEmpty) {
		result = sourceClosure;
		return true;
	} else {
		return false;
	}
}

OHLC::operator float() {
	// TODO: close???
	return (open + high + low + close) / 4;
}
