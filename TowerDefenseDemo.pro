QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    enemy.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    tower.cpp \
    towerposition.cpp \
    waypoint.cpp

HEADERS += \
    bullet.h \
    enemy.h \
    menu.h \
    paths.h \
    tower.h \
    towerposition.h \
    mainwindow.h \
    utility.h \
    waypoint.h

FORMS += \
    mainwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    images/Bg.png \
    images/Default.png \
    images/background.jpg \
    images/background1.jpg \
    images/background2.jpg \
    images/background3.jpg \
    images/background4.jpg \
    images/bullet.png \
    images/icon_HP.png \
    images/icon_gold.png \
    images/monster1.png \
    images/open_spot.png \
    images/tower.png \
    images/tower1.jpg \
    images/tower1.png \
    images/tower2.png \
    images/tower3.png
