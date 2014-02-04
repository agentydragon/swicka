#include "grid.h"
#include "grid_labeler.h"

Grid::Grid(float width, float height, OHLC general) {
	this->general = general;
	this->width = width;
	this->height = height;

	GridLabeler().generateLabels(general.low, general.high, labels);
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(item);

	painter->setPen(QPen(Qt::black, 1));
	/*
	painter->drawLine(0, 0, 100, 0);
	painter->drawLine(0, 0, 0, 100);
	*/

	painter->setFont(QFont("Arial", 7));

	for (float label: labels) {
		float level = ((label - general.low) / (general.high - general.low));
		float y = (1.0f - level) * height;

		painter->setPen(Qt::blue);
		painter->drawText(QRect(10, y, 50.0f, 15.0f), Qt::AlignCenter, QString::number(label));

		painter->setPen(Qt::black);
		painter->drawLine(0.0f, y, width, y);
	}
}

QRectF Grid::boundingRect() const {
	return QRectF(0, 0, width, height);
}

QPainterPath Grid::shape() const {
	QPainterPath path;
	path.addRect(0, 0, width, height);
	return path;
}
