#ifndef GRID_LABELER_H_INCLUDED
#define GRID_LABELER_H_INCLUDED

#include <QList>

class GridLabeler {
	private:
		float generateLabelStep(float min, float max);
	public:
		void generateLabels(float min, float max, QList<float> &labels);
};

#endif
