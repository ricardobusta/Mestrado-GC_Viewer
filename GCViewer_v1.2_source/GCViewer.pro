#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T12:27:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Geometria
TEMPLATE = app


SOURCES += \
    main.cpp\
    rendering/scene.cpp \
    rendering/sceneobject.cpp \
    rendering/sceneconvexhull.cpp \
    rendering/scenepointcloud.cpp \
    rendering/scenetetrahedrons.cpp \
    rendering/geometry.cpp \
    rendering/scenetext.cpp \
    interface/application.cpp \
    interface/glwidget.cpp \
    interface/mainwindow.cpp \
    interface/objectcontrolwidget.cpp \
    ric.cpp

HEADERS  += \
    rendering/scene.h \
    rendering/sceneobject.h \
    rendering/sceneconvexhull.h \
    rendering/scenepointcloud.h \
    rendering/scenetetrahedrons.h \
    rendering/geometry.h \
    rendering/scenetext.h \
    interface/application.h \
    interface/glwidget.h \
    interface/mainwindow.h \
    interface/objectcontrolwidget.h \
    ric.h

FORMS    += \
    interface/mainwindow.ui \
    interface/objectcontrolwidget.ui

OTHER_FILES += \
    HULL2D.txt \
    HULL3D.txt \
    INPUT2D.txt \
    INPUT3D.txt \
    TETRA2D.txt \
    TETRA3D.txt \

