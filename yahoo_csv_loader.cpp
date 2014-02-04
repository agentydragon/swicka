#include "yahoo_csv_loader.h"

#include "csv_reader.h"

#include <assert.h>

// Yahoo CSV format:
// [header]:
//	Date,Open,High,Low,Close,Volume,Adj Close
//	2012-12-21,35.32,35.62,34.73,35.49,3889700,35.49

YahooCSVLoader::YahooCSVLoader(QIODevice* source, OHLCMemoryProvider* storage) {
	this->source = source;
	this->storage = storage;
}

void YahooCSVLoader::load() {
	CSVReader reader(new QTextStream(source));
	reader.loadNextLine();
	assert(reader.getField(0) == "Date");

	while (reader.loadNextLine()) {
		QDate date = QDate::fromString(reader.getField(0), "yyyy-MM-dd");

		float open = reader.getField(1).toFloat(),
		      high = reader.getField(2).toFloat(),
		      low = reader.getField(3).toFloat(),
		      close = reader.getField(4).toFloat();

		OHLC tick(open, high, low, close);
		// qDebug() << date << '\t' << open << '\t' << high << '\t' << low << '\t' << close;

		storage->addData(QDateTime(date), tick);
	}
	emit dataLoaded();
}
