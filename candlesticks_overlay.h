#ifndef CANDLESTICKS_OVERLAY_H_INCLUDED
#define CANDLESTICKS_OVERLAY_H_INCLUDED

// TODO: scena by se nemela sama od sebe cela rozbijet, ne?

#include "graph_overlay.h"
#include "graph_event_controller.h"
#include <QList>

class GraphViewport;
class Candle;

class CandlesticksOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		GraphEventController controller;
		GraphViewport* viewport;
		GraphRanges ranges;
		OHLCProvider* projection;

		void rebuild();
	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		CandlesticksOverlay(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);
	private slots:
		void slotCandleEntered(QDateTime start);
		void slotCandleLeft();
	signals:
		void candleEntered(QDateTime start);
		void candleLeft();
};

#endif
