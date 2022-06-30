#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "towerposition.h"
#include "enemy.h"
#include "paths.h"
#include <cmath>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_playerHp(5)
    ,m_playerGold(300),m_waves(0),m_gameWin(false),m_gameLose(false)
{
    ui->setupUi(this);
    addWayPoint();
    loadTowerPosition();
    QTimer* timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(25);
    QTimer::singleShot(1000,this,SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QString path(":/images/map1.png");
    if(m_gameLose||m_gameWin){
        QString path(m_gameLose?WinOrLossPaths["lose"]:WinOrLossPaths["win"]);
        QPainter painter(this);
        painter.drawPixmap(0,0,970,728,path);
        return;
    }
    painter.drawPixmap(0,0,970,728,path);
    //drawPixmap的前四个参数代表的分别是，图片左上角的横坐标，图片左上角的纵坐标，图片的width，图片的height。我们一般把width和height，与图片的真实大小匹配起来
    foreach(const wayPoint* waypoint,m_wayPointList)
        waypoint->draw(&painter);

    foreach(TowerPos towerposition,m_towerPosList)
        if(!towerposition.hasTower())
            towerposition.draw(&painter);

    foreach(const Tower* tower,m_towerList)
        tower->draw(&painter);
    foreach(const Enemy* enemy,m_enemyList)
        enemy->draw(&painter);
    foreach(const Bullet* bullet,m_bulletList)
        bullet->draw(&painter);
    drawHp(&painter);
    drawGold(&painter);
    drawWaves(&painter);
    if(!canBuyTower())
        drawLackOfMoney(&painter);
}

void MainWindow::addWayPoint(){
    wayPoint* waypoint1 = new wayPoint(QPoint(91, 1));
    m_wayPointList.push_back(waypoint1);

    wayPoint* waypoint2 = new wayPoint(QPoint(91, 151));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(824, 160));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(825, 370));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(96, 377));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(95, 577));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(765, 577));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);
}

void MainWindow::loadTowerPosition(){
    QPoint pos[]={
        QPoint(180,238), QPoint(286, 238),
        QPoint(398, 238), QPoint(518,238),
        QPoint(638, 238), QPoint(740,238),
        QPoint(638,64), QPoint(733,64),
        QPoint(836,64), QPoint(914,64),
        QPoint(913, 172),QPoint(913,287),
        QPoint(184,460),QPoint(278,460),
        QPoint(383,460),QPoint(465,460),QPoint(565,460)
    };
    int len = sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
        m_towerPosList.push_back(pos[i]);
}

void MainWindow::mousePressEvent(QMouseEvent* event){
    QPoint pressPos=event->pos();
    auto it=m_towerPosList.begin();
    while(it!=m_towerPosList.end()){
        if(Qt::LeftButton==event->button()){
            if(it->containPos(pressPos) && !(it->hasTower())){
                if(!canBuyTower())return;
                srand(time(0));
                Tower* tower=new Tower(it->getPos(),m_waves*1.5+10,1000-m_waves*15, this,towerPaths[rand()%2]);
                m_towerList.push_back(tower);
                m_playerGold-=300+int(m_waves*0.8);
                it->setHasTower(true);
                update();
                break;
            }
        }
        it++;
    }
}
void MainWindow::getHpDamaged(){m_playerHp-=1;if(m_playerHp<=0)m_gameLose=true;}
void MainWindow::awardGold(){m_playerGold+=m_waves==0?350:50;}
void MainWindow::removeEnemy(Enemy* enemy){
    Q_ASSERT(enemy);//断言,判断指针为真
    foreach(Tower* tower,m_towerList){
        if(tower->getEnemyBeingAttacked()==enemy)
            tower->targetKilled();
    }

    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty()){
        m_waves++;
        if(!loadWaves())m_gameWin=true;
    }
}
QList<Enemy*> MainWindow::getEnemyList(){return m_enemyList;}

bool MainWindow::canBuyTower(){return m_playerGold>=300+m_waves*0.8;}
bool MainWindow::loadWaves(){
    srand(time(0));
    if(m_waves>=12)return false;
    for(int i=0;i<=m_waves;i++){
        wayPoint* firstWayPoint;
        firstWayPoint=m_wayPointList.first();
        Enemy* enemy=new Enemy(firstWayPoint,40+exp(double(m_waves)),2+m_waves*0.1,this,enemyPaths[rand()%4]);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(i*1500+1000,enemy,SLOT(doActive()));
    }
    return true;
}
void MainWindow::gameStart(){loadWaves();}
void MainWindow::updateMap(){
    foreach(Enemy* enemy,m_enemyList)
        enemy->move();
    foreach(Tower* tower,m_towerList)
        tower->checkEnemyInRange();
    update();
}
void MainWindow::removeBullet(Bullet* bullet){m_bulletList.removeOne(bullet);delete bullet;}
void MainWindow::addBullet(Bullet* bullet){m_bulletList.push_back(bullet);}
void MainWindow::drawHp(QPainter*painter)const{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(30,30,141,39),QString("HP:%1").arg(m_playerHp));
    painter->restore();
}
void MainWindow::drawGold(QPainter* painter)const{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(313,30,141,39),QString("Gold:%1").arg(m_playerGold));
    painter->restore();
}
void MainWindow::drawWaves(QPainter* painter)const{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(558,30,141,39),QString("Waves:%1").arg(m_waves+1));
    painter->restore();
}
void MainWindow::drawLackOfMoney(QPainter* painter)const{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(785,30,141,39),QString("金钱不足!"));
    painter->restore();
}
