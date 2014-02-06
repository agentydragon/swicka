#include "bollinger_calculator.h"
#include <cmath>

using namespace std;

BollingerCalculator::BollingerCalculator(int N, int K) {
	this->N = N;
	this->K = K;
}

void BollingerCalculator::operator<<(OHLC datapoint) {
	data.push_back(float(datapoint));
	while (data.size() > N) data.pop_front();
}

bool BollingerCalculator::get(BollingerEntry& entry) {
	if (data.size() < N) return false;
	float sum = 0;
	for (float i: data) sum += i;
	sum /= N;

	float error = 0;
	for (float i: data) error += (i - sum) * (i - sum);
	error = sqrt(error / N);

	entry.floor = sum - K * error;
	entry.midpoint = sum;
	entry.ceiling = sum + K * error;
	return true;
}
