#ifndef CANDLE_H
#define CANDLE_H

#include <QColor>
#include <QGraphicsItem>

#include "ohlc.h"
#include "graph_event_controller.h"
#include "graph_ranges.h"

class Candle : public QGraphicsItem {
	public:
		// TODO: nebyl by lepsi decimal?
		Candle(QDateTime start, QDateTime end, OHLC ohlc, GraphRanges ranges, GraphEventController* controller);

		QRectF boundingRect() const;
		QPainterPath shape() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

	private:
		QDateTime start, end;
		GraphEventController* controller;
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

		GraphRanges ranges;
		OHLC ohlc;

	public:
		void setRanges(GraphRanges ranges);
		float getWidth() const;
		QDateTime getStart();
};

#endif // CANDLE_H
