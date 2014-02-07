#ifndef RSI_OVERLAY_H_INCLUDED
#define RSI_OVERLAY_H_INCLUDED

// TODO: scena by se nemela sama od sebe cela rozbijet, ne?

#include "graph_overlay.h"
#include "graph_event_controller.h"
#include <QList>

class GraphViewport;

class RSIOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		GraphViewport* viewport;
		GraphRanges ranges;
		OHLCProvider* projection;
	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		RSIOverlay(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);
};

#endif
