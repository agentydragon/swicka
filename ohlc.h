#ifndef OHLC_H_INCLUDED
#define OHLC_H_INCLUDED

#include <QDebug>

class OHLCProvider;

struct OHLC {
	public:
		OHLC() {}
		OHLC(float o, float h, float l, float c): open(o), high(h), low(l), close(c) {}

		float open, high, low, close;
		void operator<<(const OHLC& other);
		bool isUp();
		void standardizeTo(OHLC general);

		static bool span(OHLCProvider* provider, OHLC& result);
};

QDebug operator<< (QDebug d, const OHLC &ohlc);

#endif
