#include "candle.h"

#include <QtWidgets>

// Expected to be standardized to (1.0) == min-max of whole scene
Candle::Candle(QDateTime time, OHLC ohlc, float width, GraphRanges ranges, GraphEventController* controller) {
	this->time = time;
	this->ohlc = ohlc;
	this->width = width;
	this->ranges = ranges;
	this->controller = controller;

	setAcceptHoverEvents(true);
}

void Candle::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event);
	controller->signalCandleEntered(time);
}

void Candle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	Q_UNUSED(event);
	controller->signalCandleLeft();
}

QRectF Candle::boundingRect() const {
	return QRectF(0, 0, width, ranges.height);
}

QPainterPath Candle::shape() const {
	QPainterPath path;
	path.addRect(0, 0, width, ranges.height);
	return path;
}

void Candle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);

	float penWidth = 0.3f;
	if (option->state & QStyle::State_Selected)
		penWidth += 0.3f;

	// background of graph
	//painter->fillRect(QRect(0, 0, width, height), QBrush(QColor(200, 200, 200)));

	painter->setPen(QPen(Qt::gray, penWidth));

	float yLow = ranges.getPriceY(ohlc.low), yHigh = ranges.getPriceY(ohlc.high);
	painter->drawLine(QPointF(width / 2.0f, yLow), QPointF(width / 2.0f, yHigh));

	float yOpen = ranges.getPriceY(ohlc.open), yClose = ranges.getPriceY(ohlc.close);
	QColor fillColor = ohlc.isUp() ? QColor(0, 255, 0) : QColor(255, 0, 0);
	painter->fillRect(QRectF(0.0f, yOpen, width, yClose - yOpen), QBrush(fillColor));

	/*
	   if (lod >= 1) {
	   painter->setPen(QPen(Qt::gray, 1));
	   painter->drawLine(94, 53, 94, 15);
	   painter->setPen(QPen(Qt::black, 0));
	   }

	// Draw lines
	QVarLengthArray<QLineF, 36> lines;
	if (lod >= 0.5) {
	for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2)) {
	lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
	lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
	}
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
