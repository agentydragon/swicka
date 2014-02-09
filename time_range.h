#ifndef TIME_RANGE_H_INCLUDED
#define TIME_RANGE_H_INCLUDED

class TimeRange {
	public:
		QDateTime begin, end;
		TimeRange(QDateTime b, QDateTime e): begin(b), end(e) {};
};

#endif
