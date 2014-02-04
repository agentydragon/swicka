#ifndef YAHOO_CSV_LOADER_H_INCLUDED
#define YAHOO_CSV_LOADER_H_INCLUDED

#include <QIODevice>

#include "data_loader.h"
#include "ohlc_memory_provider.h"

class YahooCSVLoader: public DataLoader {
	Q_OBJECT

	public:
		YahooCSVLoader(QIODevice* source, OHLCMemoryProvider* storage);
		virtual void load();

	private:
		QIODevice* source;
		OHLCMemoryProvider* storage;

	signals:
		void dataLoaded();
};

#endif
