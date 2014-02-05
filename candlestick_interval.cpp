#include "candlestick_interval.h"
#include <QDebug>

// TODO: optimize this, this gives quadratic complexity...

int CandlestickInterval::index(QDateTime start, QDateTime end) {
	int j = 0;
	qDebug() << "index" << end << "before" << start;
	if (end < start) return -1; // minus something...
	for (QDateTime i = lastBefore(start);
			i < firstAfter(end);
			i = firstAfter(i), j++) {
		qDebug() << "*" << i;
	}
	qDebug() << "->" << j;
	return j;
}

int CI::Day::index(QDateTime start, QDateTime end) {
	QDateTime i = lastBefore(start);
	end = firstAfter(end);

	int days = 0;

	// Bigger jumps
	while (i.date().month() < end.date().month() - 1 || i.date().year() < end.date().year()) {
		days += i.date().daysInMonth();
		i = i.addMonths(1);

		//qDebug() << "*" << i << " #" << days;
	}

	for (; i < firstAfter(end); i = firstAfter(i), days++) {
		//qDebug() << "*" << i << " #" << days;
	}
	qDebug() << "->" << days;
	return days;
}
