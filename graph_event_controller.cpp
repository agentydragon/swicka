#include <QDebug>

#include "graph_event_controller.h"

void GraphEventController::signalCandleEntered(QDateTime start) {
	emit candleEntered(start);
}

void GraphEventController::signalCandleLeft() {
	emit candleLeft();
}
