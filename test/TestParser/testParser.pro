CONFIG += qtestlib
TEMPLATE = app
QT += xml 
TARGET = 
DEFINES += private=public

# Test code
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += TestParser.cpp

# Code to test
DEPENDPATH  += ../../src/
INCLUDEPATH += ../../src/
SOURCES += metar.cpp
