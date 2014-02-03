#ifndef CSV_READER_H_INCLUDED
#define CSV_READER_H_INCLUDED

#include <QObject>
#include <QTextStream>

class CSVReader: public QObject {
	private:
		QTextStream* stream;
		QString currentLine;
		QStringList fields;
	public:
		CSVReader(QTextStream* stream);
		bool loadNextLine();
		QString getField(int i);
};

#endif
