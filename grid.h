#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <QtWidgets>

#include "ohlc.h"

class Grid: public QGraphicsItem {
	public:
		Grid(float width, float height, OHLC general);
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
		QRectF boundingRect() const;
		QPainterPath shape() const;
	private:
		float width, height;
		OHLC general;
		QList<float> labels;
};

#endif
