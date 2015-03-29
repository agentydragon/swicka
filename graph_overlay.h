#ifndef GRAPH_OVERLAY_H_INCLUDED
#define GRAPH_OVERLAY_H_INCLUDED

#include "number_axis.h"
#include "time_axis.h"

#include <QObject>

class QGraphicsScene;
class OHLCProvider;

class GraphOverlay: public QObject {
	Q_OBJECT

	public:
		virtual void insertIntoScene(QGraphicsScene* scene) = 0;
		virtual ~GraphOverlay() {}

	public slots:
		virtual void timeAxisChanged(TimeAxis timeAxis) = 0;
		virtual void numberAxisChanged(NumberAxis numberAxis) = 0;
		virtual void projectionChanged(OHLCProvider* projection) = 0;
};

#endif
