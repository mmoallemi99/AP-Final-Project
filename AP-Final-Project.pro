#-------------------------------------------------
#
# Project created by QtCreator 2019-05-12T21:39:46
#
#-------------------------------------------------

QT       += core gui sql widgets uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AP-Final-Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
l
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    authentication.cpp \
    product.cpp \
    index.cpp \
    shop.cpp \
    credit_manager.cpp \
    user.cpp

RESOURCES =


HEADERS += \
    authentication.h \
    index.h \
    product.h \
    shop.h \
    credit_manager.h \
    user.h


FORMS += \
    new_product.ui \
    authentication.ui \
    index.ui \
    shop.ui \
    credit_manager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
