#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QSize>
#include <QPainter>
#include <QString>
class TowerPos{
public:
    TowerPos(QPoint pos, QString path = (":/images/towerdir.png"));
    QPoint getPos();
    bool containPos(QPoint pos);//判断pos是否在防御塔坑的范围
    void draw(QPainter* painter)const;
    bool hasTower();//判定是否有防御塔
    void setHasTower(bool hasTower = true);//设置是否有防御塔
private:
    QPoint m_pos;
    QString m_path;
    bool m_hasTower;
    static const QSize m_size;
};
#endif // TOWERPOSITION_H
