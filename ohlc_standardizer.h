#ifndef OHLC_STANDARDIZER_H_INCLUDED
#define OHLC_STANDARDIZER_H_INCLUDED

#include "ohlc_provider.h"

class OHLCStandardizer: public OHLCProvider {
	private:
		OHLCProvider* source;
		bool sourceEmpty;
		OHLC sourceClosure;
	public:
		OHLC getSourceClosure();

		OHLCStandardizer(OHLCProvider* source);
		virtual QDateTime getMinimum();
		virtual QDateTime getMaximum();
		virtual CandlestickInterval* getInterval();
		virtual bool tryGetData(QDateTime start, OHLC& output);

		// TODO: iterator
};

#endif
