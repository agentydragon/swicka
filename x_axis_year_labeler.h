#ifndef X_AXIS_LABELER_YEAR_INCLUDED
#define X_AXIS_LABELER_YEAR_INCLUDED

#include "x_axis_labeler.h"

class XAxisYearLabeler: public XAxisLabeler {
	public:
		virtual QList<QPair<QDateTime, QString> > makeLabels(QDateTime start, QDateTime end);
};

#endif
