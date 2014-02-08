#ifndef EMA_CALCULATOR_H_INCLUDED
#define EMA_CALCULATOR_H_INCLUDED

#include "ohlc.h"

class EMACalculator {
	public:
		EMACalculator(int N);
		void operator<<(float x);
		void operator<<(OHLC x);
		bool get(float& output);
	private:
		float alpha;
		float last;
		bool gotAny;
};

#endif
