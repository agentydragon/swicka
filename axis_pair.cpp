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

float AxisPair::getMinTimeX() const {
	return getTimeX(getMinTime());
}

float AxisPair::getMaxTimeX() const {
	return getTimeX(getMaxTime());
}
