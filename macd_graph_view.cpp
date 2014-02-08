#include <QWheelEvent>
#include <QDebug>

#include "macd_graph_view.h"
#include "macd_overlay.h"

#include <assert.h>

MACDGraphView::MACDGraphView() {
	m_viewport = NULL;
}

GraphViewport* MACDGraphView::viewport() {
	if (m_viewport) {
		// TODO: mozna odebrat zachazeni s Y z GraphViewport?
		GraphViewport* v = MACDOverlay::internalizedViewport(m_viewport);
		return v; // TODO: cache it!
	} else return NULL;
}

void MACDGraphView::internalizeViewport(GraphViewport* viewport) {
	qDebug() << "Internalizing new viewport";
	// TODO: internalize in some other way...
	m_viewport = viewport;

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));
}

void MACDGraphView::addOverlays() {
	qDebug() << "Adding overlays";
	overlays.push_back(new MACDOverlay(viewport()));
}
