QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chess_main.cpp \
    chesspiece.cpp \
    chessuiboard.cpp \
    doublegamechoose.cpp \
    doublewuzichessui.cpp \
    gamechoose.cpp \
    main.cpp \
    mainwindow.cpp \
    settingui.cpp \
    sockettcp.cpp \
    wuzi_chess.cpp \
    wuzichessui.cpp

HEADERS += \
    chess_main.h \
    chesspiece.h \
    chessuiboard.h \
    doublegamechoose.h \
    doublewuzichessui.h \
    gamechoose.h \
    mainwindow.h \
    settingui.h \
    sockettcp.h \
    wuzi_chess.h \
    wuzichessui.h

FORMS += \
    doublegamechoose.ui \
    gamechoose.ui \
    mainwindow.ui \
    settingui.ui \
    wuzichessui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
