#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QObject>
#include <QPainter>
#include <QString>
#include <QSize>

#include "enemy.h"
#include "mainwindow.h"
#include "tower.h"
#include "utility.h"

class Enemy;
class Tower;
class MainWindow;

class Bullet:public QObject{
    Q_OBJECT
    Q_PROPERTY(QPoint m_curPos READ getCurPos WRITE setCurPos)
public:
    Bullet();
    Bullet(QPoint start,QPoint target,int damage,Enemy* tarEnemy,MainWindow * game,QString path=":/images/bullet1.png");
    QPoint getCurPos();
    void setCurPos(QPoint curPos);
    void move();
    void draw(QPainter * painter)const;
private slots:
    void hitTarget();

private:
    QPoint m_curPos;
    QPoint m_startPos;
    QPoint m_targetPos;
    int m_damage;
    QString m_path;

    Enemy* m_targetEnemy;
    MainWindow* m_game;

    static const QSize m_fixedSize;//子弹大小

};

#endif // BULLET_H
