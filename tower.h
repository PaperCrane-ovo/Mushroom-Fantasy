#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QString>
#include <QObject>
#include "mainwindow.h"

class MainWindow;

class tower: QObject {
    Q_OBJECT
public:
    tower(QPoint p, MainWindow *game, QString path = ":/images/images/image1.png");
    tower();
    ~tower();
    void draw(QPainter *p) const;
private:
    QPoint m_pos;
    QString m_path;
    int m_atkRange, atk; //攻击范围和攻击值
    MainWindow *m_game;
    static const QSize m_size;
};

#endif // TOWER_H
