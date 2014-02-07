#include "graph_ranges.h"

#include <QDebug>

float GraphRanges::getPriceY(float price) {
	float level = ((price - priceLow) / (priceHigh - priceLow));
	return (1.0f - level) * height;
}

float GraphRanges::getYPrice(float y) {
	float rl = 1.0f - (y / height);
	return (rl * (priceHigh - priceLow)) + priceLow;
}

float GraphRanges::getTimeX(QDateTime time) {
	float level = (float)(time.toTime_t() - start.toTime_t()) / (end.toTime_t() - start.toTime_t());
	return level * width;
}

float GraphRanges::getTimeSpanWidth(float secs) const {
	return secs / (end.toTime_t() - start.toTime_t()) * width;
}

QDateTime GraphRanges::getXTime(float x) {
	float level = x / width;
	return start.addSecs((float)(end.toTime_t() - start.toTime_t()) * level);
}

QDebug operator<< (QDebug d, const GraphRanges &ranges) {
	d << "[" << ranges.priceLow << ".." << ranges.priceHigh << ";" << ranges.start << ".." << ranges.end << "; " << ranges.width << "x" << ranges.height << "]";
    return d;
}
