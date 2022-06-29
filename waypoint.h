#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class wayPoint{
    QPoint m_pos;
    wayPoint *m_nextWayPoint;//下一个航点的指针
public:
    wayPoint(QPoint pos);
    void setNextWayPoint(wayPoint *nextWayPoint);//设置下一个航点
    wayPoint* getNextWayPoint();//得到下一个航点
    const QPoint getPos();//得到中心点
    void draw(QPainter* painter)const;//绘画
};

#endif // WAYPOINT_H
