#ifndef BOLLINGER_CALCULATOR_H_INCLUDED
#define BOLLINGER_CALCULATOR_H_INCLUDED

#include "ohlc.h"
#include <deque>

struct BollingerEntry {
	float floor, midpoint, ceiling;
	BollingerEntry() {}
	BollingerEntry(float f, float m, float c): floor(f), midpoint(m), ceiling(c) {}
};

class BollingerCalculator {
	public:
		BollingerCalculator(int N = 20, int K = 2);
		void operator<<(OHLC datapoint);
		bool get(BollingerEntry& output);
	private:
		int N, K;
		std::deque<float> data;
};

#endif
