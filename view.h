#ifndef VIEW_H
#define VIEW_H

#include "ohlc_provider.h"
#include "graph_viewport.h"
#include "abstract_graph_view.h"

class QGraphicsScene;
class QLabel;
class QSlider;
class QToolButton;
class GraphOverlay;

class View : public QFrame {
	Q_OBJECT
	public:
		explicit View(const QString &name, QWidget *parent = 0);
		QGraphicsScene* getMainScene();
	private slots:
		void graphViewDataPointHovered(QDateTime time, float price);
		void zoom(QDateTime time, int delta);
	signals:
		void dataPointHovered(QDateTime time, float price);

	public slots:
		void changeDataSource(OHLCProvider* source);
		void resetView(); // reset to default view

	private:
		GraphViewport *viewport;

		OHLCProvider* source;

		AbstractGraphView *mainGraph;
		AbstractGraphView *RSIGraph;
		AbstractGraphView *MACDGraph;
		QToolButton *resetButton;
	public:
		int getViewportWidth(); int getViewportHeight();
};

#endif // VIEW_H
