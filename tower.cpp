#include "tower.h"
#include "mainwindow.h"

#include <QPoint>
#include <QPainter>
#include <QString>

const QSize Tower::m_fixedSize(100,154);
Tower::Tower(){}
Tower::~Tower(){
    delete m_fireRateTime;
    m_fireRateTime=NULL;
    m_game=NULL;m_attackedEnemy=NULL;
    delete m_attackedEnemy;

}
Tower::Tower(QPoint pos,MainWindow* game,QString path):m_pos(pos),m_path(path),m_attackRange(150),m_game(game),
    m_attackedEnemy(NULL),m_attacking(false),m_damage(10),m_fireRate(1000){
    m_fireRateTime=new QTimer(this);
    connect(m_fireRateTime,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}
void Tower::draw(QPainter *painter)const{
    painter->save();
    painter->setPen(QColor(181,234,221));
    painter->drawEllipse(m_pos,m_attackRange,m_attackRange);//画出攻击范围
    painter->drawPixmap(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2,m_fixedSize.width(),m_fixedSize.height(),m_path);
}
void Tower::chooseEnemyToAttack(Enemy* enemy){
    m_attackedEnemy=enemy;
    attackEnemy();
    m_attackedEnemy->getAttacked(this);
}
void Tower::attackEnemy(){m_fireRateTime->start(m_fireRate);}
void Tower::shootWeapon(){
    Bullet* bullet=new Bullet(m_pos,m_attackedEnemy->getPos(),m_damage,m_attackedEnemy,m_game);
    m_game->addBullet(bullet);
    bullet->move();
}
//TODO
void Tower::targetKilled(){
    if(m_attackedEnemy)
        m_attackedEnemy=NULL;
    checkEnemyInRange();
    if(!m_attackedEnemy)
        m_fireRateTime->stop();
}
void Tower::loseSightOfEnemy(){
    m_attackedEnemy->getLostSight(this);
    targetKilled();
}
void Tower::checkEnemyInRange(){
    if(m_attackedEnemy){
        if(!collisionWithCircle(m_pos,m_attackRange,m_attackedEnemy->getPos(),1))
            loseSightOfEnemy();
    }
    else{
        QList<Enemy*> enemyList=m_game->getEnemyList();
        foreach(Enemy* enemy,enemyList)
            if(!collisionWithCircle(m_pos,m_attackRange,enemy->getPos(),1)){
                chooseEnemyToAttack(enemy);
                break;
            }
    }
}
Enemy* Tower::getEnemyBeingAttacked(){return m_attackedEnemy;}
