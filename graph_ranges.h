#ifndef GRAPH_RANGES_H_INCLUDED
#define GRAPH_RANGES_H_INCLUDED

#include <QDateTime>

struct GraphRanges {
	float priceLow, priceHigh;
	QDateTime start, end;

	float width, height;

	public:
		float getPriceY(float price);
		float getYPrice(float y);
		float getTimeX(QDateTime time);
		float getTimeSpanWidth(float secs) const;
		QDateTime getXTime(float x);
};

QDebug operator<< (QDebug d, const GraphRanges &ranges);

#endif
