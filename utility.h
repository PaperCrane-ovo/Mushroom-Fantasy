#ifndef UTILITY_H
#define UTILITY_H
#include <QPoint>
#include <cmath>
//圆形碰撞箱
inline bool isIncide(QPoint p1,int r1,QPoint p2,int r2){
    int x=p1.x()-p2.x();
    int y=p1.y()-p2.y();
    int dis=x*x+y*y;
    return dis<pow(r1+r2,2);
}
#endif // UTILITY_H
