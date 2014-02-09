#include "number_axis.h"

NumberAxis::NumberAxis(QString label, NumberRange range, float min, float max) {
	begin = range.minimum; end = range.maximum;
	this->minimum = min; this->maximum = max;
	this->label = label;
}

NumberAxis::NumberAxis(QString label, float begin, float end, float min, float max) {
	this->begin = begin; this->end = end;
	this->minimum = min; this->maximum = max;
	this->label = label;
}

float NumberAxis::numToCoord(float x) const {
	float level = (x - begin) / (end - begin);
	float coord = (1.0f - level) * (maximum - minimum) + minimum;
	return coord;
}

float NumberAxis::coordToNum(float x) const {
	float level = (x - minimum) / (maximum - minimum);
	float num = (1.0f - level) * (end - begin) + begin;
	return num;
}

float NumberAxis::getMinCoord() const {
	return minimum;
}

float NumberAxis::getMaxCoord() const {
	return maximum;
}

float NumberAxis::getCenterCoord() const {
	return (getMinCoord() + getMaxCoord()) / 2;
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

QString NumberAxis::getLabel() const {
	return label;
}
