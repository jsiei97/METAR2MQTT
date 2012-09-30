CONFIG += qtestlib
TEMPLATE = app
TARGET = 
DEFINES += private=public

# Test code
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += TestMosq.cpp

# Code to test
DEPENDPATH  += ../../src/
INCLUDEPATH += ../../src/
#SOURCES += ConfigParse.cpp
#SOURCES += Station.cpp
