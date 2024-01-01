QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IncomingPost.cpp \
    Post.cpp \
    main.cpp \
    network.cpp \
    postdialog.cpp \
    socialnetworkwindow.cpp \
    user.cpp

HEADERS += \
    IncomingPost.h \
    Post.h \
    network.h \
    postdialog.h \
    socialnetworkwindow.h \
    user.h

FORMS += \
    postdialog.ui \
    socialnetworkwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    posts.txt \
    social.txt
