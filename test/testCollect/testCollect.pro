CONFIG += qtestlib
TEMPLATE = app
TARGET = 
DEFINES += private=public

# Test code
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += TestCollect.cpp

# Code to test
DEPENDPATH  += ../../src/
INCLUDEPATH += ../../src/
SOURCES += CollectMETAR.cpp

