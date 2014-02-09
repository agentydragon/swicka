#include <QWheelEvent>
#include <QDebug>

#include "rsi_graph_view.h"
#include "rsi_overlay.h"
#include "graph_viewport.h"

#include <assert.h>

RSIGraphView::RSIGraphView() {
	m_viewport = NULL;
}

GraphViewport* RSIGraphView::viewport() {
	return m_viewport;
}

void RSIGraphView::internalizeViewport(GraphViewport* viewport) {
	qDebug() << "Internalizing new viewport";
	m_viewport = viewport;

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));
}

void RSIGraphView::addOverlays() {
	qDebug() << "Adding RSI overlay";
	overlays.push_back(new RSIOverlay());
}

NumberAxis RSIGraphView::numberAxis() {
	return NumberAxis(0.0f, 100.0f, 0.0f, height());
}
