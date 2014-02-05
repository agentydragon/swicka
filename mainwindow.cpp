#include "mainwindow.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QStatusBar>
#include <QLineEdit>
#include <QInputDialog>

#include "ohlc_shrinker.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	view = new View("Top left view");

	setCentralWidget(view);
	setWindowTitle(tr("TODO titulek"));

	createActions();
	createMenus();

	statusBar()->showMessage("Hello world");

	// loadData();
	// doLoadYahooStock("GOOG");
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

void MainWindow::doLoadYahooStock(QString symbol) {
	source = new OHLCMemoryProvider(QDateTime(QDate(2007, 11, 1)), QDateTime(QDate(2009, 12, 22)), new CI::Day);// Day);
	yl = new YahooLoader(symbol, YahooLoader::DAY, source);

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
