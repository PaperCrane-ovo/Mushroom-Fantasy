#ifndef PATHS_H
#define PATHS_H
#include <QMap>
#include <QString>
QVector<QString> enemyPaths={":/images/enemy1.png",":/images/enemy2.png",":/images/enemy3.png",":/images/enemy4.png"};
QVector<QString> towerPaths={":/images/tower1.png",":/images/tower2.png"};
QMap<QString,QString> WinOrLossPaths {{"lose",":/images/lose.png"},{"win",":/images/win.png"}};
#endif // PATHS_H
