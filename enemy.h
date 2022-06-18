#ifndef ENEMY_H
#define ENEMY_H

#include <QPoint>
#include <QString>
#include <QPainter>
#include <QSize>

#include "waypoint.h"
#include "mainwindow.h"

class MainWindow;
class tower;

class enemy: public QObject {
    Q_OBJECT
public:
    enemy(wayPoint *s, MainWindow *game, QString path = ":/images/images/enemy.png");
    ~enemy();
    void draw(QPainter *p) const;
    QPoint getPos();

    void move();  //敌人移动
    void attacked(tower *t);  //被防御塔攻击
    void hurted(int damage);
    void defeated();  //敌人死亡
    void out_of_range(tower *t);  //脱离攻击范围

private slots:
    void doActive(); //私有信号槽(?)，敌人是否可以移动

private:
    int strength;  //最大生命值
    int cur_strength;  //当前生命值
    int speed; //移动速度
    bool active;  //是否可以移动

    wayPoint *m_goal_pos;
    MainWindow *m_game;
    QPoint m_pos;
    QString m_path;
    QList<tower *> atker_tower;  //正在攻击自己的防御塔

    static const QSize m_size;
};

#endif // ENEMY_H
