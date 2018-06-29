TEMPLATE = app
TARGET = Kalk
INCLUDEPATH += .

CONFIG += c++11

# Input
HEADERS += DataType.h \
           datatypes/Matrix.h \
           datatypes/Network.h \
           datatypes/Number.h \
           datatypes/SparseMatrix.h \
           datatypes/SquareMatrix.h \
           datatypes/User.h
SOURCES += DataType.cpp \
           main.cpp \
           datatypes/Matrix.cpp \
           datatypes/Network.cpp \
           datatypes/Number.cpp \
           datatypes/SparseMatrix.cpp \
           datatypes/SquareMatrix.cpp \
           datatypes/User.cpp
