#ifndef MACD_GRAPH_VIEW_H_INCLUDED
#define MACD_GRAPH_VIEW_H_INCLUDED

#include "abstract_graph_view.h"

class GraphOverlay;

class MACDGraphView: public AbstractGraphView {
	Q_OBJECT

	public:
		MACDGraphView();

	private:
		GraphViewport* m_viewport;

	protected:
		virtual GraphViewport* viewport();
		virtual void internalizeViewport(GraphViewport* viewport);
		virtual void addOverlays();
		virtual NumberAxis numberAxis(); // min..max of MACD
};

#endif
