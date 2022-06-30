#include "menu.h"
#include <QString>
#include <QPoint>
#include <QPainter>
#include "mainwindow.h"
#include "ui_menu.h"
class MainWindow;
Menu::Menu(QWidget* parent):QWidget(parent),ui(new Ui::menu){
    ui->setupUi(this);
}
Menu::~Menu(){delete ui;}
void Menu::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QString path(":/images/begin.png");
    painter.drawPixmap(0,0,970,728,path);
}
void Menu::mousePressEvent(QMouseEvent*event){
    QPoint pos=event->pos();
    if(event->button()==Qt::LeftButton){
        if(pos.x()<434&&pos.x()>193&&pos.y()<441&&pos.y()>336){
            MainWindow* mainwindow=new MainWindow();
            mainwindow->resize(QSize(970,728));
            mainwindow->show();
        }
        if(pos.x()<434&&pos.x()>193&&pos.y()<568&&pos.y()>485)
            exit(0);
    }
}
