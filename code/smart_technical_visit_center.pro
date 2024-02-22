QT       += core gui sql
QT       += core gui charts
QT       += core gui printsupport
QT       += core gui multimedia multimediawidgets
QT       += core gui serialport



#mailing
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
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
    addservice.cpp \
    ajouter.cpp \
    centre.cpp \
    fidele2.cpp \
    lanmessage.cpp \
    modifier.cpp \
    modifservice.cpp \
    service.cpp \
    statistique.cpp \
    statservice.cpp \
    dialognickname.cpp \
    messenger.cpp\
    peer.cpp \
    pmwindow.cpp\
    ajout_employes.cpp \
    ajouter_rdvs.cpp \
    ajoutermachine.cpp \
    arduino_employe.cpp \
    authentification.cpp \
    calender.cpp \
    connexion.cpp \
    drilldownslice.cpp \
    employe.cpp \
    historique.cpp \
    machine.cpp \
    machinestatuswindow.cpp \
    main.cpp \
    mainwindow.cpp \
    modifier_employes.cpp \
    modifier_rdv.cpp \
    modifiermachine.cpp \
    rdv.cpp \
    rdv_arduino.cpp \
    smtp.cpp \
    stat_combo.cpp \
    stat_rdv.cpp \
    statmachine.cpp \
    vehicule.cpp \
    videoplayer.cpp

HEADERS += \
 addservice.h \
    ajouter.h \
    centre.h \
    fidele2.h \
    lanmessage.h \
    modifier.h \
    modifservice.h \
    service.h \
    statistique.h \
    statservice.h\
    dialognickname.h\
    messenger.h\
   peer.h\
   pmwindow.h\
    ajout_employes.h \
    ajouter_rdvs.h \
    ajoutermachine.h \
    arduino_employe.h \
    authentification.h \
    calender.h \
    connexion.h \
    drilldownslice.h \
    employe.h \
    historique.h \
    machine.h \
    machinestatuswindow.h \
    mainwindow.h \
    modifier_employes.h \
    modifier_rdv.h \
    modifiermachine.h \
    rdv.h \
    rdv_arduino.h \
    smtp.h \
    stat_combo.h \
    stat_rdv.h \
    statmachine.h \
    vehicule.h \
    videoplayer.h

FORMS += \
    ajout_employes.ui \
    ajouter.ui \
    ajouter_rdvs.ui \
    ajoutermachine.ui \
    authentification.ui \
    calender.ui \
    historique.ui \
    machinestatuswindow.ui \
    mainwindow.ui \
    modifier.ui \
    modifier_employes.ui \
    modifier_rdv.ui \
    modifiermachine.ui \
    stat_combo.ui \
    stat_rdv.ui \
    statistique.ui \
    statmachine.ui \
    videoplayer.ui \
    addservice.ui \
    modifservice.ui \
    statservice.ui \
    dialognickname.ui \
    pmwindow.ui \
    fidele2.ui \
    lanmessage.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
