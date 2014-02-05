#ifndef OHLC_MEMORY_PROVIDER
#define OHLC_MEMORY_PROVIDER

#include <vector>
#include <utility>

#include "ohlc_provider.h"

using namespace std;

class OHLCMemoryProvider: public OHLCProvider {
	private:
		QDateTime minimum;
		QDateTime maximum;
		CandlestickInterval* interval;

		// pair: OHLC, present?
		vector<pair<OHLC, bool> > data;

		long getTimeIndex(QDateTime time);
		long length;

	public:
		OHLCMemoryProvider(QDateTime minimum, QDateTime maximum, CandlestickInterval* interval);

		void addData(QDateTime start, OHLC data);

		virtual QDateTime getMinimum();
		virtual QDateTime getMaximum();
		virtual CandlestickInterval* getInterval();

		virtual bool tryGetData(QDateTime start, OHLC& output);
};

#endif
