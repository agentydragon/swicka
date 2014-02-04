#include "csv_reader.h"
#include <QDebug>

CSVReader::CSVReader(QTextStream* stream) {
	this->stream = stream;
}

bool CSVReader::loadNextLine() {
	currentLine = stream->readLine();

	if (currentLine.isNull()) {
		return false;
	} else {
		// qDebug() << currentLine;
		fields = currentLine.split(','); // TODO: all the crazy formats and such
		return true;
	}
}

QString CSVReader::getField(int i) {
	return fields[i];
}
