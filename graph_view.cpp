#include <QWheelEvent>
#include <QDebug>

#include "graph_view.h"

#include "grid.h"
#include "candlesticks_overlay.h"
#include "bollinger_overlay.h"

#include <assert.h>

GraphView::GraphView() {
	m_viewport = NULL;
}

GraphViewport* GraphView::viewport() {
	return m_viewport;
}

void GraphView::internalizeViewport(GraphViewport* viewport) {
	qDebug() << "Internalizing new viewport";
	m_viewport = viewport;

	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));
}

void GraphView::addOverlays() {
	qDebug() << "Adding overlays";
	overlays.push_back(new Grid(viewport()));
	overlays.push_back(new BollingerOverlay(viewport()));
	overlays.push_back(new CandlesticksOverlay(viewport()));

	// connect(candlesticks, SIGNAL(candleEntered(QDateTime)), this, SLOT(candleEntered(QDateTime)));
	// connect(candlesticks, SIGNAL(candleLeft), this, SLOT(candleLeft));
}

void GraphView::candleEntered(QDateTime start) {
	// TODO
	qDebug() << "candle entered:" << start;
}

void GraphView::candleLeft() {
	qDebug() << "candle exited";
}
