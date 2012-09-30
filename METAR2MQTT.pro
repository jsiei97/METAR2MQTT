TEMPLATE = app
QT += xml 
TARGET = 
DEPENDPATH += src 
INCLUDEPATH += src

# Input
SOURCES += src/main.cpp 

HEADERS += src/metar.h
SOURCES += src/metar.cpp 

SOURCES += src/ConfigParse.cpp
HEADERS += src/ConfigParse.h

SOURCES += src/Station.cpp
HEADERS += src/Station.h
