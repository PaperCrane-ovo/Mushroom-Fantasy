#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>

#include "waypoint.h"
#include "towerposition.h"
#include "tower.h"
#include "enemy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wayPoint;
class tower;
class enemy;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addWayPoint();  //添加航点
    void setTowerPos();
    void hurted(int damage);  //基地受到伤害
    void award(int m);
    void remove_enemy(enemy *e);
    QList<enemy *> get_enemy();
    bool load_waves();

private:
    Ui::MainWindow *ui;
    QList<wayPoint*> m_wayPoint_list;
    QList<TowerPosition> m_TowerPosition_list;
    QList<tower *> m_tower_list;
    QList<enemy *> m_enemy_list;
    int strength;
    int money;
    int m_waves;
    bool win, lose;

private slots:
    void update_map();
    void game_start();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *);
};
#endif // MAINWINDOW_H
