#ifndef NUMBER_AXIS_H_INCLUDED
#define NUMBER_AXIS_H_INCLUDED

#include "number_range.h"
#include <QDateTime>

class NumberAxis {
	private:
		float begin, end; // viewport
		float minimum, maximum; // widget
	public:
		NumberAxis() {}
		NumberAxis(NumberRange range, float min, float max);
		NumberAxis(float begin, float end, float min, float max);
		float numToCoord(float x) const;
		float coordToNum(float x) const;
		float getMaxCoord() const;
		float getMinNum() const;
		float getMaxNum() const;

		void setMinNum(float x);
		void setMaxNum(float x);
};

#endif
