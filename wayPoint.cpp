#include "waypoint.h"

#include <QPoint>
#include <QPainter>

wayPoint::wayPoint(QPoint pos): m_pos(pos), m_nextWayPoint(NULL) {}

void wayPoint::setNextWayPoint(wayPoint *nextWayPoint) {
    this->m_nextWayPoint = nextWayPoint;
}

wayPoint *wayPoint::getNextWayPoint() {
    return this->m_nextWayPoint;
}

const QPoint wayPoint::getPos() {
    return this->m_pos;
}

void wayPoint::draw(QPainter *painter) const {
    painter->save(); //保存原始的绘画参数
    painter->setPen(Qt::green); //设置画笔的颜色
    painter->drawEllipse(m_pos, 4, 4);  //画一个半径为4的圆
    //图片的大小单位是像素
    painter->drawEllipse(m_pos, 1, 1);
}
