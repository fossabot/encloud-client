#pragma once

#include <QWidget>

namespace Ui {
class LoginWelcomeWidget;
}

class LoginWelcomeWidget : public QWidget{
    Q_OBJECT
public:
    explicit LoginWelcomeWidget(QWidget *parent = nullptr);
    ~LoginWelcomeWidget();

private:
    Ui::LoginWelcomeWidget *ui;
};

