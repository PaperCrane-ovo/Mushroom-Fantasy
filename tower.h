#ifndef TOWER_H
#define TOWER_H
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QTimer>
#include "mainwindow.h"
#include "bullet.h"
class MainWindow;
class QPainter;
class Enemy;
class QTimer;
class Tower:QObject{
    Q_OBJECT
    public:
        Tower(QPoint pos,MainWindow * game,QString path=":/images/tower1.png");
        ~Tower();
        Tower();
        void attackEnemy();
        void targetKilled();
        void chooseEnemyToAttack(Enemy* enemy);
        void removeBullet();
        void loseSightOfEnemy();
        void checkEnemyInRange();
        Enemy* getEnemyBeingAttacked();
        void draw(QPainter * painter)const;//画出防御塔
    private:
        QPoint m_pos;//防御塔的中心点
        QString m_path;//防御塔图片的路径

        int m_attackRange;//攻击范围
        static const QSize m_size;//防御塔图片的固定大小
        MainWindow * m_game;//指向mainwindow的指针
        Enemy* m_attackedEnemy;
        int m_damage;
        int m_fireRate;
        QTimer* m_fireRateTimer;
private slots:
        void shootWeapon();
};

#endif // TOWER_H
