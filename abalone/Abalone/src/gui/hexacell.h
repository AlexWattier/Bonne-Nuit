#ifndef HEXACELL_H
#define HEXACELL_H

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

#include "../abalone/Model.h"
#include "../abalone/Case.h"
#include "../abalone/Controller.h"
#include "../gui/mainwindow.h"
#include "point.hpp"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneWheelEvent;

namespace gui::hexacell {
/**
 * @brief The HexaCell class
 */
class HexaCell  : public QGraphicsPolygonItem
{
    static const double zValMax; //z-val of selected items
    double zval; //z-val at instanciation
private:

    gui::mainwindow::MainWindow *mainwindow_;
    std::string commande= "";
    void convertToCoord();

protected:
    double rad, dx, dy;//hexagon radius, coordinate (x,y) of center
    bool mouseover, selected, moved;//mouse interaction booleans

public:
    HexaCell(int dx ,int dy ,double longLargeur ,double longHauteur ,
             gui::mainwindow::MainWindow *mainwindow);
    ~HexaCell();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    inline QPointF coord(double x, double y) const;

    inline void setLocation(double x, double y);

    void sendTouchClick();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void wheelEvent(QGraphicsSceneWheelEvent * event);
};
}
#endif // HEXACELL_H
