#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <QtWidgets>

#include "graph_overlay.h"
#include "axis_pair.h"

class Grid: public GraphOverlay {
	Q_OBJECT

	private:
		AxisPair axisPair;
		bool drawTimeLabels;
	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis);
		virtual void numberAxisChanged(NumberAxis numberAxis);
		virtual void projectionChanged(OHLCProvider* projection);
	public:
		Grid(bool drawTimeLabels = true);
		virtual void insertIntoScene(QGraphicsScene* scene);

		class GridGraphics: public QGraphicsItem {
		public:
			GridGraphics(AxisPair axisPair, bool drawTimeLabels);
			void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
			QRectF boundingRect() const;
			QPainterPath shape() const;
		private:
			bool drawTimeLabels;
			AxisPair axisPair;
			QList<QPair<QDateTime, QString> > xlabels;
			QList<QPair<float, QString> > ylabels;
		};
};

#endif
