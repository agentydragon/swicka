#include <QWheelEvent>
#include <QDebug>

#include "macd_graph_view.h"
#include "macd_overlay.h"
#include "graph_viewport.h"

#include <assert.h>

MACDGraphView::MACDGraphView() {
	m_viewport = NULL;
}

GraphViewport* MACDGraphView::viewport() {
	return m_viewport;
}

void MACDGraphView::internalizeViewport(GraphViewport* viewport) {
	qDebug() << "Internalizing new viewport";
	m_viewport = viewport;

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));
}

void MACDGraphView::addOverlays() {
	qDebug() << "Adding overlays";
	overlays.push_back(new MACDOverlay(viewport()));
}
