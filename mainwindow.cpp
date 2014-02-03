#include "candle.h"
#include "mainwindow.h"

#include <QHBoxLayout>
#include <QSplitter>

#include "ohlc.h"
#include "ohlc_provider.h"
#include "ohlc_random_generator.h"
#include "ohlc_standardizer.h"

#include "grid.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
	view = new View("Top left view");
	scene = new QGraphicsScene;
	view->view()->setScene(scene);
	// view->view()->setScene(new QGraphicsScene);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	setLayout(layout);

	setWindowTitle(tr("TODO titulek"));

	loadData();

	connect(view->view(), SIGNAL(resized()), this, SLOT(drawData()));
}

void MainWindow::loadData() {
	memProvider = new OHLCMemoryProvider(QDateTime(QDate(2008, 1, 1)), QDateTime(QDate(2009, 12, 22)), 24 * 60 * 60);
	yl = new YahooLoader("GOOG", YahooLoader::DAY, memProvider);

	qDebug() << "Connecting signals";
	connect(yl, SIGNAL(dataLoaded()), this, SLOT(drawData()));

	qDebug() << "Starting to load data";
	yl->load();

	qDebug() << "Data started to load";
}

void MainWindow::drawData() {
	OHLCStandardizer* provider = new OHLCStandardizer(memProvider);
		// new OHLCStandardizer(new OHLCRandomGenerator());
	long totalWidth = view->view()->width(), totalHeight = view->view()->height();
	qDebug() << "width" << totalWidth << "height" << totalHeight;

	// TODO: chci s tim taky spocitat celkove OHLC tohohle providera, abych z toho udelal velkou svicku, ktera mi rekne, kam mam davat podsvicky
	scene->clear();

	scene->addItem(new Grid(totalWidth, totalHeight, provider->getSourceClosure(), QList<float>(), QList<float>()));

	// Populate scene
	int nitems = 0;
	int x = 0;

	long candle_count = (provider->getMaximum().toTime_t() - provider->getMinimum().toTime_t()) / provider->getQuantumSeconds();

	float candleWidth = (float)totalWidth / (float)candle_count;
	float graphHeight = totalHeight;
	//    OHLCProvider* provider = memProvider;
	

	for (QDateTime start = provider->getMinimum(); start < provider->getMaximum(); start = start.addSecs(provider->getQuantumSeconds())) {
		OHLC tick;
		if (provider->tryGetData(start, tick)) {
			QGraphicsItem *item = new Candle(tick, candleWidth, graphHeight);
			item->setPos(QPointF(x * candleWidth, 0));
			scene->addItem(item);
//			qDebug() << tick;
		}

		x++;

		++nitems;
	}

	qDebug() << "Scene created.";
	//  view->view()->setScene(scene); // scenes can be shared - maybe use this?
}
