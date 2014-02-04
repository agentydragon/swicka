#include "x_axis_month_labeler.h"

#include <QDebug>

QList<QPair<QDateTime, QString> > XAxisMonthLabeler::makeLabels(QDateTime start, QDateTime end) {
	QDateTime a = start;
	a.setTime(QTime(0, 0, 0));
	a.setDate(QDate(a.date().year(), a.date().month(), 1));

	QList<QPair<QDateTime, QString> > labels;
	for (; a <= end; a.setDate(a.date().addMonths(1))) {
		qDebug() << "* " << a;
		labels.push_back(QPair<QDateTime, QString>(a, a.toString("MM/yyyy")));
	}
	return labels;
}
