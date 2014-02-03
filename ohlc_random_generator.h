#ifndef OHLC_RANDOM_GENERATOR_H_INCLUDED
#define OHLC_RANDOM_GENERATOR_H_INCLUDED

#include "ohlc_provider.h"

#include <QDateTime>

class OHLCRandomGenerator: public OHLCProvider {
	public:
		virtual QDateTime getMinimum();
		virtual QDateTime getMaximum();
		virtual int getQuantumSeconds();
		virtual bool tryGetData(QDateTime start, OHLC& output);
};

#endif
