#ifndef GRAPH_RANGES_H_INCLUDED
#define GRAPH_RANGES_H_INCLUDED

#include <QDateTime>

struct GraphRanges {
	float priceLow, priceHigh;
	QDateTime start, end;

	float width, height;

	public:
		float getPriceY(float price);
		float getTimeX(QDateTime time);
		float getTimeSpanWidth(float secs);
};

#endif
