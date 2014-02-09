#include "time_axis.h"

TimeAxis::TimeAxis(TimeRange range, float min, float max) {
	begin = range.begin;
	end = range.end;
	minimum = min;
	maximum = max;
}

TimeAxis::TimeAxis(QDateTime begin, QDateTime end, float min, float max) {
	this->begin = begin;
	this->end = end;
	minimum = min;
	maximum = max;
}

float TimeAxis::timeToCoord(QDateTime time) const {
	float level = (float)(time.toTime_t() - begin.toTime_t()) / (float)(end.toTime_t() - begin.toTime_t());
	return (level * (maximum - minimum)) + minimum;
}

QDateTime TimeAxis::coordToTime(float coord) const {
	float level = (coord - minimum) / (maximum - minimum);
	return begin.addSecs((float)(end.toTime_t() - begin.toTime_t()) * level);
}

float TimeAxis::getMaxCoord() const {
	return maximum;
}

QDateTime TimeAxis::getMinTime() const {
	return begin;
}

QDateTime TimeAxis::getMaxTime() const {
	return end;
}
