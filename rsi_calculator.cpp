#include <QDebug>

#include "rsi_calculator.h"

RSICalculator::RSICalculator(int N) {
	this->N = N;
}

void RSICalculator::operator<<(OHLC datapoint) {
	Entry e;
	if (datapoint.close > datapoint.open) {
		e.U = datapoint.close - datapoint.open;
		e.D = 0;
	} else {
		e.D = datapoint.open - datapoint.close;
		e.U = 0;
	}
	data.push_back(e);
	while (data.size() > N) data.pop_front();
}

float RSICalculator::getUpAvg() {
	float s = 0;
	for (const Entry& e: data) s += e.U;
	return s / data.size();
}

float RSICalculator::getDownAvg() {
	float s = 0;
	for (const Entry& e: data) s += e.D;
	return s / data.size();
}

bool RSICalculator::get(float& output) {
	float U = getUpAvg(), D = getDownAvg();
	if (data.size() < N) return false;
	qDebug() << "U=" << U << "D=" << D;
	if (D < 0.00001f) {
		output = 100.0f; // D=0 corner case
		return true;
	}
	output = 100.0f - (100.0f / (1.0f + (U / D)));
	return true;
}
