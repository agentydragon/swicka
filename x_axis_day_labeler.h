#ifndef X_AXIS_LABELER_DAY_INCLUDED
#define X_AXIS_LABELER_DAY_INCLUDED

#include "x_axis_labeler.h"

class XAxisDayLabeler: public XAxisLabeler {
	public:
		virtual QList<QPair<QDateTime, QString> > makeLabels(QDateTime start, QDateTime end);
};

#endif
