# QT +=
TARGET = lab5
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    distribution.cpp \
    bayesianclassifier.cpp \
    distributionparameters.cpp
HEADERS += mainwindow.h \
    distribution.h \
    classifier.h \
    bayesianclassifier.h \
    distributionparameters.h \
    matrix/include/matrix.h
FORMS += mainwindow.ui
OTHER_FILES += README \
    .gitignore
