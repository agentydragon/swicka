#include "candle.h"

#include <QtWidgets>

Candle::Candle(QDateTime start, QDateTime end, OHLC ohlc, GraphRanges ranges, GraphEventController* controller) {
	this->start = start;
	this->end = end;
	this->ohlc = ohlc;
	this->ranges = ranges;
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
	// TODO
	return ranges.getTimeSpanWidth(end.toTime_t() - start.toTime_t());
}

QRectF Candle::boundingRect() const {
	return QRectF(0, 0, getWidth(), ranges.height);
}

QPainterPath Candle::shape() const {
	QPainterPath path;
	path.addRect(0, 0, getWidth(), ranges.height);
	return path;
}

void Candle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);

	float width = getWidth();
	float penWidth = width / 10;
	if (penWidth < 0.5f) penWidth = 0.5f;
	if (penWidth > 2.0f) penWidth = 2.0f;

	if (option->state & QStyle::State_Selected) {
		penWidth *= 2.0f;
		painter->fillRect(QRect(0, 0, width, ranges.height), QBrush(QColor(200, 200, 200)));
	}

	painter->setPen(QPen(Qt::gray, penWidth));

	float yLow = ranges.getPriceY(ohlc.low), yHigh = ranges.getPriceY(ohlc.high);
	painter->drawLine(QPointF(width / 2.0f, yLow), QPointF(width / 2.0f, yHigh));

	float yOpen = ranges.getPriceY(ohlc.open), yClose = ranges.getPriceY(ohlc.close);

	QRectF rect(0.0f, yOpen, width, yClose - yOpen);
	QColor fillColor = ohlc.isUp() ? QColor(0, 255, 0) : QColor(255, 0, 0);
	painter->fillRect(rect, QBrush(fillColor));

	float strokeWidth = penWidth * 0.7f;
	if (strokeWidth > 0.5f) {
		painter->setPen(QPen(Qt::gray, strokeWidth));
		painter->drawRect(rect);
	}

	/*
	   if (lod >= 1) {
	   painter->setPen(QPen(Qt::gray, 1));
	   painter->drawLine(94, 53, 94, 15);
	   painter->setPen(QPen(Qt::black, 0));
	   }

	// Draw lines
	QVarLengthArray<QLineF, 36> lines;
	if (lod >= 0.5) {
	for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
	lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
	lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
	}
	}
	if (lod >= 0.4) {
	const QLineF lineData[] = {
	QLineF(45, 35, 55, 35)
	};
	lines.append(lineData, 6);
	}
	painter->drawLines(lines.data(), lines.size());
	*/
}

void Candle::setRanges(GraphRanges ranges) {
	this->ranges = ranges;
}

QDateTime Candle::getStart() {
	return start;
}
