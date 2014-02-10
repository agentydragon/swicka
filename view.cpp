#include "view.h"

#include "ohlc_shrinker.h"
#include "ohlc_random_generator.h"

#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif
#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <qmath.h>

#include <assert.h>

#include "graph_view.h"
#include "rsi_graph_view.h"
#include "macd_graph_view.h"

View::View(const QString &name, QWidget *parent) : QFrame(parent) {
	source = NULL;
	viewport = NULL;

	setFrameStyle(Sunken | StyledPanel);
	mainGraph = new GraphView();
	mainGraph->setParent(this);

	RSIGraph = new RSIGraphView();
	RSIGraph->setParent(this);

	MACDGraph = new MACDGraphView();
	MACDGraph->setParent(this);

	resetButton = new QToolButton;
	resetButton->setText(tr("Reset"));

	QSplitter* splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Vertical);
	splitter->addWidget(mainGraph);
	splitter->addWidget(RSIGraph);
	splitter->addWidget(MACDGraph);

	QGridLayout *topLayout = new QGridLayout;
	topLayout->addWidget(splitter, 1, 0);
	topLayout->addWidget(resetButton, 2, 1);
	setLayout(topLayout);

	connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));

	resetView();

	connect(mainGraph, SIGNAL(dataPointHovered(QDateTime, float)), this, SLOT(graphViewDataPointHovered(QDateTime, float)));
	connect(mainGraph, SIGNAL(dataPointZoomed(QDateTime, int)), this, SLOT(zoom(QDateTime, int)));
	connect(RSIGraph, SIGNAL(dataPointZoomed(QDateTime, int)), this, SLOT(zoom(QDateTime, int)));
	connect(MACDGraph, SIGNAL(dataPointZoomed(QDateTime, int)), this, SLOT(zoom(QDateTime, int)));
}

void View::graphViewDataPointHovered(QDateTime time, float price) {
	emit dataPointHovered(time, price);
}

QGraphicsScene* View::getMainScene() {
	return mainGraph->getScene();
}

void View::resetView() {
	if (source) {
		viewport->reset();
		mainGraph->assignViewport(viewport);
		RSIGraph->assignViewport(viewport);
		MACDGraph->assignViewport(viewport);
	} else {
		qDebug() << "calling resetView with no source, doing nothing";
	}
}

void View::zoom(QDateTime center, int delta) {
	if (viewport) {
		viewport->zoom(delta, center);
		mainGraph->notifyOverlaysProjectionChanged();
		mainGraph->notifyOverlaysRangesChanged();

		RSIGraph->notifyOverlaysProjectionChanged();
		RSIGraph->notifyOverlaysRangesChanged();

		MACDGraph->notifyOverlaysProjectionChanged();
		MACDGraph->notifyOverlaysRangesChanged();
	} else {
		qDebug() << "no viewport, doing nothing";
	}
}

void View::changeDataSource(OHLCProvider* source) {
	this->source = source;
	if (viewport) delete viewport;

	// margin: 0.5
	viewport = new GraphViewport(source, 0.5f);
	viewport->setParent(this);

	resetView();
}

int View::getViewportWidth() { return mainGraph->width(); }
int View::getViewportHeight() { return mainGraph->height(); }
