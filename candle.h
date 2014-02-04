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
		Candle(QDateTime time, OHLC ohlc, float width, GraphRanges ranges, GraphEventController* controller);

		QRectF boundingRect() const;
		QPainterPath shape() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

	private:
		QDateTime time;
		GraphEventController* controller;
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

	private:
		GraphRanges ranges;
		float width;
		OHLC ohlc;
};

#endif // CANDLE_H
