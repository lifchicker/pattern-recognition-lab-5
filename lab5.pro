# QT +=
TARGET = lab5
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    distribution.cpp \
    distributioninfo.cpp \
    activedistribution.cpp \
    selection.cpp \
    classifier.cpp \
    bayesianclassifier.cpp
HEADERS += mainwindow.h \
    distribution.h \
    distributioninfo.h \
    randomvector.h \
    activedistribution.h \
    selection.h \
    classifier.h \
    bayesianclassifier.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    .gitignore
