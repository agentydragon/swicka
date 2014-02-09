#ifndef CANDLE_H
#define CANDLE_H

#include <QColor>
#include <QGraphicsItem>

#include "ohlc.h"
#include "graph_event_controller.h"
#include "axis_pair.h"

class Candle : public QGraphicsItem {
	public:
		// TODO: nebyl by lepsi decimal?
		Candle(QDateTime start, QDateTime end, OHLC ohlc, AxisPair axisPair, GraphEventController* controller);

		QRectF boundingRect() const;
		QPainterPath shape() const;

	private:
		void paintHighLow(QPainter *painter);
		void paintOpenClose(QPainter *painter);
		QRectF getOpenCloseRect();

	public:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

	private:
		QDateTime start, end;
		GraphEventController* controller;
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

		AxisPair axisPair;
		OHLC ohlc;

	public:
		void setAxisPair(AxisPair axisPair);
		float getWidth() const;
		QDateTime getStart();
};

#endif
