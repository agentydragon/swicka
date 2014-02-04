#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <QtWidgets>

#include "graph_ranges.h"

class Grid: public QGraphicsItem {
	public:
		Grid(GraphRanges ranges);
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
		QRectF boundingRect() const;
		QPainterPath shape() const;
	private:
		GraphRanges ranges;
		QList<QPair<QDateTime, QString> > xlabels;
		QList<QPair<float, QString> > ylabels;
};

#endif
