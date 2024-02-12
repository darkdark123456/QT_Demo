QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialoglocate.cpp \
    main.cpp \
    mainwindow.cpp \
    qdialoglogin.cpp \
    qwdialogheader.cpp \
    qwdialogsize.cpp

HEADERS += \
    dialoglocate.h \
    mainwindow.h \
    qdialoglogin.h \
    qwdialogheader.h \
    qwdialogsize.h

FORMS += \
    dialoglocate.ui \
    mainwindow.ui \
    qdialoglogin.ui \
    qwdialogheader.ui \
    qwdialogsize.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
