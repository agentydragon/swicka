
#include "candle.h"

#include <QtWidgets>

// Expected to be standardized to (1.0) == min-max of whole scene
Candle::Candle(OHLC ohlc, float width, float height) {
	this->ohlc = ohlc;
	this->width = width;
	this->height = height;
}

QRectF Candle::boundingRect() const {
    return QRectF(0, 0, width, height);
}

QPainterPath Candle::shape() const {
    QPainterPath path;
    path.addRect(0, 0, width, height);
    return path;
}

void Candle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    int penWidth = 1;
    if (option->state & QStyle::State_Selected)
        penWidth += 2;

    painter->setPen(QPen(Qt::gray, penWidth));
    painter->drawLine(width / 2, ohlc.low * height, width / 2, ohlc.high * height);

    QColor fillColor = ohlc.isUp() ? QColor(0, 255, 0) : QColor(255, 0, 0);
    painter->setBrush(QBrush(fillColor));

    painter->drawRect(QRect(0, ohlc.open * height, width, ohlc.close * height));

    /*
    if (lod >= 1) {
        painter->setPen(QPen(Qt::gray, 1));
        painter->drawLine(15, 54, 94, 54);
        painter->drawLine(94, 53, 94, 15);
        painter->setPen(QPen(Qt::black, 0));
    }

    // Draw lines
    QVarLengthArray<QLineF, 36> lines;
    if (lod >= 0.5) {
        for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2)) {
            lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
            lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
        }
        for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2)) {
            lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
            lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
        }
    }
    if (lod >= 0.4) {
        const QLineF lineData[] = {
            QLineF(25, 35, 35, 35),
            QLineF(35, 30, 35, 40),
            QLineF(35, 30, 45, 35),
            QLineF(35, 40, 45, 35),
            QLineF(45, 30, 45, 40),
            QLineF(45, 35, 55, 35)
        };
        lines.append(lineData, 6);
    }
    painter->drawLines(lines.data(), lines.size());
    */
}
