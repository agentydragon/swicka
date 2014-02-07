#ifndef RSI_OVERLAY_H_INCLUDED
#define RSI_OVERLAY_H_INCLUDED

// TODO: scena by se nemela sama od sebe cela rozbijet, ne?

#include "graph_overlay.h"
#include "graph_event_controller.h"
#include <QList>
#include <QGraphicsItem>

class GraphViewport;

class RSIOverlay: public GraphOverlay {
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
				QList<QPair<QDateTime, float>> data;

				QRectF boundingRect() const;
				QPainterPath shape() const;
				void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
		};
	public slots:
		virtual void rangesChanged(GraphRanges ranges);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		RSIOverlay(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);
};

#endif
