
#ifndef CANDLE_H
#define CANDLE_H

#include <QColor>
#include <QGraphicsItem>

#include "ohlc.h"

class Candle : public QGraphicsItem
{
public:
	// TODO: nebyl by lepsi decimal?
    Candle(OHLC ohlc, float width, float height);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

private:
    float width, height;
    OHLC ohlc;
};

#endif // CANDLE_H
