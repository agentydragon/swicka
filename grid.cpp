#include "grid.h"
#include "grid_labeler.h"

Grid::GridGraphics::GridGraphics(AxisPair pair, bool drawTimeLabels): axisPair(pair) {
	this->drawTimeLabels = drawTimeLabels;
	GridLabeler().generateYLabels(axisPair.numberAxis.getMinNum(), axisPair.numberAxis.getMaxNum(), ylabels);
	GridLabeler().generateXLabels(axisPair.timeAxis.getMinTime(), axisPair.timeAxis.getMaxTime(), xlabels);
}

void Grid::GridGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(item);

	painter->setFont(QFont("Arial", 7));

	painter->setPen(QPen(Qt::black, 1.0f));
	painter->drawText(QRect(3, axisPair.numberAxis.getCenterCoord(), 50.0f, 15.0f), Qt::AlignLeft, axisPair.numberAxis.getLabel());

	float timeLabelsX = axisPair.getMinTimeX() - 50.0f;

	QPen gridPen = QPen(Qt::gray, 0.5f);
	for (QPair<float, QString> label: ylabels) {
		float y = axisPair.getPriceY(label.first);

		painter->setPen(Qt::blue);
		painter->drawText(QRect(timeLabelsX, y, 50.0f, 15.0f), Qt::AlignLeft, label.second);

		painter->setPen(gridPen);
		painter->drawLine(QPointF(axisPair.getMinTimeX(), y), QPointF(axisPair.getMaxTimeX(), y));
	}

	for (QPair<QDateTime, QString> label: xlabels) {
		float x = axisPair.getTimeX(label.first);

		if (drawTimeLabels) {
			painter->setPen(Qt::red);
			painter->drawText(QRect(x, 10, 50.0f, 20.0f), Qt::AlignLeft, label.second);
		}

		painter->setPen(gridPen);
		painter->drawLine(QPointF(x, axisPair.getMinPriceY()), QPointF(x, axisPair.getMaxPriceY()));
	}
}

QRectF Grid::GridGraphics::boundingRect() const {
	return QRectF(0, 0, axisPair.getWidth(), axisPair.getHeight());
}

QPainterPath Grid::GridGraphics::shape() const {
	QPainterPath path;
	path.addRect(0, 0, axisPair.getWidth(), axisPair.getHeight());
	return path;
}

Grid::Grid(bool drawTimeLabels) {
	this->drawTimeLabels = drawTimeLabels;
}

void Grid::insertIntoScene(QGraphicsScene* scene) {
	scene->addItem(new GridGraphics(axisPair, drawTimeLabels));
}

void Grid::numberAxisChanged(NumberAxis numberAxis) {
	qDebug() << "grid notified of number axis change";
	axisPair.numberAxis = numberAxis;
}

void Grid::timeAxisChanged(TimeAxis timeAxis) {
	qDebug() << "grid notified of time axis change";
	axisPair.timeAxis = timeAxis;
}

void Grid::projectionChanged(OHLCProvider* projection) {
	(void) projection;
}
