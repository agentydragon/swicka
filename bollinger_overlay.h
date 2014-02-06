#ifndef BOLLINGER_OVERLAY_H_INCLUDED
#define BOLLINGER_OVERLAY_H_INCLUDED

#include "graph_overlay.h"
#include "bollinger_calculator.h"
#include <QGraphicsItem>

class GraphViewport;

class BollingerOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		GraphViewport* viewport;
		GraphRanges ranges;
		OHLCProvider* projection;
		int N, K;

	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);

	public:
		BollingerOverlay(GraphViewport* viewport, int N = 20, int K = 2);
		virtual void insertIntoScene(QGraphicsScene* scene);
		virtual ~BollingerOverlay() {}

	private:
		class Band: public QGraphicsItem {
			private:
				GraphRanges ranges;
			public:
				Band(GraphRanges ranges);
				QList<QPair<QDateTime,BollingerEntry>> data;

				QRectF boundingRect() const;
				QPainterPath shape() const;
				void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
		};
};

#endif
