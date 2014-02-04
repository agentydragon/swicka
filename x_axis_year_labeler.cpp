#include "x_axis_year_labeler.h"

#include <QDebug>

QList<QPair<QDateTime, QString> > XAxisYearLabeler::makeLabels(QDateTime start, QDateTime end) {
	QDateTime a = start;
	a.setTime(QTime(0, 0, 0));
	a.setDate(QDate(a.date().year(), 1, 1));

	QList<QPair<QDateTime, QString> > labels;
	for (; a <= end; a.setDate(a.date().addYears(1))) {
		qDebug() << "* " << a;
		labels.push_back(QPair<QDateTime, QString>(a, a.toString("yyyy")));
	}
	return labels;
}
