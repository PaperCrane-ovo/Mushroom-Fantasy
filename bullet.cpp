#include "bullet.h"
#include "mainwindow.h"
#include "tower.h"
#include "enemy.h"
#include "utility.h"

#include <QPoint>
#include <QPainter>
#include <QSize>
#include <QString>
#include <QPropertyAnimation>
const QSize Bullet::m_fixedSize(5,5);
Bullet::Bullet(){}
Bullet::Bullet(QPoint start,QPoint target,int damage,Enemy* targetEnemy,MainWindow* game,QString path)
    :m_curPos(start),m_startPos(start),m_targetPos(target),m_damage(damage),m_path(path),m_targetEnemy(targetEnemy),m_game(game){}
QPoint Bullet::getCurPos(){return m_curPos;}
void Bullet::setCurPos(QPoint curPos){m_curPos=curPos;}
void Bullet::move(){
    static int hitTime=100;
    QPropertyAnimation* animation=new QPropertyAnimation(this,"m_curPos");
    animation->setDuration(hitTime);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
    animation->start();
}
void Bullet::hitTarget(){
    if(m_game->getEnemyList().indexOf(m_targetEnemy)!=-1)
        m_targetEnemy->getDamaged(m_damage);
    m_game->removeBullet(this);
}
void Bullet::draw(QPainter* painter)const{
    painter->drawPixmap(m_curPos,m_path);
}
