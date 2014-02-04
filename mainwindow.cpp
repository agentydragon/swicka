#include "mainwindow.h"

#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
	view = new View("Top left view");

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	setLayout(layout);

	setWindowTitle(tr("TODO titulek"));

	loadData();
}

void MainWindow::loadData() {
	source = new OHLCMemoryProvider(QDateTime(QDate(2008, 1, 1)), QDateTime(QDate(2009, 12, 22)), 24 * 60 * 60);
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
