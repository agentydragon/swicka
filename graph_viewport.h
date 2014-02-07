#ifndef GRAPH_VIEWPORT_H_INCLUDED
#define GRAPH_VIEWPORT_H_INCLUDED

#include <QDateTime>
#include "graph_ranges.h"

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
		QDateTime getViewBegin();
		QDateTime getViewEnd();

		OHLCProvider* getSourceProjection();

		GraphRanges getRanges();
		void reset();
};

#endif
