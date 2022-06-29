#include "towerposition.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

const QSize TowerPosition::m_fixedSize(100,102);

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

bool TowerPosition::ContainPos(QPoint pos){
    bool xInHere=pos.x()>m_pos.x()-m_fixedSize.width()/2&&pos.x()<m_pos.x()+m_fixedSize.width()/2;
    bool yInHere=pos.y()>m_pos.y()-m_fixedSize.height()/2&&pos.y()<m_pos.y()+m_fixedSize.height()/2;
    return xInHere&&yInHere;
}

void TowerPosition::draw(QPainter* painter)const{
    painter->drawPixmap(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2,m_fixedSize.width(),m_fixedSize.height(),m_path);
}
