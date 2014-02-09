#ifndef MACD_CALCULATOR_H_INCLUDED
#define MACD_CALCULATOR_H_INCLUDED

#include "ema_calculator.h"

class MACDCalculator {
	public:
		struct Entry {
			float macd, signal, histogram;
		};
	private:
		EMACalculator slow, fast, signal;
		Entry current;
		bool gotSome;
	public:
		MACDCalculator(int slowSpeed = 26, int fastSpeed = 12, int signalSpeed = 9);

		void operator<<(OHLC datapoint);
		bool get(Entry& output);
};

QDebug operator<< (QDebug d, const MACDCalculator::Entry &entry);

#endif
