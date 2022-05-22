#pragma once

#include "loginwindow/loginwindow.h"
#include "mainwindow/mainwindow.h"
#include <QObject>

class EncloudController : public QObject
{
    Q_OBJECT
public:
    explicit EncloudController();

    void run();


private:
    LoginWindow     *m_loginWindow;
    MainWindow      *m_mainWindow;

signals:

};

