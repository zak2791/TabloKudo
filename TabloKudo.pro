RC_ICONS = kudo.ico

QT       += core gui multimedia qml quickwidgets svg svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addform.cpp \
    choosingnames.cpp \
    endtime.cpp \
    formsettings.cpp \
    hansoku.cpp \
    lcdstopwatch.cpp \
    lcdtimer.cpp \
    listfamily.cpp \
    main.cpp \
    mainlistmodel.cpp \
    mainwindow.cpp \
    nameandteam.cpp \
    pcscreen.cpp \
    rate.cpp \
    sidelistmodel.cpp \
    svglabel.cpp \
    svgpushbutton.cpp \
    tvscreen.cpp

HEADERS += \
    addform.h \
    choosingnames.h \
    endtime.h \
    formsettings.h \
    hansoku.h \
    lcdstopwatch.h \
    lcdtimer.h \
    listfamily.h \
    listview.h \
    mainlistmodel.h \
    mainwindow.h \
    nameandteam.h \
    pcscreen.h \
    rate.h \
    sidelistmodel.h \
    svglabel.h \
    svgpushbutton.h \
    tvscreen.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    addform.ui \
    code.ui \
    formsettings.ui \
    hans.ui \
    mainwindow.ui \
    settings_window.ui

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

RESOURCES += \
    resources.qrc

DISTFILES +=

TRANSLATIONS = languages/language_en.ts
