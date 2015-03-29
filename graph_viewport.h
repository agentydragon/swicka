#ifndef GRAPH_VIEWPORT_H_INCLUDED
#define GRAPH_VIEWPORT_H_INCLUDED

#include <QObject>
#include <QDateTime>
#include "time_range.h"
#include "number_range.h"

class OHLCProvider;

// Contains the current selected graph time span.
class GraphViewport: public QObject {
	Q_OBJECT

	public slots:
		void zoom(int delta, QDateTime center);

	signals:
		void changed();

	private:
		float viewMargin;
		double zoomLevel;
		QDateTime viewBegin, viewEnd;
		OHLCProvider* source;
		OHLCProvider* projection;

		void resetProjection();

	public:
		GraphViewport(OHLCProvider* source, float viewMargin);
		GraphViewport* duplicate();
		QDateTime getViewBegin();
		QDateTime getViewEnd();

		TimeRange getTimeRange();
		NumberRange getClosureNumberRange();

		OHLCProvider* getSourceProjection();

		void reset();
};

#endif
