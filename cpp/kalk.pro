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
    model/DataType.cpp \
    model/datatypes/Matrix.cpp \
    model/datatypes/SquareMatrix.cpp \
    model/datatypes/SparseMatrix.cpp \
    model/datatypes/User.cpp \
    model/datatypes/Network.cpp \
    view/KeypadInput.cpp \
    view/Widget.cpp \
    view/MatrixBuilder.cpp \
    view/MatrixKalk.cpp \
    view/SquareMatrixKalk.cpp \
    view/SparseMatrixKalk.cpp \
    view/NetworkManager.cpp \
    controller/MatrixController.cpp \
    controller/SquareMatrixController.cpp \
    controller/SparseMatrixController.cpp \
    controller/NetworkController.cpp \
    exceptions/KalkException.cpp \
    exceptions/IndexOutOfBoundsException.cpp \
    exceptions/ZeroMultiplierException.cpp \
    exceptions/InvalidMatrixIndexes.cpp \
    exceptions/NullPointerException.cpp \
    exceptions/InvalidMatrixTypeException.cpp \
    exceptions/InvalidLayoutException.cpp

HEADERS += \
    model/DataType.h \
    model/datatypes/Matrix.h \
    model/datatypes/SquareMatrix.h \
    model/datatypes/SparseMatrix.h \
    model/datatypes/Network.h \
    model/datatypes/User.h \
    view/KeypadInput.h \
    view/Widget.h \
    view/MatrixBuilder.h \
    view/MatrixKalk.h \
    view/SquareMatrixKalk.h \
    view/SparseMatrixKalk.h \
    view/NetworkManager.h \
    controller/MatrixController.h \
    controller/SquareMatrixController.h \
    controller/SparseMatrixController.h \
    controller/NetworkController.h \
    exceptions/KalkException.h \
    exceptions/IndexOutOfBoundsException.h \
    exceptions/ZeroMultiplierException.h \
    exceptions/InvalidMatrixIndexes.h \
    exceptions/NullPointerException.h \
    exceptions/InvalidMatrixTypeException.h \
    exceptions/InvalidLayoutException.h
