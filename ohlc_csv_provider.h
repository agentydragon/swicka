#ifndef OHLC_CSV_PROVIDER
#define OHLC_CSV_PROVIDER

#include "ohlc_provider.h"

#include <QString>

class OHLCCSVProvider: public OHLCProvider {
	public:
		OHLCCSVProvider(QString filename);
		virtual QDateTime getMinimum();
		virtual QDateTime getMaximum();
		virtual int getQuantumSeconds();
		virtual bool tryGetData(QDateTime start, OHLC& output);
};

#endif
