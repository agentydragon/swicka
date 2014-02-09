#include "abstract_graph_view.h"

#include <QWheelEvent>
#include <QDebug>

#include "graph_view.h"
#include "graph_overlay.h"
#include "graph_viewport.h"

#include <assert.h>

void AbstractGraphView::mouseMoveEvent(QMouseEvent *e) {
	if (viewport()) {
		QDateTime time = timeAxis().coordToTime(e->x());
		float price = numberAxis().coordToNum(e->y());
		emit dataPointHovered(time, price);
		e->accept();
	}
}

void AbstractGraphView::wheelEvent(QWheelEvent *e) {
	if (viewport()) {
		// if (e->modifiers() & Qt::ControlModifier) {
		emit dataPointZoomed(timeAxis().coordToTime(e->x()), e->delta());
		e->accept();
	}
}

void AbstractGraphView::resizeEvent(QResizeEvent*) {
	emit resized();
}

AbstractGraphView::AbstractGraphView() {
	scene = new QGraphicsScene;
	setScene(scene);
	scene->setParent(this);

	setMouseTracking(true);

	connect(this, SIGNAL(resized()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(this, SIGNAL(resized()), this, SLOT(redraw()));
}

void AbstractGraphView::assignViewport(GraphViewport* viewport) {
	assert(viewport);
	qDebug() << "Assigning new viewport:" << viewport;

	for (GraphOverlay* g: overlays) delete g;
	overlays.clear(); // TODO: destroy...

	internalizeViewport(viewport);
	addOverlays();

	notifyOverlaysProjectionChanged();
	notifyOverlaysRangesChanged();
	redraw(); // Because of newly created viewport.
}

void AbstractGraphView::notifyOverlaysProjectionChanged() {
	if (viewport()) {
		qDebug() << "notifying overlays of projection change";
		OHLCProvider* projection = viewport()->getSourceProjection();

		for (GraphOverlay* overlay: overlays) {
			overlay->projectionChanged(projection);
		}
	}
}

void AbstractGraphView::notifyOverlaysRangesChanged() {
	if (viewport()) {
		qDebug() << "notifying overlays of ranges change";
		TimeAxis t = timeAxis();
		NumberAxis n = numberAxis();

		for (GraphOverlay* overlay: overlays) {
			overlay->timeAxisChanged(t);
			overlay->numberAxisChanged(n);
		}
	}
}

TimeAxis AbstractGraphView::timeAxis() {
	return TimeAxis(viewport()->getTimeRange(), 0.0f, width());
}

NumberAxis AbstractGraphView::numberAxis() {
	return NumberAxis(viewport()->getClosureNumberRange(), 0.0f, height());
}

void AbstractGraphView::redraw() {
	if (!viewport()) {
		qDebug() << "redrawing with NULL viewport, drawing nothing.";
		return;
	}

	qDebug() << "Redrawing. Viewport from:" << viewport()->getViewBegin() << "to:" << viewport()->getViewEnd();
	scene->clear();

	qDebug() << "== DRAWING OVERLAYS ==";
	for (GraphOverlay* overlay: overlays) {
		overlay->insertIntoScene(scene);
		qDebug() << "===";
	}
	qDebug() << "== OVERLAYS FINISHED ==";
}

QGraphicsScene* AbstractGraphView::getScene() {
	return scene;
}
