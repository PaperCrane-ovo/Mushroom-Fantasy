#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "waypoint.h"
#include "towerposition.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    addWayPoint();
    setTowerPos();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QString path(":/images/images/background.png");
    painter.drawPixmap(0, 0, 3840, 1985, path);

    foreach(const wayPoint *p, m_wayPoint_list)
        p->draw(&painter);

    foreach(const TowerPosition p, m_TowerPosition_list)
        p.draw(&painter);
}

void MainWindow::addWayPoint() {
    wayPoint *waypoint1 = new wayPoint(QPoint(390, 10));
    m_wayPoint_list.append(waypoint1);

    wayPoint *waypoint2 = new wayPoint(QPoint(390, 430));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPoint_list.append(waypoint2);

    wayPoint * waypoint3 = new wayPoint(QPoint(3280, 430));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPoint_list.append(waypoint3);

    wayPoint * waypoint4 = new wayPoint(QPoint(3280, 1030));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPoint_list.append(waypoint4);

    wayPoint * waypoint5 = new wayPoint(QPoint(390, 1030));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPoint_list.append(waypoint5);

    wayPoint * waypoint6 = new wayPoint(QPoint(390, 1592));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPoint_list.append(waypoint6);

    wayPoint * waypoint7 = new wayPoint(QPoint(2600, 1592));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPoint_list.append(waypoint7);
}

void MainWindow::setTowerPos() {
    QPoint pos[] = { QPoint(2498,-200), QPoint(226,98), QPoint(439,98), QPoint(3210,215),
                    QPoint(186,215), QPoint(314,215), QPoint(105,321), QPoint(223,323), QPoint(365,319) };
    int len = sizeof(pos) / sizeof(QPoint);
    for (int i = 0; i < len; ++i) {
        m_TowerPosition_list.append(pos[i]);
    }
}
