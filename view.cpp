#include "view.h"

#include "ohlc_standardizer.h"
#include "ohlc_shrinker.h"
#include "ohlc_random_generator.h"

#include "graph_overlay.h"
#include "grid.h"
#include "candlesticks_overlay.h"
#include "bollinger_overlay.h"

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

void GraphicsView::wheelEvent(QWheelEvent *e) {
	// if (e->modifiers() & Qt::ControlModifier) {
	view->zoom(e->delta(), e->x());
	e->accept();
}

void GraphicsView::resizeEvent(QResizeEvent*) {
	emit resized();
}

View::View(const QString &name, QWidget *parent) : QFrame(parent) {
	source = NULL;
	viewport = NULL;

	setFrameStyle(Sunken | StyledPanel);
	graphicsView = new GraphicsView(this);
	graphicsView->setRenderHint(QPainter::Antialiasing, false);
	graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

	QToolButton *zoomInIcon = new QToolButton;
	QToolButton *zoomOutIcon = new QToolButton;

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
	printButton = new QToolButton;
	// printButton->setIcon(QIcon(QPixmap(":/fileprint.png")));

	QButtonGroup *pointerModeGroup = new QButtonGroup;
	pointerModeGroup->setExclusive(true);
	pointerModeGroup->addButton(selectModeButton);
	pointerModeGroup->addButton(dragModeButton);

	labelLayout->addWidget(label);
	labelLayout->addStretch();
	labelLayout->addWidget(label2);
	labelLayout->addWidget(selectModeButton);
	labelLayout->addWidget(dragModeButton);
	labelLayout->addStretch();
	labelLayout->addWidget(antialiasButton);
	labelLayout->addWidget(openGlButton);
	labelLayout->addWidget(printButton);

	QGridLayout *topLayout = new QGridLayout;
	topLayout->addLayout(labelLayout, 0, 0);
	topLayout->addWidget(graphicsView, 1, 0);
	topLayout->addLayout(zoomSliderLayout, 1, 1);
	topLayout->addWidget(resetButton, 2, 1);
	setLayout(topLayout);

	connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
	connect(selectModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
	connect(dragModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
	connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
	connect(openGlButton, SIGNAL(toggled(bool)), this, SLOT(toggleOpenGL()));
	// connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoom()));
	// connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));
	connect(printButton, SIGNAL(clicked()), this, SLOT(print()));

	scene = new QGraphicsScene;
	view()->setScene(scene);

	resetView();

	connect(view(), SIGNAL(resized()), this, SLOT(notifyOverlaysRangesChanged()));
	connect(view(), SIGNAL(resized()), this, SLOT(redraw()));
}

void View::candleEntered(QDateTime start) {
	// TODO
	qDebug() << "candle entered:" << start;
}

void View::candleLeft() {
	qDebug() << "candle exited";
}

QGraphicsView *View::view() const {
	return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView() {
	if (source) {
		// margin: 0.5
		viewport = new GraphViewport(source, 0.5f);
		connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysProjectionChanged()));
		connect(viewport, SIGNAL(changed()), this, SLOT(notifyOverlaysRangesChanged()));
		connect(viewport, SIGNAL(changed()), this, SLOT(redraw()));

		overlays.clear();

		GraphOverlay* grid = new Grid(viewport);
		overlays.push_back(grid);

		GraphOverlay* bollinger = new BollingerOverlay(viewport);
		overlays.push_back(bollinger);

		GraphOverlay* candlesticks = new CandlesticksOverlay(viewport);
		overlays.push_back(candlesticks);
		connect(candlesticks, SIGNAL(candleEntered(QDateTime)), this, SLOT(candleEntered(QDateTime)));
		connect(candlesticks, SIGNAL(candleLeft), this, SLOT(candleLeft));

		notifyOverlaysRangesChanged();
		notifyOverlaysProjectionChanged();

		setupMatrix();
		graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

		redraw(); // Because of newly created viewport.
	} else {
		qDebug() << "calling resetView with no source, doing nothing";
	}
}

void View::setupMatrix() {
	QMatrix matrix; // identity
	graphicsView->setMatrix(matrix);
}

void View::togglePointerMode() {
	graphicsView->setDragMode(selectModeButton->isChecked()
			? QGraphicsView::RubberBandDrag
			: QGraphicsView::ScrollHandDrag);
	graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::toggleOpenGL() {
#ifndef QT_NO_OPENGL
	graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
}

void View::toggleAntialiasing() {
	graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void View::print() {
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
	QPrinter printer;
	QPrintDialog dialog(&printer, this);
	if (dialog.exec() == QDialog::Accepted) {
		QPainter painter(&printer);
		graphicsView->render(&painter);
	}
#endif
}

GraphRanges View::getRanges() {
	assert(viewport);
	GraphRanges ranges = viewport->getRanges();
	ranges.width = view()->width();
	ranges.height = view()->height();
	return ranges;
}

void View::zoom(int level, int x) {
	if (viewport) {
		viewport->zoom(level, getRanges().getXTime(x));
	} else {
		qDebug() << "no viewport, doing nothing";
	}
}

void View::redraw() {
	if (!source || !viewport) {
		qDebug() << "redrawing with NULL source or viewport, drawing nothing.";
		return;
	}

	qDebug() << "view start:" << viewport->getViewBegin() << "view end:" << viewport->getViewEnd();
	qDebug() << "(clearing scene)";
	scene->clear();

	if (source->isEmpty()) {
		qDebug() << "source is empty...";
		return;
	}

	OHLCProvider* projection = viewport->getSourceProjection();
	if (projection->isEmpty()) {
		qDebug() << "drawing empty projection, doing nothing.";
	}

	qDebug() << "== DRAWING OVERLAYS ==";
	for (GraphOverlay* overlay: overlays) {
		overlay->insertIntoScene(scene);
		qDebug() << "===";
	}
	qDebug() << "== OVERLAYS FINISHED ==";
}

void View::changeDataSource(OHLCProvider* source) {
	this->source = source;
	resetView();
}

void View::notifyOverlaysProjectionChanged() {
	if (viewport) {
		qDebug() << "notifying overlays of projection change";
		OHLCProvider* projection = viewport->getSourceProjection();

		for (GraphOverlay* overlay: overlays) {
			overlay->projectionChanged(projection);
		}
	}
}

void View::notifyOverlaysRangesChanged() {
	if (viewport) {
		qDebug() << "notifying overlays of ranges change";
		GraphRanges ranges = getRanges();

		for (GraphOverlay* overlay: overlays) {
			overlay->rangesChanged(ranges);
		}
	}
}
