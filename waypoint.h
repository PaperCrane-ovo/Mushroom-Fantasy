#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class wayPoint {
public:
    wayPoint(QPoint pos);
    void setNextWayPoint(wayPoint *nextWayPoint); //设置下一个航点
    wayPoint *getNextWayPoint();  //的到下一个航点的指针
    const QPoint getPos();  //得到本航点的中心点
    void draw(QPainter *painter) const;  //绘画类函数
private:
    QPoint m_pos; //航点的中心点
    wayPoint *m_nextWayPoint; //下一个航点的指针
};

#endif // WAYPOINT_H
