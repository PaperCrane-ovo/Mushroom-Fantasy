#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu w;
    w.resize(970,728);
    w.show();
    return a.exec();
}
