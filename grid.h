#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <QtWidgets>

#include "graph_overlay.h"

class GraphViewport;

class Grid: public GraphOverlay {
	private:
		GraphViewport* viewport;
		GraphRanges ranges;
	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		Grid(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);

		class GridGraphics: public QGraphicsItem {
		public:
			GridGraphics(GraphRanges ranges);
			void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
			QRectF boundingRect() const;
			QPainterPath shape() const;
		private:
			GraphRanges ranges;
			QList<QPair<QDateTime, QString> > xlabels;
			QList<QPair<float, QString> > ylabels;
		};
};

#endif
