#pragma once

#include "mainwindow/mainwindow.h"
#include <QWidget>
#include <QTimer>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void loginProcess();

private:
    Ui::LoginWindow *ui;
signals:
    void loginSuccessfully();
};


