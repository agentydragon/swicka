#include "candle.h"
#include "mainwindow.h"

#include <QHBoxLayout>
#include <QSplitter>

#include "ohlc.h"
#include "ohlc_provider.h"
#include "ohlc_random_generator.h"
#include "ohlc_standardizer.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    View *view = new View("Top left view");
    scene = new QGraphicsScene;
    view->view()->setScene(scene);
    // view->view()->setScene(new QGraphicsScene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("TODO titulek"));

    loadData();
}

void MainWindow::loadData() {
    memProvider = new OHLCMemoryProvider(QDateTime(QDate(2008, 1, 1)), QDateTime(QDate(2012, 12, 22)), 24 * 60 * 60);
    yl = new YahooLoader("GOOG", YahooLoader::DAY, memProvider);

    qDebug() << "Connecting signals";
    connect(yl, SIGNAL(dataLoaded()), this, SLOT(drawData()));

    qDebug() << "Starting to load data";
    yl->load();

    qDebug() << "Data started to load";
}

void MainWindow::drawData() {

//    OHLCProvider* provider = new OHLCStandardizer(new OHLCRandomGenerator());

    // TODO: chci s tim taky spocitat celkove OHLC tohohle providera, abych z toho udelal velkou svicku, ktera mi rekne, kam mam davat podsvicky
//    QGraphicsScene *scene = view->view()->scene();
    scene->clear();

    // Populate scene
    int nitems = 0;
    int x = 0;
    float candleWidth = 15;
    float graphHeight = 100;
//    OHLCProvider* provider = memProvider;
    OHLCProvider* provider = new OHLCStandardizer(memProvider);
    for (QDateTime start = provider->getMinimum(); start < provider->getMaximum(); start = start.addSecs(provider->getQuantumSeconds())) {
	    OHLC tick;
	    if (provider->tryGetData(start, tick)) {
		    QGraphicsItem *item = new Candle(tick, candleWidth, graphHeight);
		    item->setPos(QPointF(x * candleWidth, 0));
		    scene->addItem(item);
		}

	    x++;

            ++nitems;
    }

    qDebug() << "Scene created.";
  //  view->view()->setScene(scene); // scenes can be shared - maybe use this?
}
