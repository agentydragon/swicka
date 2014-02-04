#ifndef GRID_LABELER_H_INCLUDED
#define GRID_LABELER_H_INCLUDED

#include <QList>
#include <QPair>
#include <QDateTime>

class GridLabeler {
	private:
		float generateYLabelStep(float min, float max);
	public:
		void generateYLabels(float min, float max, QList<QPair<float, QString> > &labels);
		void generateXLabels(QDateTime min, QDateTime max, QList<QPair<QDateTime, QString> > &labels);
};

#endif
