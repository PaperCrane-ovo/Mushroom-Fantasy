#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "towerposition.h"
#include "waypoint.h"
#include <QMouseEvent>
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wayPoint;
class Tower;
class Enemy;
class Bullet;

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addWayPoint();//添加航点
    void loadTowerPosition();//加载防御塔坑

    void getHpDamaged();
    void awardGold();//敌人死亡奖励
    void removeEnemy(Enemy* enemy);
    QList<Enemy*> getEnemyList();

    void removeBullet(Bullet* bullet);
    void addBullet(Bullet* bullet);

    bool loadWaves();
    void drawHp(QPainter* painter)const;
    void drawGold(QPainter* painter)const;
    void drawWaves(QPainter* painter)const;
    void drawLackOfMoney(QPainter* painter)const;
    bool canBuyTower();

private:
    Ui::MainWindow *ui;
    QList<wayPoint*> m_wayPointList;//存储航点
    QList<TowerPosition> m_towerPositionList;//存储防御塔坑打的list
    QList<Tower*> m_towerList;
    QList<Bullet*> m_bulletList;
    QList<Enemy*>m_enemyList;
    int m_playerHp;//初始生命值
    int m_playerGold;//初始金钱

    int m_waves;
    bool m_gameWin,m_gameLose;
private slots:
    void updateMap();
    void gameStart();
};
#endif // MAINWINDOW_H
