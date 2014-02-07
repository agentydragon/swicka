#include <QWheelEvent>
#include <QDebug>

#include "rsi_graph_view.h"
#include "rsi_overlay.h"

#include <assert.h>

RSIGraphView::RSIGraphView() {
	m_viewport = NULL;
}

GraphViewport* RSIGraphView::viewport() {
	if (m_viewport) {
		GraphViewport* v = m_viewport->duplicate();
		v->explicitYLimits = true;
		v->yLow = 0;
		v->yHigh = 100;
		return v; // TODO: cache it!
	} else return NULL;
}

void RSIGraphView::internalizeViewport(GraphViewport* viewport) {
	qDebug() << "Internalizing new viewport";
	// TODO: internalize in some other way...
	m_viewport = viewport;

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));
}

void RSIGraphView::addOverlays() {
	qDebug() << "Adding overlays";
	overlays.push_back(new RSIOverlay(viewport()));
}
