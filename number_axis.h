#ifndef NUMBER_AXIS_H_INCLUDED
#define NUMBER_AXIS_H_INCLUDED

#include "number_range.h"
#include <QDateTime>
#include <QString>

class NumberAxis {
	private:
		float begin, end; // viewport
		float minimum, maximum; // widget
		QString label;
	public:
		NumberAxis() {}
		NumberAxis(QString label, NumberRange range, float min, float max);
		NumberAxis(QString label, float begin, float end, float min, float max);
		float numToCoord(float x) const;
		float coordToNum(float x) const;
		float getMinCoord() const;
		float getMaxCoord() const;
		float getCenterCoord() const;
		float getMinNum() const;
		float getMaxNum() const;

		void setMinNum(float x);
		void setMaxNum(float x);

		QString getLabel() const;
};

#endif
