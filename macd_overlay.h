#ifndef MACD_OVERLAY_H_INCLUDED
#define MACD_OVERLAY_H_INCLUDED

#include "graph_overlay.h"
#include <QList>
#include <QGraphicsItem>

#include "macd_calculator.h"

class GraphViewport;

class MACDOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		GraphViewport* viewport;
		GraphRanges ranges;
		OHLCProvider* projection;

		class Graphics: public QGraphicsItem {
			private:
				GraphRanges ranges;
			public:
				Graphics(GraphRanges ranges);
				QList<QPair<QDateTime, MACDCalculator::Entry>> data;

				QRectF boundingRect() const;
				QPainterPath shape() const;
				void paint(QPainter *painer, const QStyleOptionGraphicsItem *item, QWidget *widget);
		};
	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		MACDOverlay(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);

		// HACK
		static GraphViewport* internalizedViewport(GraphViewport* viewport);
};

#endif
