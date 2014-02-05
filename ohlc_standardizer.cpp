#include "ohlc_standardizer.h"

#include <assert.h>

OHLC OHLCStandardizer::getSourceClosure() {
	return sourceClosure;
}

OHLCStandardizer::OHLCStandardizer(OHLCProvider* source) {
	assert(source);
	this->source = source;

	sourceEmpty = !OHLC::span(source, sourceClosure);
}

QDateTime OHLCStandardizer::getMinimum() { return source->getMinimum(); }
QDateTime OHLCStandardizer::getMaximum() { return source->getMaximum(); }
CandlestickInterval* OHLCStandardizer::getInterval() { return source->getInterval(); }

bool OHLCStandardizer::tryGetData(QDateTime start, OHLC& output) {
	if (source->tryGetData(start, output)) {
		assert(!sourceEmpty);
		output.standardizeTo(sourceClosure);
		return true;
	} else {
		return false;
	}
}
