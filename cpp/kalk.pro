#-------------------------------------------------
#
# Project created by QtCreator 2018-06-04T13:47:47
# Improved by Timmmmmmmmmmmmmmmy
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kalk
TEMPLATE = app

# Enables C++11
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    model/datatypes/Matrix.cpp \
    model/datatypes/SparseMatrix.cpp \
    model/DataType.cpp \
#   model/datatypes/Number.cpp \
    view/Widget.cpp \
    view/MatrixBuilder.cpp \
    view/MatrixCreator.cpp \
    view/Keypad.cpp \
    view/KeypadInput.cpp \
    controller/MatrixController.cpp

HEADERS += \
    model/datatypes/Matrix.h \
    model/datatypes/Network.h \
    model/datatypes/SparseMatrix.h \
    model/datatypes/User.h \
    model/DataType.h \
#   model/datatypes/Number.h \
    view/Widget.h \
    view/MatrixBuilder.h \
    view/MatrixCreator.h \
    view/Keypad.h \
    view/KeypadInput.h \
    controller/MatrixController.h

RESOURCES += \
    resources.qrc
