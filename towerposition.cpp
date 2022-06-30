#include "towerposition.h"
#include <QSize>
#include <QPainter>
#include <QPixmap>
const QSize TowerPos::m_size(100,102);
TowerPos::TowerPos(QPoint pos,QString path):m_pos(pos),m_path(path),m_hasTower(false){}
bool TowerPos::hasTower(){
    return m_hasTower;
}
void TowerPos::setHasTower(bool hasTower){
    m_hasTower=hasTower;
}

QPoint TowerPos::getPos(){
    return m_pos;
}
bool TowerPos::containPos(QPoint pos){
    bool xIn=pos.x()>m_pos.x()-m_size.width()/2&&pos.x()<m_pos.x()+m_size.width()/2;
    bool yIn=pos.y()>m_pos.y()-m_size.height()/2&&pos.y()<m_pos.y()+m_size.height()/2;
    return xIn&&yIn;
}
void TowerPos::draw(QPainter* painter)const{
    painter->drawPixmap(m_pos.x()-m_size.width()/2,m_pos.y()-m_size.height()/2,m_size.width(),m_size.height(),m_path);
}
