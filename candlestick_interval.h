#ifndef CANDLESTICK_INTERVAL_H_INCLUDED
#define CANDLESTICK_INTERVAL_H_INCLUDED

#include <QDateTime>

// TODO: my own interval representation? (to store logical size, not second size)
class CandlestickInterval {
	public:
		virtual QDateTime lastBefore(QDateTime x) = 0;
		virtual QDateTime firstAfter(QDateTime x) = 0;

		virtual int index(QDateTime start, QDateTime end);
};

namespace CI {
	class PureTimespan: public CandlestickInterval {
		private:
			int seconds;
		public:
			PureTimespan(int s): seconds(s) {};

			virtual QDateTime lastBefore(QDateTime x) {
				return x;
			}

			virtual QDateTime firstAfter(QDateTime x) {
				return lastBefore(x).addSecs(seconds);
			}
	};

	/*
	class Minute: public CandlestickInterval {
		public:
			virtual QDateTime lastBefore(QDateTime x) {
				x.setTime(QTime(x.time().hour(), x.time().minute(), 0));
				return x;
			}

			virtual QDateTime firstAfter(QDateTime x) {
				return lastBefore(x).addMinutes(1);
			}
	};
	*/

	/*
	class Hour: public CandlestickInterval {
		public:
			virtual QDateTime lastBefore(QDateTime x) {
				x.setTime(QTime(x.hour(), 0, 0));
				return x;
			}

			virtual QDateTime firstAfter(QDateTime x) {
				return lastBefore(x).addHours(1);
			}
	};
	*/

	class Day: public CandlestickInterval {
		public:
			virtual QDateTime lastBefore(QDateTime x) {
				x.setTime(QTime(0, 0, 0));
				return x;
			}

			virtual QDateTime firstAfter(QDateTime x) {
				return lastBefore(x).addDays(1);
			}

			virtual int index(QDateTime start, QDateTime end);
	};

	class Month: public CandlestickInterval {
		public:
			virtual QDateTime lastBefore(QDateTime x) {
				x.setTime(QTime(0, 0, 0));
				x.setDate(QDate(x.date().year(), x.date().month(), 1));
				return x;
			}

			virtual QDateTime firstAfter(QDateTime x) {
				return lastBefore(x).addMonths(1);
			}
	};

	class Year: public CandlestickInterval {
		public:
			virtual QDateTime lastBefore(QDateTime x) {
				x.setTime(QTime(0, 0, 0));
				x.setDate(QDate(x.date().year(), 1, 1));
				return x;
			}

			virtual QDateTime firstAfter(QDateTime x) {
				return lastBefore(x).addYears(1);
			}
	};
};

#endif
