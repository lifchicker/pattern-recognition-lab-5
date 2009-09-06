# QT +=
TARGET = lab5
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    distribution.cpp \
    distributioninfo.cpp \
    activedistribution.cpp
HEADERS += mainwindow.h \
    distribution.h \
    distributioninfo.h \
    activedistribution.h \
    randomvector.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    .gitignore
