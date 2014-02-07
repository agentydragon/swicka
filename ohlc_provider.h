#ifndef OHLC_PROVIDER_H_INCLUDED
#define OHLC_PROVIDER_H_INCLUDED

#include "ohlc.h"
#include <QDateTime>

#include "candlestick_interval.h"

class OHLCProvider: public QObject {
	Q_OBJECT

	public:
		class out_of_range: std::exception {};

		virtual QDateTime getMinimum() = 0;
		virtual QDateTime getMaximum() = 0;
		virtual CandlestickInterval* getInterval() = 0;
		virtual bool tryGetData(QDateTime start, OHLC& output) = 0;

		bool isEmpty();
};

#endif
