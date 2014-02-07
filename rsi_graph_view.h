#ifndef RSI_GRAPH_VIEW_H_INCLUDED
#define RSI_GRAPH_VIEW_H_INCLUDED

#include "abstract_graph_view.h"

class GraphOverlay;

class RSIGraphView: public AbstractGraphView {
	Q_OBJECT

	public:
		RSIGraphView();

	protected:
		virtual void internalizeViewport(GraphViewport* viewport);
		virtual void addOverlays();
};

#endif
