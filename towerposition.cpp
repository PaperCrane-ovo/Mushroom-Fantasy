#include "towerposition.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

const QSize TowerPosition::m_size(100,102);

TowerPosition::TowerPosition(QPoint pos,QString path):m_pos(pos),m_path(path),m_hasTower(false){}

bool TowerPosition::hasTower(){
    return m_hasTower;
}

void TowerPosition::setHasTower(bool hasTower){
    m_hasTower=hasTower;
}


QPoint TowerPosition::getPos(){
    return m_pos;
}

bool TowerPosition::containPos(QPoint pos){
    bool xIn=pos.x()>m_pos.x()-m_size.width()/2&&pos.x()<m_pos.x()+m_size.width()/2;
    bool yIn=pos.y()>m_pos.y()-m_size.height()/2&&pos.y()<m_pos.y()+m_size.height()/2;
    return xIn&&yIn;
}

void TowerPosition::draw(QPainter* painter)const{
    painter->drawPixmap(m_pos.x()-m_size.width()/2,m_pos.y()-m_size.height()/2,m_size.width(),m_size.height(),m_path);
}
