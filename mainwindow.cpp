#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "waypoint.h"
#include "towerposition.h"
#include "enemy.h"
#include "tower.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), strength(100), money(1000), m_waves(0), win(false), lose(false) {
    ui->setupUi(this);
    addWayPoint();
    setTowerPos();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30);
    QTimer::singleShot(300, this, SLOT(game_start()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    if(win || lose) {
            QString  result = win ? "YOU WIN" : "YOU LOST";
            QPainter painter(this);
            painter.setPen(Qt::red);
            painter.drawText(rect(),Qt::AlignCenter, result);
            return ;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QString path(":/images/images/background.png");
    painter.drawPixmap(0, 0, 3840, 1985, path);

    foreach(const wayPoint *p, m_wayPoint_list)
        p->draw(&painter);

    foreach(const TowerPosition p, m_TowerPosition_list)
        p.draw(&painter);

    foreach(const tower *t, m_tower_list)
        t->draw(&painter);

    foreach(const enemy *e, m_enemy_list)
        e->draw(&painter);
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
    QPoint pos[] = { QPoint(2498,-200), QPoint(826, 275), QPoint(2139, 275), QPoint(3210,215), QPoint(126, 275),
                    QPoint(1486,275), QPoint(1714,870), QPoint(505,871), QPoint(1123,873), QPoint(-285,919), QPoint(1823, 1473) };
    int len = sizeof(pos) / sizeof(QPoint);
    for (int i = 0; i < len; ++i) {
        m_TowerPosition_list.append(pos[i]);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *m) {
    QPoint p = m->pos();
    for (auto ii = m_TowerPosition_list.begin(); ii != m_TowerPosition_list.end(); ++ii) {
        if (Qt::LeftButton == m->button()) {
            if (ii->isValidPos(p) && !ii->hasTower()) {
                tower *t = new tower(ii->getCenterPos(), this);
                m_tower_list.append(t);
                ii->setHasTower(true);
                update();
                break;
            }
        }
    }
}

bool MainWindow::load_waves() {
    if (m_waves >= 6)  return false;
    int enemy_time[] = {100, 500, 600, 1000, 3000, 6000};
    for (int i = 0; i < 6; ++i) {
        wayPoint *s = m_wayPoint_list.first();
        enemy *e = new enemy(s, this);
        m_enemy_list.append(e);
        QTimer::singleShot(enemy_time[i], e, SLOT(doActive()));
    }
    return true;
}

void MainWindow::game_start() {  load_waves();  }

void MainWindow::update_map() {
    foreach(enemy *e, m_enemy_list)
        e->move();
    update();
}

void MainWindow::hurted(int damage) {  strength -= damage;  }

void MainWindow::award(int m) {  money += m;  }

void MainWindow::remove_enemy(enemy *e) {
    Q_ASSERT(e);
    m_enemy_list.removeOne(e);
    delete e;
    if (m_enemy_list.empty()) {
        ++m_waves;
        if (!load_waves())  win = true;
    }
}

QList<enemy *> MainWindow::get_enemy() {  return m_enemy_list;  }
