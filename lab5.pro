# QT +=
TARGET = lab5
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    distribution.cpp \
    ../lab_tmp/lab5/distributioninfo.cpp
HEADERS += mainwindow.h \
    distribution.h \
    ../lab_tmp/lab5/distributioninfo.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    .gitignore
