#include "grid_labeler.h"

#include "x_axis_labeler.h"

#include <QDebug>

#include <cmath>

using namespace std;

float GridLabeler::generateYLabelStep(float min, float max) {
	int labelsLeast = 5;
	int labelsMost = 11;

	float difference = max - min;

	int multiplier = 1;
	float base = 0.00001f;

	// Try steps of 1, 2, 5, 10, 20, 50, etc.
	int ticks = ceil(difference / (base * multiplier));

	while (ticks > labelsMost) {
		switch (multiplier) {
			case 1: multiplier = 2; break;
			case 2: multiplier = 5; break;
			case 5: multiplier = 1; base *= 10; break;
		}
		ticks = ceil(difference / (base * multiplier));

		qDebug() << "mult=" << multiplier << "base=" << base;
	}

	while (ticks < labelsLeast) {
		switch (multiplier) {
			case 1: multiplier = 5; base /= 10; break;
			case 2: multiplier = 1; break;
			case 5: multiplier = 2; break;
		}
		ticks = ceil(difference / (base * multiplier));

		qDebug() << "mult=" << multiplier << "base=" << base;
	}

	return multiplier * base;
}

void GridLabeler::generateYLabels(float min, float max, QList<QPair<float, QString> > &labels) {
	qDebug() << "generating Y labels: min=" << min << "max=" << max;
	if (min == max) {
		qDebug() << "empty range";
		return;
	}
	float step = generateYLabelStep(min, max);
	
	labels.clear();
	for (float a = floor(min / step) * step; a < max; a += step) {
		if (a >= min) {
			labels.push_back(QPair<float, QString>(a, QString::number(a)));
		}
	}
	qDebug() << labels.size() << "Y labels generated with step" << step;
}

#include "x_axis_year_labeler.h"
#include "x_axis_month_labeler.h"
#include "x_axis_day_labeler.h"

void GridLabeler::generateXLabels(QDateTime min, QDateTime max, QList<QPair<QDateTime, QString> > &labels) {
	qDebug() << "generating X labels: min=" << min << "max=" << max;
	if (min == max) {
		qDebug() << "empty range";
		return;
	}
	QList<XAxisLabeler*> labelers;
	// TODO: choose 2 most appropriate labelers...
	//labelers.push_back(new XAxisYearLabeler);
	labelers.push_back(new XAxisMonthLabeler);
	//labelers.push_back(new XAxisDayLabeler);
	labels = labelers[0]->makeLabels(min, max);
	qDebug() << "X labels generated";
}
