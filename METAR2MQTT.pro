TEMPLATE = app
QT += xml 
TARGET = 
DEPENDPATH += src 
INCLUDEPATH += src
LIBS += -lmosquittopp -lmosquitto -lcurl

target.path = /usr/local/bin/
INSTALLS += target

# Input
SOURCES += src/main.cpp 

HEADERS += src/metar.h
SOURCES += src/metar.cpp 

SOURCES += src/ConfigParse.cpp
HEADERS += src/ConfigParse.h

SOURCES += src/Station.cpp
HEADERS += src/Station.h

SOURCES += src/MosqConnect.cpp
HEADERS += src/MosqConnect.h
