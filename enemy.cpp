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

const QSize Enemy::m_size(55,65);

Enemy::Enemy(wayPoint* firstWayPoint,int Hp,int walkingSpeed,MainWindow* game,QString path):
    QObject(0),m_maxHp(Hp),m_walkingSpeed(walkingSpeed),m_game(game),m_pos(firstWayPoint->getPos()),m_path(path){
    m_curHp=m_maxHp;
    m_active=false;
    m_destWayPoint=firstWayPoint->getNextWayPoint();
}
Enemy::~Enemy(){
    m_destWayPoint=NULL;
    m_game=NULL;
}
///绘出enemy

void Enemy::draw(QPainter* painter)const{
    if(!m_active) return;

    painter->save();
    ///画出敌人的血条
    static const int healthBarWidth=m_size.width();//血条长度
    QPoint healthBarPoint=m_pos+QPoint(-m_size.width()/2,-m_size.height());
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,2));
    painter->drawRect(healthBarBackRect);
    ///画出当前血量
    painter->setBrush(Qt::green);
    ///算出当前血量占比
    QRect healthBarRect(healthBarPoint,QSize((double)m_curHp/m_maxHp*healthBarWidth,2));
    painter->drawRect(healthBarRect);
    ///画敌人
    QPoint tmp(m_pos.x()-m_size.width()/2,m_pos.y()-m_size.height()/2);//得到图片左上点
    painter->drawPixmap(tmp.x(),tmp.y(),m_path);
    painter->restore();
}

void Enemy::move(){
    if(!m_active)return;
    if(isIncide(m_pos,1,m_destWayPoint->getPos(),1)){//到达目标航点
        if(m_destWayPoint->getNextWayPoint()){
            m_pos=m_destWayPoint->getPos();
            m_destWayPoint=m_destWayPoint->getNextWayPoint();

        }
        else{
            m_game->getHpDamaged();
            m_game->removeEnemy(this);
            return;
        }
    }
    else{
        QPoint targetPoint  = m_destWayPoint->getPos();
        double speed=m_walkingSpeed;
        QVector2D vector2d(targetPoint-m_pos);//长度归一化
        vector2d.normalize();
        m_pos=m_pos+vector2d.toPoint()*speed;
    }
}

void Enemy::doActive(){
    m_active=true;
}

QPoint Enemy::getPos(){
    return m_pos;
}

void Enemy::getDamaged(int damage)
{
    m_curHp-=damage;
    if(m_curHp<=0)
    {
        m_game->awardGold();
        getRemoved();
    }
}
void Enemy::getRemoved(){
    m_game->removeEnemy(this);
}

