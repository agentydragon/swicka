#include "x_axis_day_labeler.h"

#include <QDebug>

XAxisDayLabeler::XAxisDayLabeler(int every) {
	this->every = every;
}

QList<QPair<QDateTime, QString> > XAxisDayLabeler::makeLabels(QDateTime start, QDateTime end) {
	QDate a = start.date(), last = a;

	QList<QPair<QDateTime, QString> > labels;
	for (; a <= end.date(); ) {
		if (a.month() != last.month()) {
			a = QDate(a.year(), a.month(), 1); // Reset on month boundary
		}
		labels.push_back(QPair<QDateTime, QString>(QDateTime(a), a.toString("dd.MM.")));

		last = a;
		a = a.addDays(every);
	}
	return labels;
}
