#include "hexacell.h"
using namespace gui::hexacell;


double const HexaCell::zValMax = 10000;//arbitrary

/**
 * @brief Controller::Controller Constructor of a Controller.
 * @param dx .
 * @param dy .
 * @param longLargeur .
 * @param longHauteur .
 * @param mainwindow .
 */
HexaCell::HexaCell(int dx, int dy,double longLargeur,double longHauteur,gui::mainwindow::MainWindow *mainwindow)
    : QGraphicsPolygonItem(nullptr),rad(40), dx(dx), dy(dy),
      mouseover(false), selected(false), moved(false)
{
    this->mainwindow_ = mainwindow;
    this->setAcceptHoverEvents(true);
    zval = zValue();

    double largeur = longLargeur * sqrt(3)*rad;
    double hauteur = longHauteur * -1.5*rad;
    double X = largeur+sqrt(3)*rad*dx;

    static const double piOver6 = atan(1) * 4/6;

    QPolygonF polygon;
    auto&& corners = gui::point::orbit({X, hauteur},6, rad, piOver6);
    for(auto& p : corners)
        polygon << QPointF(p.first, p.second);

    setPolygon(polygon);
}

/**
 * @brief HexaCell::~HexaCell Destructor of HexaCell
 */
HexaCell::~HexaCell(){

}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void HexaCell::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{

    if(mouseover)
    {
        QPen pen(Qt::blue, 1);
        painter->setPen(pen);

        QBrush brush;
        brush.setColor(Qt::green);
        brush.setStyle(Qt::SolidPattern);

        painter->setBrush(brush);
    }
    else
    {
        QPen pen(Qt::blue, 1);
        painter->setPen(pen);

        QBrush brush;
        brush.setColor(Qt::cyan);
        brush.setStyle(Qt::SolidPattern);

        painter->setBrush(brush);
    }

    painter->drawPolygon(polygon());
}


void HexaCell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mouseover = true;
    update();
}

void HexaCell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mouseover = false;
    update();
}

void HexaCell::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    moved = false;
    selected = !selected; //I'd like to put this in "released"
    convertToCoord();
    update();
    //relaunches the event in order to allow dragging
    QGraphicsItem::mousePressEvent(event);
}

void HexaCell::convertToCoord()
{
    int intDx = static_cast<int>(dx);
    int intDy = static_cast<int>(dy)+1;
    std::string stringDx;
    switch (intDx) {
    case 0:stringDx = "A";break;
    case 1:stringDx = "B";break;
    case 2:stringDx = "C";break;
    case 3:stringDx = "D";break;
    case 4:stringDx = "E";break;
    case 5:stringDx = "F";break;
    case 6:stringDx = "G";break;
    case 7:stringDx = "H";break;
    case 8:stringDx = "I";break;
    }
    std::string stringDy= std::to_string(intDy);
    commande= stringDx + stringDy ;
    sendTouchClick();
}


void HexaCell::sendTouchClick()
{
    this->mainwindow_->receivedTouchClick(commande);
}

void HexaCell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //why isn't this ever fired ?
}

void HexaCell::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moved = true;
}

void HexaCell::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    //write stuff here
    //rad +/-= 10 ?

    QGraphicsItem::wheelEvent(event);
}
#pragma GCC diagnostic pop

