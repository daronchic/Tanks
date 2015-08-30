TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    level.cpp


LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += C:/SFML-master/include
DEPENDPATH += C:/SFML-master/include

HEADERS += \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    level.h
