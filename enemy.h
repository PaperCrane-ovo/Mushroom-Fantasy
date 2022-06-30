#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QPainter>
#include <QSize>

#include "waypoint.h"
#include "mainwindow.h"
#include "tower.h"

class MainWindow;
class Tower;
class QPainter;
class wayPoint;

class Enemy:public QObject{
     Q_OBJECT;
public:
    Enemy(wayPoint* startPoint,int Hp,int walkingSpeed,MainWindow* game,QString path=":/images/enemy1.png");
    ~Enemy();
    void draw(QPainter* painter)const;
    void move();

    QPoint getPos();

    void getAttacked(Tower* tower);
    void getDamaged(int damage);
    void getRemoved();
    void getLostSight(Tower* tower);

private slots:
    void doActive();//是否可以移动

private:
    int m_maxHp;
    int m_curHp;
    int m_walkingSpeed;
    bool m_active;

    wayPoint* m_destWayPoint;
    MainWindow* m_game;
    QPoint m_pos;
    QString m_path;

    static const QSize m_size;
};

#endif // ENEMY_H
