#include "x_axis_day_labeler.h"

#include <QDebug>

QList<QPair<QDateTime, QString> > XAxisDayLabeler::makeLabels(QDateTime start, QDateTime end) {
	QDateTime a = start;
	a.setTime(QTime(0, 0, 0));

	QList<QPair<QDateTime, QString> > labels;
	for (; a <= end; a.setDate(a.date().addDays(1))) {
		labels.push_back(QPair<QDateTime, QString>(a, a.toString("dd.MM.")));
	}
	return labels;
}
