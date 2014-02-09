#ifndef RSI_CALCULATOR_H_INCLUDED
#define RSI_CALCULATOR_H_INCLUDED

#include "ohlc.h"
#include <deque>

class RSICalculator {
	public:
		RSICalculator(unsigned int N = 14);
		void operator<<(OHLC datapoint);
		bool get(float& output);
	private:
		struct Entry {
			float D, U;
		};
		float getUpAvg();
		float getDownAvg();
		unsigned int N;
		std::deque<Entry> data;
};

#endif
