#include "graph_ranges.h"

float GraphRanges::getPriceY(float price) {
	float level = ((price - priceLow) / (priceHigh - priceLow));
	return (1.0f - level) * height;
}

float GraphRanges::getTimeX(QDateTime time) {
	float level = (float)(time.toTime_t() - start.toTime_t()) / (end.toTime_t() - start.toTime_t());
	return level * width;
}

float GraphRanges::getTimeSpanWidth(float secs) {
	return secs / (end.toTime_t() - start.toTime_t()) * width;
}

QDateTime GraphRanges::getXTime(float x) {
	float level = x / width;
	return start.addSecs((float)(end.toTime_t() - start.toTime_t()) * level);
}
