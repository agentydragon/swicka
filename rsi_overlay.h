#ifndef RSI_OVERLAY_H_INCLUDED
#define RSI_OVERLAY_H_INCLUDED

// TODO: scena by se nemela sama od sebe cela rozbijet, ne?

#include "axis_pair.h"
#include "graph_overlay.h"
#include <QList>
#include <QGraphicsItem>

class RSIOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		AxisPair axisPair;
		OHLCProvider* projection;

		class Graphics: public QGraphicsItem {
			private:
				AxisPair axisPair;
			public:
				Graphics(AxisPair pair);
				QList<QPair<QDateTime, float>> data;

				QRectF boundingRect() const;
				QPainterPath shape() const;
				void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
		};
	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis);
		virtual void numberAxisChanged(NumberAxis numberAxis);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		RSIOverlay();
		virtual void insertIntoScene(QGraphicsScene* scene);
};

#endif
