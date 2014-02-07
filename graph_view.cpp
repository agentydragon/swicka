#include <QWheelEvent>
#include <QDebug>

#include "graph_view.h"
#include "graph_overlay.h"

#include "grid.h"
#include "candlesticks_overlay.h"
#include "bollinger_overlay.h"

#include <assert.h>

void GraphView::mouseMoveEvent(QMouseEvent *e) {
	GraphRanges ranges = getRanges();
	QDateTime time = ranges.getXTime(e->x());
	float price = ranges.getYPrice(e->y());
	emit dataPointHovered(time, price);
	e->accept();
}

void GraphView::wheelEvent(QWheelEvent *e) {
	// if (e->modifiers() & Qt::ControlModifier) {
	emit dataPointZoomed(getRanges().getXTime(e->x()), e->delta());
	e->accept();
}

void GraphView::resizeEvent(QResizeEvent*) {
	emit resized();
}

GraphView::GraphView() {
	scene = new QGraphicsScene;
	setScene(scene);
	scene->setParent(this);

	viewport = NULL;

	connect(this, SIGNAL(resized()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(this, SIGNAL(resized()), this, SLOT(redraw()));
}

void GraphView::assignViewport(GraphViewport* viewport) {
	assert(viewport);
	qDebug() << "Assigning new viewport:" << viewport;

	setMouseTracking(true);
	overlays.clear(); // TODO: destroy...

	this->viewport = viewport;

	GraphOverlay* grid = new Grid(viewport);
	overlays.push_back(grid);

	GraphOverlay* bollinger = new BollingerOverlay(viewport);
	overlays.push_back(bollinger);

	GraphOverlay* candlesticks = new CandlesticksOverlay(viewport);
	overlays.push_back(candlesticks);
	// connect(candlesticks, SIGNAL(candleEntered(QDateTime)), this, SLOT(candleEntered(QDateTime)));
	// connect(candlesticks, SIGNAL(candleLeft), this, SLOT(candleLeft));

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));

	notifyOverlaysProjectionChanged();
	notifyOverlaysRangesChanged();
	redraw(); // Because of newly created viewport.
}

void GraphView::notifyOverlaysProjectionChanged() {
	if (viewport) {
		qDebug() << "notifying overlays of projection change";
		OHLCProvider* projection = viewport->getSourceProjection();

		for (GraphOverlay* overlay: overlays) {
			overlay->projectionChanged(projection);
		}
	}
}

void GraphView::notifyOverlaysRangesChanged() {
	if (viewport) {
		qDebug() << "notifying overlays of ranges change";
		GraphRanges ranges = getRanges();

		for (GraphOverlay* overlay: overlays) {
			overlay->rangesChanged(ranges);
		}
	}
}

GraphRanges GraphView::getRanges() {
	assert(viewport);
	GraphRanges ranges = viewport->getRanges();
	ranges.width = width();
	ranges.height = height();
	return ranges;
}

void GraphView::redraw() {
	if (!viewport) {
		qDebug() << "redrawing with NULL viewport, drawing nothing.";
		return;
	}

	qDebug() << "Redrawing. Viewport from:" << viewport->getViewBegin() << "to:" << viewport->getViewEnd();
	scene->clear();

	/*
	if (source->isEmpty()) {
		qDebug() << "source is empty...";
		return;
	}
	*/

	// OHLCProvider* projection = viewport->getSourceProjection();
	/*
	if (projection->isEmpty()) {
		qDebug() << "drawing empty projection, doing nothing.";
	}
	*/

	qDebug() << "== DRAWING OVERLAYS ==";
	for (GraphOverlay* overlay: overlays) {
		overlay->insertIntoScene(scene);
		qDebug() << "===";
	}
	qDebug() << "== OVERLAYS FINISHED ==";
}

void GraphView::candleEntered(QDateTime start) {
	// TODO
	qDebug() << "candle entered:" << start;
}

void GraphView::candleLeft() {
	qDebug() << "candle exited";
}

QGraphicsScene* GraphView::getScene() {
	return scene;
}
