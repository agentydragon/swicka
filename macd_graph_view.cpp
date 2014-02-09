#include <QWheelEvent>
#include <QDebug>

#include "macd_graph_view.h"
#include "macd_overlay.h"
#include "graph_viewport.h"
#include "ohlc_provider.h"

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

NumberAxis MACDGraphView::numberAxis() {
	MACDCalculator calculator;
	OHLC closure(0, 0, 0, 0); // We always need to show the zero axis.
	bool gotSomething = false, gotIt = false;
	OHLC tick;

	int N = 10;
	// hack! duplicate code!
	OHLCProvider* projection = viewport()->getSourceProjection();
	QDateTime start = projection->getInterval()->minus(timeAxis().getMinTime(), N + 1);

	for (QDateTime i = start; i < timeAxis().getMaxTime();
			i = projection->getInterval()->firstAfter(i)) {
		if (projection->tryGetData(i, tick)) {
			gotSomething = true; // to skip empty days
		}

		if (gotSomething) {
			calculator << tick;
			MACDCalculator::Entry entry;
			if (calculator.get(entry)) {
				if (gotIt) {
					closure << entry.macd;
					closure << entry.signal;
					closure << entry.histogram;
				} else {
					float min = fmin(fmin(entry.macd, entry.signal), entry.histogram);
					float max = fmax(fmax(entry.macd, entry.signal), entry.histogram);
					closure = OHLC(min, max, min, max);
					gotIt = true;
				}
			}
		}
	}
	// qDebug() << "MACD closure:" << closure;

	return NumberAxis(closure.low, closure.high, 0.0f, height());
}
