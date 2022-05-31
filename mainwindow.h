#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

#include "waypoint.h"
#include "towerposition.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wayPoint;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addWayPoint();  //添加航点
    void setTowerPos();

private:
    Ui::MainWindow *ui;
    QList<wayPoint*> m_wayPoint_list;
    QList<TowerPosition> m_TowerPosition_list;

protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // MAINWINDOW_H
