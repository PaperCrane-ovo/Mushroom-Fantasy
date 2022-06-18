#include "tower.h"
#include "mainwindow.h"

#include <QPoint>
#include <QString>
#include <QPainter>

const QSize tower::m_size(800, 1000);
tower::tower() {}

tower::~tower() {}

tower::tower(QPoint p, MainWindow *game, QString path) : m_pos(p), m_path(path), m_atkRange(400), m_game(game) {}

void tower::draw(QPainter *p) const {
    p->save();
    p->setPen(Qt::white);
    p->drawEllipse(m_pos, m_atkRange, m_atkRange);  //画出防御塔攻击范围
    p->drawPixmap(m_pos.x() - m_size.width() / 2 + 60, m_pos.y() - m_size.height() / 2 - 140, m_size.width(), m_size.height(), m_path);
}
