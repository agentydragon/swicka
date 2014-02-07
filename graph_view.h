#ifndef GRAPH_VIEW_H_INCLUDED
#define GRAPH_VIEW_H_INCLUDED

#include "abstract_graph_view.h"

class GraphOverlay;

class GraphView: public AbstractGraphView {
	Q_OBJECT

	public:
		GraphView();

	private:
		GraphViewport* m_viewport;
	protected:
		virtual GraphViewport* viewport();
		virtual void internalizeViewport(GraphViewport* viewport);
		virtual void addOverlays();

	private slots:
		void candleEntered(QDateTime start);
		void candleLeft();
};

#endif
