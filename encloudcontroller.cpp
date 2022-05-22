#include "encloudcontroller.h"
#include "loginwindow/loginwindow.h"
#include "mainwindow/mainwindow.h"
#include <iostream>
#include <functional>
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QIcon>
EncloudController::EncloudController(){
    m_loginWindow = new LoginWindow();
    connect(m_loginWindow, &LoginWindow::loginSuccessfully, [this](){
       m_mainWindow = new MainWindow();
       connect(m_mainWindow,&MainWindow::accountLogouted,[this](){
          m_mainWindow->close();
          m_mainWindow->deleteLater();
          m_loginWindow->show();
       });
       m_mainWindow->show();
    });
}

void EncloudController::run()
{

    m_loginWindow->show();
    return;
}
