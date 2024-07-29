QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets

TARGET = Demo1
TEMPLATE = app

#CONFIG += c++11 console
#CONFIG -= app_bundle

DEFINES += QT_MESSAGELOGCONTEXT

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0		

win32:{
        PlatformFolder = win32
        LIBS += -lws2_32

        QMAKE_CXXFLAGS += -std=c++11
        QMAKE_CXXFLAGS += -std=c++14

        QMAKE_LFLAGS_RELEASE += /MAP
        QMAKE_CFLAGS_RELEASE += /Zi
        QMAKE_LFLAGS_RELEASE += /debug /opt:ref

        CONFIG(debug, debug|release){
            message("D***** win32 version")
        }
        else{
            message("R***** win32 version")
        }        
}

unix:!macx:{
        PlatformFolder = linux

        QMAKE_LFLAGS += -no-pie
        QMAKE_CXXFLAGS += -std=c++11
        QMAKE_CXXFLAGS += -std=c++14
        CONFIG(debug, debug|release){
            message("D***** linux version")
        }
        else{
            message("R***** linux version")
        }
}

DESTDIR = $$PWD/./bin/$$PlatformFolder

INCLUDEPATH += \
        ./inc \
        ./interface

HEADERS += \
        inc/internal.h \
        inc/stheader.h \
        interface/IMgrObject.h \
        interface/IMgrService.h \
        framework/ObjectMgr.h \
        framework/GenUtils.h \
        framework/AppConfig.h \
        framework/FrameWork.h \
        framework/ObjectServiceLocator.h \
        main/application.h \

SOURCES += \
        main/main.cpp \
        main/application.cpp \
        framework/ObjectMgr.cpp \
        framework/GenUtils.cpp \
        framework/AppConfig.cpp \
        framework/FrameWork.cpp \

#RESOURCES += \
#	res/QDemo1.qrc

CODECFORTR  = UTF-8
CODECFORSRC = UTF-8

#TRANSLATIONS = res/translations/style_en.ts \
#        res/translations/style_zh_CN.ts
