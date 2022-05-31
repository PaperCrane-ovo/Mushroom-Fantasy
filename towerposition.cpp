#include "towerposition.h"
#include <QPainter>
#include <QSize>
#include <QPixmap>

const QSize TowerPosition::m_size(800, 800);

TowerPosition::TowerPosition(QPoint pos, QString path) : m_pos(pos), m_path(path), m_hasTower(false) {}

bool TowerPosition::hasTower() { return m_hasTower; }

void TowerPosition::setHasTower(bool hasTower) { m_hasTower = hasTower; }

QPoint TowerPosition::getPos() { return m_pos; }

QPoint TowerPosition::getCenterPos() {
    QPoint center;
    center.setX(m_pos.x() + m_size.width() / 2);
    center.setY(m_pos.y() + m_size.height() / 2);
    return center;
}

bool TowerPosition::isValidPos(QPoint pos) {
    int nx = m_pos.x() + m_size.width(), ny = m_pos.y() + m_size.height();
    if (pos.x() < m_pos.x() || pos.y() < m_pos.y() || pos.x() > nx || pos.y() > ny) return false;
    return true;
}

void TowerPosition::draw(QPainter *p) const{
    p->drawPixmap(m_pos.x(), m_pos.y(), m_size.width(), m_size.height(), m_path);
}
