#include "BlackBall.h"
#include "point.hpp"

using namespace gui::ball;

/**
 * @brief Controller::Controller Constructor of a Controller.
 * @param dx .
 * @param dy .
 * @param longLargeur .
 * @param longHauteur .
 * @param state .
 */
BlackBall::BlackBall(int dx ,int dy ,double longLargeur,double longHauteur, abalone::Model::Board::StateCase state)
    : QGraphicsPolygonItem(nullptr), dx(dx), dy(dy),
      mouseover(false), selected(false), moved(false),state(state)
{
    this->setAcceptHoverEvents(true);
    zval = zValue();

    double radCell = 40;
    double largeur = sqrt(3)*radCell;
    double X = longLargeur * largeur + largeur * dx;
    double Y =  longHauteur * (-1.5*radCell);


    static const double piOver6 = atan(1) * 4/6;

    QPolygonF polygon;
    auto&& corners = gui::point::orbit({X, Y},100, 20., piOver6);
    for(auto& p : corners)
        polygon << QPointF(p.first, p.second);

    setPolygon(polygon);
}

/**
 * @brief BlackBall::~BlackBall Destructor of BlackBall
 */
BlackBall::~BlackBall(){

}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void BlackBall::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    QPen pen(Qt::blue, 1);
    painter->setPen(pen);
    QBrush brush;
    if (state == abalone::Model::Board::BLACK)
        brush.setColor(Qt::black);
    if (state == abalone::Model::Board::WHITE)
        brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawPolygon(polygon());
}

void BlackBall::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mouseover = true;
    //update();
}

void BlackBall::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouseover = false;
    // update();
}

void BlackBall::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    moved = false;
    selected = !selected; //I'd like to put this in "released"
    update();

    //relaunches the event in order to allow dragging
    QGraphicsItem::mousePressEvent(event);
}

void BlackBall::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //why isn't this ever fired ?
}

void BlackBall::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moved = true;
}

void BlackBall::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    //write stuff here
    //rad +/-= 10 ?

    QGraphicsItem::wheelEvent(event);
}
#pragma GCC diagnostic pop
