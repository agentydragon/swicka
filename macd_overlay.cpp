#include "macd_overlay.h"

#include <QGraphicsScene>
#include <QPainter>

#include "ohlc_provider.h"

#include <assert.h>

#include "macd_calculator.h"
#include "graph_viewport.h"

void MACDOverlay::timeAxisChanged(TimeAxis timeAxis) {
	axisPair.timeAxis = timeAxis;
}

void MACDOverlay::numberAxisChanged(NumberAxis numberAxis) {
	axisPair.numberAxis = numberAxis;
}

void MACDOverlay::projectionChanged(OHLCProvider* projection) {
	this->projection = projection;
}

MACDOverlay::MACDOverlay(GraphViewport* viewport) {
	this->viewport = viewport;
}

// TODO: settable parameters
void MACDOverlay::insertIntoScene(QGraphicsScene* scene) {
	qDebug() << "Rendering MACD overlay";

	MACDCalculator calculator;
	Graphics* item = new Graphics(axisPair);

	OHLC tick;
	bool gotSomething = false;

	int N = 10;
	// hack
	QDateTime start = projection->getInterval()->minus(axisPair.getMinTime(), N + 1);
	qDebug() << "MACD overlay start:" << start;

	for (QDateTime i = start; i < axisPair.getMaxTime();
			i = projection->getInterval()->firstAfter(i)) {
		if (projection->tryGetData(i, tick)) {
			gotSomething = true; // to skip empty days
		}

		if (gotSomething) {
			calculator << tick;
			MACDCalculator::Entry entry;
			if (calculator.get(entry)) {
				item->data.push_back(QPair<QDateTime, MACDCalculator::Entry>(i, entry));
			}
		}
	}
	scene->addItem(item);

	qDebug() << "Rendered MACD overlay";
}

QRectF MACDOverlay::Graphics::boundingRect() const {
	return QRectF(0, 0, axisPair.getWidth(), axisPair.getHeight());
}

QPainterPath MACDOverlay::Graphics::shape() const {
	// TODO
	QPainterPath path;
	path.addRect(0, 0, axisPair.getWidth(), axisPair.getHeight());
	return path;
}

MACDOverlay::Graphics::Graphics(AxisPair pair): axisPair(pair) {}

// TODO: compose this from basic items rather than a monolith...
void MACDOverlay::Graphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(option);

	// Zero level
	painter->setPen(QPen(Qt::black, 1.0f));
	painter->drawLine(QPointF(0.0f, axisPair.getPriceY(0.0f)), QPointF(axisPair.getWidth(), axisPair.getPriceY(0.0f)));

	for (int i = 1; i < data.size(); i++) {
		float x1 = axisPair.getTimeX(data[i - 1].first),
			x2 = axisPair.getTimeX(data[i].first);

		painter->setPen(QPen(Qt::blue, 1.0f));
		painter->drawLine(
			QPointF(x1, axisPair.getPriceY(data[i - 1].second.macd)),
			QPointF(x2, axisPair.getPriceY(data[i].second.macd))
		);

		painter->setPen(QPen(Qt::red, 1.0f));
		painter->drawLine(
			QPointF(x1, axisPair.getPriceY(data[i - 1].second.signal)),
			QPointF(x2, axisPair.getPriceY(data[i].second.signal))
		);
	}
}

// HACK
/*
GraphViewport* MACDOverlay::internalizedViewport(GraphViewport* viewport) {
	OHLCProvider* projection = viewport->getSourceProjection();
	OHLC tick(0, 0, 0, 0);
	bool gotSomething = false;
	bool gotSomeData = false;
	MACDCalculator calculator;
	for (QDateTime i = viewport->getViewBegin(); i < viewport->getViewEnd();
			i = projection->getInterval()->firstAfter(i)) {
		if (projection->tryGetData(i, tick)) {
			gotSomething = true; // to skip empty days
		}

		if (gotSomething) {
			calculator << tick;
			MACDCalculator::Entry entry;
			if (calculator.get(entry)) {
				tick << entry.macd;
				tick << entry.signal;
				tick << entry.histogram; // TODO: signal je vazeny prumer a histogram je rozdil.
				// TODO: asi neni vubec potreba standardizovat podle neceho jinyho...
				// TODO: histogram ale vlastne bude potrebovat jinou osu, ne?
				gotSomeData = true;
			}
		}
	}

	if (gotSomeData) {
		// TODO: viewport factory? (skala na Y: podle min/max, podle OHLCProvider, ...)
		GraphViewport* v = viewport->duplicate();
		v->explicitYLimits = true;
		v->yLow = tick.low;
		v->yHigh = tick.high;
		return v; // TODO: cache it!
	}

	// XXX
	return viewport;
}
*/
