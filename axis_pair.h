#ifndef AXIS_PAIR_H_INCLUDED
#define AXIS_PAIR_H_INCLUDED

#include "time_axis.h"
#include "number_axis.h"

// TODO: more generic?

class AxisPair {
	public:
		NumberAxis numberAxis;
		TimeAxis timeAxis;

		AxisPair() {}
		AxisPair(NumberAxis num, TimeAxis time);

		float getTimeX(QDateTime time) const;
		float getPriceY(float price) const; // TODO: rename
		float getWidth() const;
		float getHeight() const;

		QDateTime getMinTime() const;
		QDateTime getMaxTime() const;

		float getMinPrice() const;
		float getMaxPrice() const;

		float getMinTimeX() const;
		float getMaxTimeX() const;

		float getMinPriceY() const;
		float getMaxPriceY() const;
};

#endif
