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
	./inc

HEADERS += \
	main/application.h \
	inc/internal.h \
	inc/stHeader.h \
	inc/GenUtils.h \
	inc/FrameWork.h \
	inc/ObjectMgr.h \
	inc/StyleSheet.h \
	control/ControlerMain.h \
	control/HomePageControl.h \
	control/MainFrameControl.h \
	control/WorkMainControl.h \
	control/ToolStatusControl.h \
	widget/HomePageView.h \
	widget/MainFrameView.h \
	widget/WorkMainView.h \
	widget/ToolStatusView.h \ 
	widget/BottomMenuView.h \
	inc/test/FuncTest.h \
	inc/test/ThreadTest.h \
	inc/elsNet/elsHeader.h \
	inc/elsNet/elsServer.h \
	inc/elsNet/elsBaseAdapter.h \
	inc/elsNet/elsDataAdapter.h \

SOURCES += \
	main/main.cpp \
	main/application.cpp \
	inc/GenUtils.cpp \
	inc/FrameWork.cpp \
	inc/ObjectMgr.cpp \
	inc/StyleSheet.cpp \
	control/ControlerMain.cpp \
	control/HomePageControl.cpp \
	control/MainFrameControl.cpp \
	control/WorkMainControl.cpp \
	control/ToolStatusControl.cpp \
	widget/HomePageView.cpp \
	widget/MainFrameView.cpp \
	widget/WorkMainView.cpp \
	widget/ToolStatusView.cpp \
	widget/BottomMenuView.cpp \
	inc/test/FuncTest.cpp \
	inc/test/ThreadTest.cpp \
	inc/elsNet/elsServer.cpp \
	inc/elsNet/elsBaseAdapter.cpp \
	inc/elsNet/elsDataAdapter.cpp \

#RESOURCES += \
#	res/QDemo1.qrc

CODECFORTR  = UTF-8
CODECFORSRC = UTF-8

#TRANSLATIONS = res/translations/style_en.ts \
#        res/translations/style_zh_CN.ts
