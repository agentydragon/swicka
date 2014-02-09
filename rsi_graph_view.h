#ifndef RSI_GRAPH_VIEW_H_INCLUDED
#define RSI_GRAPH_VIEW_H_INCLUDED

#include "abstract_graph_view.h"

class GraphOverlay;

class RSIGraphView: public AbstractGraphView {
	Q_OBJECT

	public:
		RSIGraphView();

	private:
		GraphViewport* m_viewport;

	protected:
		virtual GraphViewport* viewport();
		virtual void internalizeViewport(GraphViewport* viewport);
		virtual void addOverlays();
		virtual NumberAxis numberAxis(); // 0 .. 100
};

#endif
