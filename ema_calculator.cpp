#include "ema_calculator.h"

EMACalculator::EMACalculator(int N) {
	alpha = 2.0f / (1.0f + N);
	gotAny = false;
}

void EMACalculator::operator<<(OHLC x) {
	return operator<<(float(x));
}

void EMACalculator::operator<<(float x) {
	if (!gotAny) {
		last = x;
	} else {
		last = (x - last) * alpha + last;
	}
	gotAny = true;
}

bool EMACalculator::get(float& output) {
	output = last;
	return gotAny;
}
