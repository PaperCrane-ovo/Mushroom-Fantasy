#ifndef UTILITY_H
#define UTILITY_H

#endif // UTILITY_H
#include <QPoint>
#include <cmath>
//判断两个点是否相撞
inline bool is_coincide(QPoint p1, int r1, QPoint p2, int r2) {
    int xx = p1.x() - p2.x(), yy = p1.y() - p2.y();
    int dis = sqrt(xx * xx + yy * yy);
    return dis < r1 + r2;
}
