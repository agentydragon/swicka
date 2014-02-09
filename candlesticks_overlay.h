#ifndef CANDLESTICKS_OVERLAY_H_INCLUDED
#define CANDLESTICKS_OVERLAY_H_INCLUDED

// TODO: scena by se nemela sama od sebe cela rozbijet, ne?

#include "graph_overlay.h"
#include "graph_event_controller.h"
#include "axis_pair.h"
#include <QList>

class Candle;

class CandlesticksOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		GraphEventController* controller;
		OHLCProvider* projection;
		AxisPair axisPair;

		void rebuild();
	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis);
		virtual void numberAxisChanged(NumberAxis numberAxis);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		CandlesticksOverlay();
		virtual void insertIntoScene(QGraphicsScene* scene);
	private slots:
		void slotCandleEntered(QDateTime start);
		void slotCandleLeft();
	signals:
		void candleEntered(QDateTime start);
		void candleLeft();
};

#endif
