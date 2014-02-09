#include "x_axis_month_labeler.h"

#include <QDebug>

XAxisMonthLabeler::XAxisMonthLabeler(int every) {
	this->every = every;
}

QList<QPair<QDateTime, QString> > XAxisMonthLabeler::makeLabels(QDateTime start, QDateTime end) {
	QDate a = QDate(start.date().year(), start.date().month(), 1);

	QList<QPair<QDateTime, QString> > labels;

	QDate last = a;
	while (a <= end.date()) {
		qDebug() << a << "; last=" << last;
		QString format;
		if (a.year() != last.year() || a == last) {
			format = "MM/yyyy"; // TODO: and it's major
		} else {
			format = "MM";
		}
		if (a.year() > last.year()) { // reset on year boundaries
			a = QDate(a.year(), 1, 1);
		}

		QDateTime dt(a);
		labels.push_back(QPair<QDateTime, QString>(dt, a.toString(format)));
		last = a;
		a = a.addMonths(every);
	}
	return labels;
}
