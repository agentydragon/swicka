#ifndef MACD_OVERLAY_H_INCLUDED
#define MACD_OVERLAY_H_INCLUDED

#include "axis_pair.h"
#include "graph_overlay.h"
#include <QList>
#include <QGraphicsItem>

#include "macd_calculator.h"

class GraphViewport;

class MACDOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		GraphViewport* viewport;
		AxisPair axisPair;
		OHLCProvider* projection;

		class Graphics: public QGraphicsItem {
			private:
				AxisPair axisPair;
			public:
				Graphics(AxisPair pair);
				QList<QPair<QDateTime, MACDCalculator::Entry>> data;

				QRectF boundingRect() const;
				QPainterPath shape() const;
				void paint(QPainter *painer, const QStyleOptionGraphicsItem *item, QWidget *widget);
		};
	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis);
		virtual void numberAxisChanged(NumberAxis numberAxis);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		MACDOverlay(GraphViewport* viewport);
		virtual void insertIntoScene(QGraphicsScene* scene);
};

#endif
