#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

#include "ohlc_provider.h"
#include "graph_ranges.h"
#include "graph_viewport.h"

class QLabel;
class QSlider;
class QToolButton;
class GraphOverlay;

class View;

class GraphicsView : public QGraphicsView {
	Q_OBJECT
	public:
		GraphicsView(View *v) : QGraphicsView(), view(v) { }
	protected:
		void wheelEvent(QWheelEvent *);
		void resizeEvent(QResizeEvent *);
	private:
		View *view;
	signals:
		void resized();
};

class View : public QFrame {
	Q_OBJECT
	public:
		explicit View(const QString &name, QWidget *parent = 0);
		QGraphicsView *view() const;

	public slots:
		void zoom(int level = 1, int x = -1);
		void changeDataSource(OHLCProvider* source);
		void redraw();
		void resetView(); // reset to default view

	private slots:
		void setupMatrix();
		void togglePointerMode();
		void toggleOpenGL();
		void toggleAntialiasing();
		void print();
		void candleEntered(QDateTime start);
		void candleLeft();

	private:
		QList<GraphOverlay*> overlays;

		GraphRanges getRanges();
		GraphViewport *viewport;

		OHLCProvider* source;

		QGraphicsScene *scene;

		QGraphicsView *graphicsView;
		QLabel *label;
		QLabel *label2;
		QToolButton *selectModeButton;
		QToolButton *dragModeButton;
		QToolButton *openGlButton;
		QToolButton *antialiasButton;
		QToolButton *resetButton;
		// QSlider *zoomSlider;
	private slots:
		void notifyOverlaysProjectionChanged();
		void notifyOverlaysRangesChanged();
};

#endif // VIEW_H
