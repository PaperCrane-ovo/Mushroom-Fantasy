#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <mainwindow.h>
namespace Ui{class menu;}
class Menu:public QWidget{
    Q_OBJECT
private:
    Ui::menu * ui;
public:
    explicit Menu(QWidget* parent=nullptr);
    ~Menu();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
};

#endif // MENU_H
