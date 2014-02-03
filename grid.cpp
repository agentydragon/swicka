#include "grid.h"

Grid::Grid(float width, float height, OHLC general, QList<float> major, QList<float> minor) {
	this->general = general;
	this->major = major;
	this->minor = minor;
	this->width = width;
	this->height = height;
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(item);

	painter->setPen(QPen(Qt::black, 1));
	/*
	painter->drawLine(0, 0, 100, 0);
	painter->drawLine(0, 0, 0, 100);
	*/

	for (float i = 0.0f; i <= 1.0f; i += 0.1f) {
		float level = general.low + i * (general.high - general.low);

		painter->setPen(Qt::blue);
		painter->setFont(QFont("Arial", 7));
		painter->drawText(QRect(10, (1.0 - i) * height, 50.0f, 15.0f), Qt::AlignCenter, QString::number(level));
	}
}

QRectF Grid::boundingRect() const {
	return QRectF(0, 0, 100, 100);
}

QPainterPath Grid::shape() const {
	QPainterPath path;
	path.addRect(0, 0, 100, 100);
	return path;
}
