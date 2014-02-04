#ifndef X_AXIS_LABELER_H_INCLUDED
#define X_AXIS_LABELER_H_INCLUDED

#include <QList>
#include <QPair>
#include <QDateTime>
#include <QString>

class XAxisLabeler {
	public:
		virtual QList<QPair<QDateTime, QString> > makeLabels(QDateTime start, QDateTime end) = 0;
};

#endif
