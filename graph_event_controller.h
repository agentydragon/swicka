#ifndef GRAPH_EVENT_CONTROLLER_H_INCLUDED
#define GRAPH_EVENT_CONTROLLER_H_INCLUDED

#include <QObject>
#include <QDateTime>

class GraphEventController: public QObject {
	Q_OBJECT

	public:
		void signalCandleEntered(QDateTime start);
		void signalCandleLeft();

	signals:
		void candleEntered(QDateTime start);
		void candleLeft();
};

#endif
