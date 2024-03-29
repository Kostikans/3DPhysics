#-------------------------------------------------
#
# Project created by QtCreator 2019-09-04T15:56:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursachh
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/camera.cpp \
        src/collisiondetector.cpp \
        src/contact.cpp \
        src/floor.cpp \
        src/gravity.cpp \
        src/light.cpp \
        src/main.cpp \
        src/primitive.cpp \
        src/rigidbody.cpp \
        src/scenenode.cpp \
        src/sphereobj.cpp \
        src/widget.cpp

HEADERS += \
        src\camera.h \
        collisiondetector.h \
        contact.h \
        floor.h \
        gravity.h \
        light.h \
        primitive.h \
        rigidbody.h \
        scenenode.h \
        sphereobj.h \
        widget.h

LIBS += -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    fshader.frag \
    light.frag \
    light.vert \
    vshader.vert

RESOURCES += \
    shaders.qrc
