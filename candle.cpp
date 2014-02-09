#include "candle.h"

#include <QtWidgets>

Candle::Candle(QDateTime start, QDateTime end, OHLC ohlc, AxisPair axes, GraphEventController* controller):
	axisPair(axes) {
	this->start = start;
	this->end = end;
	this->ohlc = ohlc;
	this->controller = controller;

	setAcceptHoverEvents(true);
	setFlags(QGraphicsItem::ItemIsSelectable);
}

void Candle::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event);
	controller->signalCandleEntered(start);
}

void Candle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event);
	controller->signalCandleLeft();
}

float Candle::getWidth() const {
	float w = axisPair.getTimeX(end) - axisPair.getTimeX(start);
	// qDebug() << "candle width:" << w << "(start=" << start << "end=" << end << ")";
	return w;
}

QRectF Candle::boundingRect() const {
	// TODO
	return QRectF(0, 0, getWidth(), axisPair.getHeight());
}

QPainterPath Candle::shape() const {
	// TODO
	QPainterPath path;
	path.addRect(0, 0, getWidth(), axisPair.getHeight());
	return path;
}

QRectF Candle::getOpenCloseRect() {
	float width = getWidth();
	float yOpen = axisPair.getPriceY(ohlc.open), yClose = axisPair.getPriceY(ohlc.close);
	return QRectF(0.0f, yOpen, width, yClose - yOpen);
}

void Candle::paintHighLow(QPainter *painter) {
	float width = getWidth();
	float penWidth = width / 10;
	if (penWidth < 0.5f) penWidth = 0.5f;
	if (penWidth > 2.0f) penWidth = 2.0f;

	float yLow = axisPair.getPriceY(ohlc.low), yHigh = axisPair.getPriceY(ohlc.high);
	painter->save();
	painter->setPen(QPen(Qt::gray, penWidth));
	painter->drawLine(QPointF(width / 2.0f, yLow), QPointF(width / 2.0f, yHigh));
	painter->restore();
}

void Candle::paintOpenClose(QPainter *painter) {
	float strokeWidth = getWidth() / 10 * 0.7f;
	QRectF rect = getOpenCloseRect();

	if (strokeWidth > 0.5f) {
		painter->setPen(QPen(Qt::gray, strokeWidth));
		painter->drawRect(rect);
	}

	QColor fillColor = ohlc.isUp() ? QColor(0, 255, 0) : QColor(255, 0, 0);
	painter->fillRect(rect, QBrush(fillColor));
}

void Candle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);

	if (option->state & QStyle::State_Selected) {
		painter->fillRect(QRect(0, 0, getWidth(), axisPair.getHeight()), QBrush(QColor(200, 200, 200)));
	}

	paintHighLow(painter);
	paintOpenClose(painter);
}

void Candle::setAxisPair(AxisPair axisPair) {
	this->axisPair = axisPair;
}

QDateTime Candle::getStart() {
	return start;
}
