#include "ohlc.h"
#include "ohlc_random_generator.h"

QDateTime OHLCRandomGenerator::getMinimum() {
	return QDateTime(QDate(2010, 1, 1));
}

QDateTime OHLCRandomGenerator::getMaximum() {
	return QDateTime(QDate(2012, 12, 22));
}

int OHLCRandomGenerator::getQuantumSeconds() {
	return 24 * 60 * 60;
}

bool OHLCRandomGenerator::tryGetData(QDateTime start, OHLC& output) {
	srand(start.toTime_t());

	if (rand() % 10 == 0) return false;

	output.low = rand() % 200;
	output.high = output.low + rand() % 200 + 1;
	output.open = output.low + rand() % (int)(output.high - output.low);
	output.close = output.low + rand() % (int)(output.high - output.low);
	return true;
}
