#include "axis_pair.h"

AxisPair::AxisPair(NumberAxis num, TimeAxis time): numberAxis(num), timeAxis(time) {
}

float AxisPair::getTimeX(QDateTime time) const {
	return timeAxis.timeToCoord(time);
}

float AxisPair::getPriceY(float price) const {
	return numberAxis.numToCoord(price);
}

float AxisPair::getWidth() const {
	return timeAxis.getMaxCoord();
}

float AxisPair::getHeight() const {
	return numberAxis.getMaxCoord();
}

QDateTime AxisPair::getMinTime() const {
	return timeAxis.getMinTime();
}

QDateTime AxisPair::getMaxTime() const {
	return timeAxis.getMaxTime();
}

float AxisPair::getMinPrice() const {
	return numberAxis.getMinNum();
}

float AxisPair::getMaxPrice() const {
	return numberAxis.getMaxNum();
}

float AxisPair::getMinTimeX() const {
	return getTimeX(getMinTime());
}

float AxisPair::getMaxTimeX() const {
	return getTimeX(getMaxTime());
}

float AxisPair::getMinPriceY() const {
	return getPriceY(getMinPrice());
}

float AxisPair::getMaxPriceY() const {
	return getPriceY(getMaxPrice());
}
