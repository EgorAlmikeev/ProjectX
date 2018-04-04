#-------------------------------------------------
#
# Project created by QtCreator 2018-02-19T10:57:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectX
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    MathCore/MathParser.c \
    MathCore/MathUtils.c \
    MathCore/Algorithms/Integral.c \
    Core/CalcThread.cpp \
    Core/Utils.cpp \
    Frames/helpDialogFrame.cpp \
    Frames/integralConstStepFrame.cpp \
    Core/lntegralThreads.cpp \
    Frames/integralFloatingStepFrame.cpp \
    Frames/integralMultipleFrame.cpp

HEADERS  += mainwindow.h \
    MathCore/MathParser.h \
    MathCore/MathUtils.h \
    MathCore/Algorithms/Integral.h \
    Core/CalcThread.h \
    Core/Utils.h \
    X.h \
    Frames/frames.h \
    Frames/helpDialogFrame.h \
    Frames/integralConstStepFrame.h \
    Core/IntegralThreads.h \
    Core/XCore.h \
    MathCore/XMath.h \
    Frames/UIConsts.h \
    Frames/integralFloatingStepFrame.h \
    Frames/integralMultipleFrame.h

FORMS    += mainwindow.ui \
    Frames/helpDialogFrame.ui \
    Frames/integralConstStepFrame.ui \
    Frames/integralFloatingStepFrame.ui \
    Frames/integralMultipleFrame.ui

RESOURCES += \
    res/res.qrc

DISTFILES += \
    res/icon.icns

win32:RC_ICONS = $$PWD/res/icon.ico

macx:ICON = res/icon.icns
