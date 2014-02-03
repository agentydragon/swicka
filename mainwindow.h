#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "yahoo_loader.h"
#include "ohlc_memory_provider.h"
#include "view.h"

class QGraphicsScene;
class QSplitter;

class MainWindow : public QWidget {
	Q_OBJECT
	public:
		MainWindow(QWidget *parent = 0);

	private:
		void setupMatrix();
		void loadData();

		OHLCMemoryProvider* source;
		YahooLoader* yl;

		View *view;

	public slots:
		void drawData();
};

#endif // MAINWINDOW_H
