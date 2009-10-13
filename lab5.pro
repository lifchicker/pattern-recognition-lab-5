# QT +=
TARGET = lab5
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    distribution.cpp \
    selection.cpp \
    bayesianclassifier.cpp \
    distributionparameters.cpp \
    mathfunctions.cpp
HEADERS += mainwindow.h \
    distribution.h \
    randomvector.h \
    selection.h \
    classifier.h \
    bayesianclassifier.h \
    distributionparameters.h \
    mathfunctions.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    .gitignore
