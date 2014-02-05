#ifndef GRAPH_OVERLAY_H_INCLUDED
#define GRAPH_OVERLAY_H_INCLUDED

#include "graph_ranges.h"

class QGraphicsScene;

class GraphOverlay {
	public:
		virtual void insertIntoScene(QGraphicsScene* scene) = 0;

	public slots:
		virtual void rangesChanged(GraphRanges ranges) = 0;
};

#endif
