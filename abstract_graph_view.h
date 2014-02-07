#ifndef ABSTRACT_GRAPH_VIEW_H_INCLUDED
#define ABSTRACT_GRAPH_VIEW_H_INCLUDED

#include <QGraphicsView>

#include "graph_viewport.h"
#include "graph_ranges.h"

class GraphOverlay;

class AbstractGraphView: public QGraphicsView {
	Q_OBJECT

	public:
		AbstractGraphView();
		QGraphicsScene* getScene();
	public slots:
		void redraw();
	protected:
		QList<GraphOverlay*> overlays;
		QGraphicsScene *scene;
		GraphRanges getRanges();

	protected:
		GraphViewport* viewport;
		virtual void internalizeViewport(GraphViewport* viewport) = 0;
		virtual void addOverlays() = 0;

	public slots:
		void notifyOverlaysProjectionChanged();
		void notifyOverlaysRangesChanged();

		void assignViewport(GraphViewport* viewport);

	protected:
		void mouseMoveEvent(QMouseEvent *);
		void wheelEvent(QWheelEvent *);
		void resizeEvent(QResizeEvent *);

	signals:
		void resized();
		void dataPointHovered(QDateTime time, float price);
		void dataPointZoomed(QDateTime time, int delta);
};

#endif
