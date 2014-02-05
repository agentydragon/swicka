#ifndef CANDLESTICKS_OVERLAY_H_INCLUDED
#define CANDLESTICKS_OVERLAY_H_INCLUDED

#include "graph_overlay.h"
#include <QList>

class GraphViewport;
class Candle;

class CandlesticksOverlay: public GraphOverlay {
	private:
		GraphViewport* viewport;
		GraphRanges ranges;
		OHLCProvider* projection;

		QList<Candle*> candles;

		void destroy();
		void rebuild();
	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		CandlesticksOverlay(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);
		virtual ~CandlesticksOverlay();
};

#endif
