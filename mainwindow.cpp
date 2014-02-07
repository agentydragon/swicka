#include "mainwindow.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QStatusBar>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileDialog>

#include "ohlc_shrinker.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	view = new View("Top left view");
	view->setParent(this);
	connect(view, SIGNAL(graphPointHover(QDateTime, float)), this, SLOT(graphPointHover(QDateTime, float)));

	setCentralWidget(view);
	setWindowTitle(tr("TODO titulek"));

	createActions();
	createMenus();

	statusBar()->showMessage("Hello world");

	// loadData();
	// doLoadYahooStock("GOOG");
}

void MainWindow::graphPointHover(QDateTime time, float price) {
	QString str = time.toString() + " " + QString::number(price);
	statusBar()->showMessage(str);
}

void MainWindow::createActions() {
	exitAction = new QAction(tr("Zavrit"), this);
	exitAction->setStatusTip(tr("Zavrit program"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	loadYahooStockAction = new QAction(tr("Nahrat akcie z Yahoo"), this);
	connect(loadYahooStockAction, SIGNAL(triggered()), this, SLOT(loadYahooStock()));

	exportImageAction = new QAction(tr("Exportovat obrazek"), this);
	connect(exportImageAction, SIGNAL(triggered()), this, SLOT(exportImage()));
}

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("Soubor"));
	fileMenu->addAction(loadYahooStockAction);
	fileMenu->addAction(exportImageAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void MainWindow::exportImage() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Exportovat obrázek"), "image.png", tr("Obrázky (*.png *.gif *.bmp)"));
	if (filename.isNull()) {
		qDebug() << "no file entered";
		return;
	}

	// TODO: scene must exist

	QImage image(view->getViewportWidth(), view->getViewportHeight(), QImage::Format_RGB16);
	image.fill(Qt::white);

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);
	view->getScene()->render(&painter);
	image.save(filename);
}

void MainWindow::doLoadYahooStock(QString symbol) {
	source = new OHLCMemoryProvider(QDateTime(QDate(2007, 11, 1)), QDateTime(QDate(2009, 12, 22)), new CI::Day);// Day);
	source->setParent(this);

	// TODO: fuj!!!
	yl = new YahooLoader(symbol, YahooLoader::DAY, source);
	yl->setParent(this);

	// TODO: handle errors and so on

	qDebug() << "Connecting signals";
	connect(yl, SIGNAL(dataLoaded()), this, SLOT(drawData()));

	qDebug() << "Starting to load data";
	yl->load();

	qDebug() << "Data started to load";
}

void MainWindow::drawData() {
	// view->changeDataSource(new OHLCShrinker(source, source->getMinimum(), source->getMaximum(), new CI::Month));
	view->changeDataSource(source);
}

void MainWindow::loadYahooStock() {
	// TODO: hezci dialog?
	bool ok;
	QString text = QInputDialog::getText(this, tr("Zadej symbol"), tr("Symbol:"), QLineEdit::Normal, "ADSK", &ok);
	if (ok) {
		if (text.size() > 0) {
			doLoadYahooStock(text);
		} else {
			qDebug() << "nic nezadano...";
		}
	} else {
		qDebug() << "uzivatel nic nezadal...";
	}
}
