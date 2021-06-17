QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ahp_method.cpp \
    alternativesdialog.cpp \
    criteria.cpp \
    criteriaaandalternativesdialog.cpp \
    criteriaform.cpp \
    decision.cpp \
    main.cpp \
    mainwindow.cpp \
    widget.cpp

HEADERS += \
    ahp_method.h \
    alternativesdialog.h \
    criteria.h \
    criteriaaandalternativesdialog.h \
    criteriaform.h \
    decision.h \
    mainwindow.h \
    widget.h

FORMS += \
    alternativesdialog.ui \
    criteriaaandalternativesdialog.ui \
    criteriaform.ui \
    mainwindow.ui \
    widget.ui

INCLUDEPATH += "D:\Programming\eigen-3.3.9\eigen-3.3.9"
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
