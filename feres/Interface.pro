QT       += core gui sql network charts printsupport
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += "C:\Build-OpenSSL-VC-32\include"
CONFIG += c++11
CONFIG -= app_bundle

OPENSSL_LIBS='-L/opt/ssl/lib -lssl -lcrypto'

include( $$PWD/../SMTPClient/SMTPClient.pri )
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SMTPClient/email.cpp \
    SMTPClient/emailaddress.cpp \
    SMTPClient/smtpclient.cpp \
    classe.cpp \
    connexion.cpp \
    eleve.cpp \
    food.cpp \
    main.cpp \
    mainwindow.cpp \
    stock.cpp
HEADERS += \
    SMTPClient/email.h \
    SMTPClient/emailaddress.h \
    SMTPClient/smtpclient.h \
    classe.h \
    connexion.h \
    eleve.h \
    food.h \
    mainwindow.h \
    stock.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    ressource.qrc
