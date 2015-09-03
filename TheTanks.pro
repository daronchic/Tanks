TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    level.cpp \
    entity.cpp \
    player.cpp \
    game.cpp


unix {
    LIBS += -L$pwd//3rdParty/linux/SFML-2.3.1/lib/
    INCLUDEPATH += $pwd//3rdParty/linux/SFML-master/SFML/include/
    DEPENDPATH += $pwd//3rdParty/linux/SFML-master/SFML/include/
}
win32 {
    LIBS += -LC:\Users\Doerty\Documents\TheTanks\3rdParty\windows\SFML\lib
    INCLUDEPATH += "C:\Users\Doerty\Documents\TheTanks\3rdParty\windows\SFML-master\include"
    DEPENDPATH += "C:\Users\Doerty\Documents\TheTanks\3rdParty\windows\SFML-master\include"
}
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

HEADERS += \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    level.h \
    view.h \
    entity.h \
    player.h \
    game.h
