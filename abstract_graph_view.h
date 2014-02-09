#ifndef ABSTRACT_GRAPH_VIEW_H_INCLUDED
#define ABSTRACT_GRAPH_VIEW_H_INCLUDED

#include <QGraphicsView>

#include "time_axis.h"
#include "number_axis.h"

class GraphViewport;
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

	protected:
		virtual GraphViewport* viewport() = 0;
		virtual void internalizeViewport(GraphViewport* viewport) = 0;
		virtual void addOverlays() = 0;

		virtual TimeAxis timeAxis(); // Def. impl.
		virtual NumberAxis numberAxis(); // Def. impl.: use ranges from viewport (implicit)

	public slots:
		void notifyOverlaysProjectionChanged();
		virtual void notifyOverlaysRangesChanged();

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
