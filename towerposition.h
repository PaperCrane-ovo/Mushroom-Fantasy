#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QSize>
#include <QPainter>
#include <QString>

class TowerPosition {
public:
    TowerPosition(QPoint pos, QString path = (":/images/images/image2.png"));
    QPoint getCenterPos();  //找到防御塔的中心点
    QPoint getPos();  //得到防御塔坑的左上角
    bool isValidPos(QPoint pos); //判断pos是否在防御塔坑的范围内
    void draw(QPainter *p) const;
    bool hasTower(); //判断坑里是否有塔
    void setHasTower(bool hasTower = true);
private:
    QPoint m_pos;
    QString m_path;
    bool m_hasTower;
    static const QSize m_size; //固定的防御塔坑的大小
};

#endif // TOWERPOSITION_H
