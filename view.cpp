#include "view.h"

#include "ohlc_standardizer.h"
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

View::View(const QString &name, QWidget *parent) : QFrame(parent) {
	source = NULL;
	viewport = NULL;

	setFrameStyle(Sunken | StyledPanel);
	mainGraph = new GraphView();
	mainGraph->setParent(this);
	mainGraph->setRenderHint(QPainter::Antialiasing, false);
	mainGraph->setDragMode(QGraphicsView::RubberBandDrag);
	mainGraph->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	mainGraph->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	mainGraph->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	RSIGraph = new RSIGraphView();
	RSIGraph->setParent(this);
	RSIGraph->setRenderHint(QPainter::Antialiasing, false);
	RSIGraph->setDragMode(QGraphicsView::RubberBandDrag);
	RSIGraph->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	RSIGraph->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	RSIGraph->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

	QToolButton* zoomInIcon = new QToolButton;
	QToolButton* zoomOutIcon = new QToolButton;

	// Zoom slider layout
	QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
	zoomSliderLayout->addWidget(zoomInIcon);
	zoomSliderLayout->addWidget(zoomOutIcon);

	resetButton = new QToolButton;
	resetButton->setText(tr("0"));

	// Label layout
	QHBoxLayout *labelLayout = new QHBoxLayout;
	label = new QLabel(name);
	label2 = new QLabel(tr("Pointer Mode"));
	/*
	selectModeButton = new QToolButton;
	selectModeButton->setText(tr("Select"));
	selectModeButton->setCheckable(true);
	selectModeButton->setChecked(true);
	dragModeButton = new QToolButton;
	dragModeButton->setText(tr("Drag"));
	dragModeButton->setCheckable(true);
	dragModeButton->setChecked(false);
	antialiasButton = new QToolButton;
	antialiasButton->setText(tr("Antialiasing"));
	antialiasButton->setCheckable(true);
	antialiasButton->setChecked(false);
	openGlButton = new QToolButton;
	openGlButton->setText(tr("OpenGL"));
	openGlButton->setCheckable(true);
#ifndef QT_NO_OPENGL
	openGlButton->setEnabled(QGLFormat::hasOpenGL());
#else
	openGlButton->setEnabled(false);
#endif
	QButtonGroup *pointerModeGroup = new QButtonGroup(this);
	pointerModeGroup->setExclusive(true);
	pointerModeGroup->addButton(selectModeButton);
	pointerModeGroup->addButton(dragModeButton);
	*/

	labelLayout->addWidget(label);
	labelLayout->addStretch();
	labelLayout->addWidget(label2);
	/*
	labelLayout->addWidget(selectModeButton);
	labelLayout->addWidget(dragModeButton);
	*/
	labelLayout->addStretch();
	/*
	labelLayout->addWidget(antialiasButton);
	labelLayout->addWidget(openGlButton);
	*/

	QGridLayout *topLayout = new QGridLayout;
	topLayout->addLayout(labelLayout, 0, 0);

	QSplitter* splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Vertical);
	splitter->addWidget(mainGraph);
	splitter->addWidget(RSIGraph);

	topLayout->addWidget(splitter, 1, 0);
	topLayout->addLayout(zoomSliderLayout, 1, 1);
	topLayout->addWidget(resetButton, 2, 1);
	setLayout(topLayout);

	connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
	/*
	connect(selectModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
	connect(dragModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
	connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
	connect(openGlButton, SIGNAL(toggled(bool)), this, SLOT(toggleOpenGL()));
	*/
	// connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoom()));
	// connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));

	resetView();

	connect(mainGraph, SIGNAL(dataPointHovered(QDateTime, float)), this, SLOT(graphViewDataPointHovered(QDateTime, float)));
	connect(mainGraph, SIGNAL(dataPointZoomed(QDateTime, int)), this, SLOT(zoom(QDateTime, int)));
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
	} else {
		qDebug() << "calling resetView with no source, doing nothing";
	}
}

/*
void View::togglePointerMode() {
	mainGraph->setDragMode(selectModeButton->isChecked()
			? QGraphicsView::RubberBandDrag
			: QGraphicsView::ScrollHandDrag);
	mainGraph->setInteractive(selectModeButton->isChecked());
}

void View::toggleOpenGL() {
#ifndef QT_NO_OPENGL
	mainGraph->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
}

void View::toggleAntialiasing() {
	mainGraph->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}
*/

void View::zoom(QDateTime center, int delta) {
	if (viewport) {
		viewport->zoom(delta, center);
		mainGraph->notifyOverlaysProjectionChanged();
		mainGraph->notifyOverlaysRangesChanged();

		RSIGraph->notifyOverlaysProjectionChanged();
		RSIGraph->notifyOverlaysRangesChanged();
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
