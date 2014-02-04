#include "mainwindow.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	view = new View("Top left view");

	setCentralWidget(view);
	setWindowTitle(tr("TODO titulek"));

	createActions();
	createMenus();

	statusBar()->showMessage("Hello world");

	loadData();
}

void MainWindow::createActions() {
	exitAction = new QAction(tr("Zavrit"), this);
	exitAction->setStatusTip(tr("Zavrit program"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	loadYahooStockAction = new QAction(tr("Nahrat akcie z Yahoo"), this);
	connect(loadYahooStockAction, SIGNAL(triggered()), this, SLOT(loadYahooStock()));
}

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("Soubor"));
	fileMenu->addAction(loadYahooStockAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void MainWindow::loadData() {
	source = new OHLCMemoryProvider(QDateTime(QDate(1990, 1, 1)), QDateTime(QDate(2009, 12, 22)), 24 * 60 * 60);
	yl = new YahooLoader("ADSK", YahooLoader::DAY, source);

	qDebug() << "Connecting signals";
	connect(yl, SIGNAL(dataLoaded()), this, SLOT(drawData()));

	qDebug() << "Starting to load data";
	yl->load();

	qDebug() << "Data started to load";
}

void MainWindow::drawData() {
	view->changeDataSource(source);
}

void MainWindow::loadYahooStock() {
	qDebug() << "load yahoo stock...";
}
