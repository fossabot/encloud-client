QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/cryptographymanager.cpp \
    common/entity/account.cpp \
    common/entity/directory.cpp \
    common/entity/directoryitem.cpp \
    common/entity/downloadtask.cpp \
    common/entity/file.cpp \
    common/entity/group.cpp \
    common/entity/uploadtask.cpp \
    common/message/accountsyncresponse.cpp \
    common/message/adddirectoryrequest.cpp \
    common/message/adddirectoryresponse.cpp \
    common/message/deleterequest.cpp \
    common/message/deleteresponse.cpp \
    common/message/directoryrequest.cpp \
    common/message/directoryresponse.cpp \
    common/message/downloadrequest.cpp \
    common/message/downloadresponse.cpp \
    common/message/loginrequest.cpp \
    common/message/loginresponse.cpp \
    common/entity/message.cpp \
    common/message/messagesyncresponse.cpp \
    common/message/mkdirrequest.cpp \
    common/message/mkdirresponse.cpp \
    common/message/regrequest.cpp \
    common/message/regresponse.cpp \
    common/entity/share.cpp \
    common/message/renamerequest.cpp \
    common/message/renameresponse.cpp \
    common/message/requestbase.cpp \
    common/message/responsebase.cpp \
    common/entity/user.cpp \
    common/globaldatamanager.cpp \
    common/message/uploadFileRequest.cpp \
    common/message/uploadfileresponse.cpp \
    common/message/usersyncresponse.cpp \
    common/messagemanager.cpp \
    common/networkmanager.cpp \
    common/settingmanager.cpp \
    common/storagemanager.cpp \
    encloudcontroller.cpp \
    main.cpp \
    loginwindow/logintitlewidget.cpp \
    loginwindow/loginwelcomewidget.cpp \
    loginwindow/loginwindow.cpp \
    loginwindow/loginwindowmainwidget.cpp \
    loginwindow/loginwindowsiderwidget.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/mainwindowsiderwidget.cpp \
    mainwindow/mainwindowstackwidget.cpp \
    mainwindow/mainwindowtitlewidget.cpp \
    submodule/filewindow/filewindow.cpp \
    submodule/filewindow/filewindownavigator.cpp \
    submodule/filewindow/filewindowtreewidget.cpp \
    submodule/friendwindow/friendwindow.cpp \
    submodule/groupwindow/groupwindow.cpp \
    submodule/registerwindow/checkcodelabel.cpp \
    submodule/registerwindow/registerwindow.cpp \
    submodule/settingwindow/settingwindow.cpp \
    submodule/settingwindow/settingwindowsiderwidget.cpp \
    submodule/settingwindow/settingwindowstackwidget.cpp \
    submodule/sharewindow/sharewindow.cpp \
    submodule/taskwindow/completedpage.cpp \
    submodule/taskwindow/downloadpage.cpp \
    submodule/taskwindow/taskwindow.cpp \
    submodule/taskwindow/uploadpage.cpp \
    test/mytest.cpp \
    test/opensslapitest.cpp \
    test/qtapitest.cpp

HEADERS += \
    common/cryptographymanager.h \
    common/entity/account.h \
    common/entity/directory.h \
    common/entity/directoryitem.h \
    common/entity/downloadtask.h \
    common/entity/file.h \
    common/entity/group.h \
    common/entity/uploadtask.h \
    common/message/accountsyncresponse.h \
    common/message/adddirectoryrequest.h \
    common/message/adddirectoryresponse.h \
    common/message/deleterequest.h \
    common/message/deleteresponse.h \
    common/message/directoryrequest.h \
    common/message/directoryresponse.h \
    common/message/downloadrequest.h \
    common/message/downloadresponse.h \
    common/message/loginrequest.h \
    common/message/loginresponse.h \
    common/entity/message.h \
    common/message/messagesyncresponse.h \
    common/message/mkdirrequest.h \
    common/message/mkdirresponse.h \
    common/message/regrequest.h \
    common/message/regresponse.h \
    common/entity/share.h \
    common/message/renamerequest.h \
    common/message/renameresponse.h \
    common/message/requestbase.h \
    common/message/responsebase.h \
    common/entity/user.h \
    common/globaldatamanager.h \
    common/globalmarco.h \
    common/message/uploadFileRequest.h \
    common/message/uploadfileresponse.h \
    common/message/usersyncresponse.h \
    common/messagemanager.h \
    common/networkmanager.h \
    common/settingmanager.h \
    common/storagemanager.h \
    encloudcontroller.h \
    loginwindow//loginwindow.h \
    loginwindow/logintitlewidget.h \
    loginwindow/loginwelcomewidget.h \
    loginwindow/loginwindowmainwidget.h \
    loginwindow/loginwindowsiderwidget.h \
    mainwindow/mainwindow.h \
    mainwindow/mainwindowsiderwidget.h \
    mainwindow/mainwindowstackwidget.h \
    mainwindow/mainwindowtitlewidget.h \
    submodule/filewindow/filewindow.h \
    submodule/filewindow/filewindownavigator.h \
    submodule/filewindow/filewindowtreewidget.h \
    submodule/friendwindow/friendwindow.h \
    submodule/groupwindow/groupwindow.h \
    submodule/registerwindow/checkcodelabel.h \
    submodule/registerwindow/registerwindow.h \
    submodule/settingwindow/settingwindow.h \
    submodule/settingwindow/settingwindowsiderwidget.h \
    submodule/settingwindow/settingwindowstackwidget.h \
    submodule/sharewindow/sharewindow.h \
    submodule/taskwindow/completedpage.h \
    submodule/taskwindow/downloadpage.h \
    submodule/taskwindow/taskwindow.h \
    submodule/taskwindow/uploadpage.h \
    test/mytest.h \
    test/opensslapitest.h \
    test/qtapitest.h

FORMS += \
    loginwindow/logintitlewidget.ui \
    loginwindow/loginwelcomewidget.ui \
    loginwindow/loginwindow.ui \
    loginwindow/loginwindowmainwidget.ui \
    loginwindow/loginwindowsiderwidget.ui \
    mainwindow/mainwindow.ui \
    mainwindow/mainwindowsiderwidget.ui \
    mainwindow/mainwindowstackwidget.ui \
    mainwindow/mainwindowtitlewidget.ui \
    submodule/filewindow/filewindow.ui \
    submodule/filewindow/filewindownavigator.ui \
    submodule/filewindow/filewindowtreewidget.ui \
    submodule/friendwindow/friendwindow.ui \
    submodule/groupwindow/groupwindow.ui \
    submodule/registerwindow/registerwindow.ui \
    submodule/settingwindow/settingwindow.ui \
    submodule/settingwindow/settingwindowsiderwidget.ui \
    submodule/settingwindow/settingwindowstackwidget.ui \
    submodule/sharewindow/sharewindow.ui \
    submodule/taskwindow/completedpage.ui \
    submodule/taskwindow/downloadpage.ui \
    submodule/taskwindow/taskwindow.ui \
    submodule/taskwindow/uploadpage.ui

LIBS += -lcrypto

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/resource.qrc
