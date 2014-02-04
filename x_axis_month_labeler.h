#ifndef X_AXIS_LABELER_MONTH_INCLUDED
#define X_AXIS_LABELER_MONTH_INCLUDED

#include "x_axis_labeler.h"

class XAxisMonthLabeler: public XAxisLabeler {
	public:
		virtual QList<QPair<QDateTime, QString> > makeLabels(QDateTime start, QDateTime end);
};

#endif
