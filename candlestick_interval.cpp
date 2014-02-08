#include "candlestick_interval.h"
#include <QDebug>

// TODO: optimize this, this gives quadratic complexity...

QDateTime CandlestickInterval::minus(QDateTime x, int n) {
	for (int i = 0; i <= n; i++) {
		QDateTime y = lastBefore(x);
		// XXX HACK: lastBefore returns interval start...
		if (x.toTime_t() == y.toTime_t()) y = lastBefore(y.addSecs(-1));
		x = y;
	}
	return x;
}

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

QDateTime CI::Day::lastBefore(QDateTime x) {
	x.setTime(QTime(0, 0, 0));
	return x;
}

QDateTime CI::Day::firstAfter(QDateTime x) {
	return QDateTime(x.date().addDays(1));
}

int CI::Day::index(QDateTime start, QDateTime endDT) {
	QDate i = start.date();
	QDate end = firstAfter(endDT).date();

	int days = 0;

	// Bigger jumps
	while (i.month() < end.month() - 1 || i.year() < end.year()) {
		days += i.daysInMonth();
		i = i.addMonths(1);

		// qDebug() << "*" << i << " #" << days;
	}

	for (; i < end; i = i.addDays(1), days++) {
		// qDebug() << "*" << i << " #" << days;
	}
	// qDebug() << "->" << days;
	return days;
}
