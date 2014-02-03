#ifndef OHLC_PROVIDER_H_INCLUDED
#define OHLC_PROVIDER_H_INCLUDED

#include "ohlc.h"
#include <QDateTime>

class OHLCProvider {
	public:
		virtual QDateTime getMinimum() = 0;
		virtual QDateTime getMaximum() = 0;
		virtual int getQuantumSeconds() = 0;
		virtual bool tryGetData(QDateTime start, OHLC& output) = 0;

		bool isEmpty();
};

#endif
