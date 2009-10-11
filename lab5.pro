# QT +=
TARGET = lab5
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    distribution.cpp \
    selection.cpp \
    classifier.cpp \
    bayesianclassifier.cpp \
    distributionparameters.cpp
HEADERS += mainwindow.h \
    distribution.h \
    randomvector.h \
    selection.h \
    classifier.h \
    bayesianclassifier.h \
    distributionparameters.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    .gitignore
