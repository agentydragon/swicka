#ifndef BOLLINGER_OVERLAY_H_INCLUDED
#define BOLLINGER_OVERLAY_H_INCLUDED

#include "graph_overlay.h"
#include "bollinger_calculator.h"
#include "axis_pair.h"
#include <QGraphicsItem>

class BollingerOverlay: public GraphOverlay {
	Q_OBJECT

	private:
		OHLCProvider* projection;
		int N, K;
		AxisPair axisPair;

	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis);
		virtual void numberAxisChanged(NumberAxis numberAxis);
		virtual void projectionChanged(OHLCProvider* projection);

	public:
		BollingerOverlay(int N = 20, int K = 2);
		virtual void insertIntoScene(QGraphicsScene* scene);
		virtual ~BollingerOverlay() {}

	private:
		class Band: public QGraphicsItem {
			private:
				AxisPair axisPair;
			public:
				Band(AxisPair axisPair);
				QList<QPair<QDateTime,BollingerEntry>> data;

				QRectF boundingRect() const;
				QPainterPath shape() const;
				void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
		};
};

#endif
