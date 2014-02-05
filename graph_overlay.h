#ifndef GRAPH_OVERLAY_H_INCLUDED
#define GRAPH_OVERLAY_H_INCLUDED

#include "graph_ranges.h"

class QGraphicsScene;
class OHLCProvider;

class GraphOverlay: public QObject {
	Q_OBJECT

	public:
		virtual void insertIntoScene(QGraphicsScene* scene) = 0;
		virtual ~GraphOverlay() {}

	public slots:
		virtual void rangesChanged(GraphRanges ranges) = 0;
		virtual void projectionChanged(OHLCProvider* projection) = 0;
};

#endif
