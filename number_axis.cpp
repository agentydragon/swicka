#include "number_axis.h"

NumberAxis::NumberAxis(NumberRange range, float min, float max) {
	begin = range.minimum; end = range.maximum;
	this->minimum = min; this->maximum = max;
}

NumberAxis::NumberAxis(float begin, float end, float min, float max) {
	this->begin = begin; this->end = end;
	this->minimum = min; this->maximum = max;
}

float NumberAxis::numToCoord(float x) const {
	float level = (x - begin) / (end - begin);
	return level * (maximum - minimum) + minimum;
}

float NumberAxis::coordToNum(float x) const {
	float level = (x - minimum) / (maximum - minimum);
	return level * (end - begin) + begin;
}

float NumberAxis::getMaxCoord() const {
	return maximum;
}

float NumberAxis::getMinNum() const {
	return begin;
}

float NumberAxis::getMaxNum() const {
	return end;
}

void NumberAxis::setMinNum(float x) {
	begin = x;
}

void NumberAxis::setMaxNum(float x) {
	end = x;
}
