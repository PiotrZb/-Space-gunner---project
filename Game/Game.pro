TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        airlock.cpp \
        bullet.cpp \
        fpscounter.cpp \
        hero.cpp \
        main.cpp \
        menu.cpp \
        movingplatform.cpp \
        scene1.cpp \
        sounds.cpp \
        turret.cpp
        INCLUDEPATH += "C:/sfml/SFML-2.5.1/include"
        LIBS += -L"C:/sfml/SFML-2.5.1/lib"
        CONFIG(debug, debug|release){
            LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
        } else {
            LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
        }

HEADERS += \
    airlock.h \
    bullet.h \
    fpscounter.h \
    hero.h \
    menu.h \
    movingplatform.h \
    scene1.h \
    sounds.h \
    turret.h

RC_ICONS = icon.ico
