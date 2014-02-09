#ifndef TIME_AXIS_H_INCLUDED
#define TIME_AXIS_H_INCLUDED

#include <QDateTime>
#include "time_range.h"

class TimeAxis {
	private:
		QDateTime begin, end;
		float minimum, maximum;
	public:
		TimeAxis() {} // TODO: remove those constructors!
		TimeAxis(TimeRange range, float min, float max);
		TimeAxis(QDateTime begin, QDateTime end, float min, float max);
		float timeToCoord(QDateTime time) const;
		QDateTime coordToTime(float coord) const;
		float getMaxCoord() const;
		QDateTime getMinTime() const;
		QDateTime getMaxTime() const;
};

#endif
