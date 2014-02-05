#ifndef OHLC_SHRINKER_H_INCLUDED
#define OHLC_SHRINKER_H_INCLUDED

#include "ohlc_provider.h"
#include "candlestick_interval.h"

class OHLCShrinker: public OHLCProvider {
	private:
		OHLCProvider* source;
		QDateTime minimum;
		QDateTime maximum;
		CandlestickInterval* interval;

	public:
		OHLCShrinker(OHLCProvider* source, QDateTime minimum, QDateTime maximum, CandlestickInterval* interval);

		virtual QDateTime getMinimum();
		virtual QDateTime getMaximum();
		virtual CandlestickInterval* getInterval();

		virtual bool tryGetData(QDateTime start, OHLC& output);
};

#endif
