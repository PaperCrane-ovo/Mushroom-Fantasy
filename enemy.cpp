#include "enemy.h"
#include "mainwindow.h"
#include "tower.h"
#include "utility.h"
#include "waypoint.h"

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QVector2D>

const QSize enemy::m_size(300, 400);

enemy::enemy(wayPoint *s, MainWindow *game, QString path) : QObject(0), m_game(game), m_pos(s->getPos()), m_path(path) {
    strength = 40;
    cur_strength = strength;
    speed = 1;
    active = false;
    m_goal_pos = s->getNextWayPoint();
}

enemy::~enemy() {
    atker_tower.clear();
    m_goal_pos = NULL;
    m_game = NULL;
}

void enemy::draw(QPainter *p) const {
    if (!active)  return;
    p->save();
    static const int healthBarLen = m_size.width();
    QPoint healthBarPos = m_pos + QPoint(-m_size.width() / 2, -m_size.height());
    p->setPen(Qt::NoPen);
    p->setBrush(Qt::red);
    QRect healthBkgBarRect(healthBarPos, QSize(healthBarLen, 2));
    p->drawRect(healthBkgBarRect);

    p->setBrush(Qt::green);
    QRect healthBarRect(healthBarPos, QSize((double)cur_strength / strength * healthBarLen, 2));
    p->drawRect(healthBarRect);

    QPoint tmp(m_pos.x() - m_size.width() / 2, m_pos.y() - m_size.height() / 2);
    p->drawPixmap(tmp.x(), tmp.y(), m_size.width(), m_size.height(), m_path);
    p->restore();
}

void enemy::move() {
    if (!active)  return;
    if (is_coincide(m_pos, 1, m_goal_pos->getPos(), 1)) { //到达目标航点
        if (m_goal_pos->getNextWayPoint()) {
            m_pos = m_goal_pos->getPos();
            m_goal_pos = m_goal_pos->getNextWayPoint();
        }
        else {
            m_game->hurted(5);
            m_game->remove_enemy(this);
            return;
        }
    }
    else {
        QPoint target = m_goal_pos->getPos();
        double spd = speed;
        QVector2D n(target - m_pos);
        n.normalize();
        m_pos = m_pos + n.toPoint() * spd;
    }
}

void enemy::doActive() {  active = true;  }

QPoint enemy::getPos() {  return m_pos;  }

void enemy::attacked(tower *t) {
    atker_tower.append(t);
}

void enemy::hurted(int damage) {
    cur_strength -= damage;
    if (cur_strength <= 0) {
        m_game->award(200);
        defeated();
    }
}

void enemy::defeated() {
    if (atker_tower.empty()) return;
    m_game->remove_enemy(this);
}

void enemy::out_of_range(tower *t) { atker_tower.removeOne(t);  }
