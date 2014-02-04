#include "grid_labeler.h"

#include <cmath>

using namespace std;

float GridLabeler::generateLabelStep(float min, float max) {
	int labelsLeast = 5;
	int labelsMost = 11;

	float difference = max - min;

	int multiplier = 1;
	float base = 1.0f;

	// Try steps of 1, 2, 5, 10, 20, 50, etc.
	do {
		int ticks = ceil(difference / (base * multiplier));
		if (ticks >= labelsLeast && ticks <= labelsMost) {
			break;
		}

		switch (multiplier) {
			case 1: multiplier = 2; break;
			case 2: multiplier = 5; break;
			case 5: multiplier = 1; base *= 10; break;
		}
	} while (true);

	return base * multiplier;
}

void GridLabeler::generateLabels(float min, float max, QList<float> &labels) {
	float step = generateLabelStep(min, max);
	
	labels.clear();
	for (float a = floor(min / step) * step; a < max; a += step) {
		if (a >= min) {
			labels.push_back(a);
		}
	}
}
