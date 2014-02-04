#include "grid.h"
#include "grid_labeler.h"

Grid::Grid(GraphRanges ranges) {
	this->ranges = ranges;

	// TODO fuj
	GridLabeler().generateYLabels(ranges.priceLow, ranges.priceHigh, ylabels);
	GridLabeler().generateXLabels(ranges.start, ranges.end, xlabels);
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(item);

	painter->setFont(QFont("Arial", 7));

	for (QPair<float, QString> label: ylabels) {
		float y = ranges.getPriceY(label.first);

		painter->setPen(Qt::blue);
		painter->drawText(QRect(10, y, 50.0f, 15.0f), Qt::AlignCenter, label.second);

		painter->setPen(Qt::black);
		painter->drawLine(0.0f, y, ranges.width, y);
	}

	for (QPair<QDateTime, QString> label: xlabels) {
		float x = ranges.getTimeX(label.first);

		painter->setPen(Qt::red);
		painter->drawText(QRect(x, 10, x + 100.0f, 20.0f), Qt::AlignCenter, label.second);

		painter->setPen(Qt::gray);
		painter->drawLine(x, 0.0, x, ranges.height);
	}
}

QRectF Grid::boundingRect() const {
	return QRectF(0, 0, ranges.width, ranges.height);
}

QPainterPath Grid::shape() const {
	QPainterPath path;
	path.addRect(0, 0, ranges.width, ranges.height);
	return path;
}
