#ifndef BLACKBALL_H
#define BLACKBALL_H

#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <string>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <iostream>
#include <cmath>
#include <string>

#include "../abalone/Model.h"
#include "../abalone/Case.h"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneWheelEvent;

namespace gui::ball {

/**
 * @brief The BlackBall class
 */
class BlackBall  : public QGraphicsPolygonItem
{
    static const double zValMax;
    double zval;

protected:
    double dx, dy;
    bool mouseover, selected, moved;
    abalone::Model::Board::StateCase state;


public:
    BlackBall(int dx ,int dy ,double longLargeur,
              double longHauteur, abalone::Model::Board::StateCase);
    ~BlackBall();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    inline QPointF coord(double x, double y) const;

    inline void setLocation(double x, double y);

protected:
    double getDx();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void wheelEvent(QGraphicsSceneWheelEvent * event);
};
}



#endif // BLACKBALL_H
