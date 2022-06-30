#include "tower.h"
#include "mainwindow.h"

#include <QPoint>
#include <QPainter>
#include <QString>

const QSize Tower::m_size(100,154);
Tower::Tower(){}
Tower::~Tower(){
    delete m_fireRateTimer;
    m_fireRateTimer=NULL;
    m_game=NULL;m_attackedEnemy=NULL;
    delete m_attackedEnemy;

}
Tower::Tower(QPoint pos,int damage,int fireRate,MainWindow* game,QString path):m_pos(pos),m_path(path),m_attackRange(150),m_game(game),
    m_attackedEnemy(NULL),m_damage(damage),m_fireRate(fireRate){
    m_fireRateTimer=new QTimer(this);
    connect(m_fireRateTimer,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}
void Tower::draw(QPainter *painter)const{
    painter->save();
    painter->setPen(QColor(181,234,221));
    painter->drawEllipse(m_pos,m_attackRange,m_attackRange);//画出攻击范围
    painter->drawPixmap(m_pos.x()-m_size.width()/2,m_pos.y()-m_size.height()/2,m_size.width(),m_size.height(),m_path);
}
void Tower::chooseEnemyToAttack(Enemy* enemy){
    m_attackedEnemy=enemy;
    attackEnemy();
}
void Tower::attackEnemy(){m_fireRateTimer->start(m_fireRate);}
void Tower::shootWeapon(){
    Bullet* bullet=new Bullet(m_pos,m_attackedEnemy->getPos(),m_damage,m_attackedEnemy,m_game);
    m_game->addBullet(bullet);
    bullet->move();
}
//TODO
void Tower::targetKilled(){
    if(m_attackedEnemy)
        m_attackedEnemy=NULL;
    m_fireRateTimer->stop();
}
void Tower::towerLoseSight(){
    targetKilled();
}
void Tower::checkEnemyInRange(){
    if(m_attackedEnemy){
        if(!isIncide(m_pos,m_attackRange,m_attackedEnemy->getPos(),1))
            towerLoseSight();
    }
    else{
        QList<Enemy*> enemyList=m_game->getEnemyList();
        foreach(Enemy* enemy,enemyList)
            if(isIncide(m_pos,m_attackRange,enemy->getPos(),1)){
                chooseEnemyToAttack(enemy);
                break;
            }
    }
}
Enemy* Tower::getEnemyBeingAttacked(){return m_attackedEnemy;}
void Tower::setEnemyBeingAttacked(Enemy* enemy){m_attackedEnemy=enemy;}
