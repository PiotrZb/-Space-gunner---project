TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        airlock.cpp \
        asteroid.cpp \
        bullet.cpp \
        fpscounter.cpp \
        gameover.cpp \
        hero.cpp \
        hud.cpp \
        main.cpp \
        menu.cpp \
        movingplatform.cpp \
        scene1.cpp \
        soldier.cpp \
        sounds.cpp \
        turret.cpp
        INCLUDEPATH += "C:/sfml/SFML-2.5.1/include"
        LIBS += -L"C:/sfml/SFML-2.5.1/lib"
        CONFIG(debug, debug|release){
            LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
        } else {
            LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
        }
        RC_ICONS = icon.ico

HEADERS += \
    airlock.h \
    asteroid.h \
    bullet.h \
    fpscounter.h \
    gameover.h \
    hero.h \
    hud.h \
    menu.h \
    movingplatform.h \
    scene1.h \
    soldier.h \
    sounds.h \
    turret.h
