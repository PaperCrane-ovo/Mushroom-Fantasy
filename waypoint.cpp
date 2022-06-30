#include "waypoint.h"

#include <QPoint>
#include <QPainter>

wayPoint::wayPoint(QPoint pos):m_pos(pos),m_nextWayPoint(NULL){}


void wayPoint::setNextWayPoint(wayPoint* nextWayPoint){
    m_nextWayPoint= nextWayPoint;
}

wayPoint* wayPoint::getNextWayPoint(){
    return m_nextWayPoint;
}

const QPoint wayPoint::getPos(){
    return m_pos;
}

void wayPoint::draw(QPainter* painter)const{
    painter->save();
    painter->setPen(Qt::green);//绿色画笔
    painter->drawEllipse(m_pos,4,4);
    painter->drawEllipse(m_pos,1,1);
    if(m_nextWayPoint){//存在下一个航点
        painter->drawLine(m_pos,m_nextWayPoint->getPos());
    }
    painter->restore();
}
