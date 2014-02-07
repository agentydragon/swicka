#include <QWheelEvent>
#include <QDebug>

#include "rsi_graph_view.h"
#include "rsi_overlay.h"

#include <assert.h>

RSIGraphView::RSIGraphView() {
	viewport = NULL;
}

void RSIGraphView::internalizeViewport(GraphViewport* viewport) {
	qDebug() << "Internalizing new viewport";
	// TODO: internalize in some other way...
	this->viewport = viewport;

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));
}

void RSIGraphView::addOverlays() {
	qDebug() << "Adding overlays";
	overlays.push_back(new RSIOverlay(viewport));
}
