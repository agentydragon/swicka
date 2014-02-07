#ifndef GRAPH_VIEW_H_INCLUDED
#define GRAPH_VIEW_H_INCLUDED

#include <QGraphicsView>

#include "graph_viewport.h"
#include "graph_ranges.h"

class GraphOverlay;

class GraphView: public QGraphicsView {
	Q_OBJECT

	public:
		GraphView();
		QGraphicsScene* getScene();
	public slots:
		void redraw();
	private:
		QList<GraphOverlay*> overlays;
		GraphViewport* viewport;
		GraphRanges getRanges();
		QGraphicsScene *scene;

	private slots:
		void candleEntered(QDateTime start);
		void candleLeft();

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
