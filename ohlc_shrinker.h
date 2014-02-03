#ifndef OHLC_SHRINKER_H_INCLUDED
#define OHLC_SHRINKER_H_INCLUDED

#include "ohlc_provider.h"

class OHLCShrinker: public OHLCProvider {
	private:
		OHLCProvider* source;
		QDateTime minimum;
		QDateTime maximum;
		int quantumSeconds;
	public:
		OHLCShrinker(OHLCProvider* source, QDateTime minimum, QDateTime maximum, int quantumSeconds);

		virtual QDateTime getMinimum();
		virtual QDateTime getMaximum();
		virtual int getQuantumSeconds();
		virtual bool tryGetData(QDateTime start, OHLC& output);
};

#endif
