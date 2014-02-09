#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <QtWidgets>

#include "graph_overlay.h"
#include "axis_pair.h"

class Grid: public GraphOverlay {
	Q_OBJECT

	private:
		AxisPair axisPair;
	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis);
		virtual void numberAxisChanged(NumberAxis numberAxis);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		Grid();
		virtual void insertIntoScene(QGraphicsScene* scene);

		class GridGraphics: public QGraphicsItem {
		public:
			GridGraphics(AxisPair axisPair);
			void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
			QRectF boundingRect() const;
			QPainterPath shape() const;
		private:
			AxisPair axisPair;
			QList<QPair<QDateTime, QString> > xlabels;
			QList<QPair<float, QString> > ylabels;
		};
};

#endif
