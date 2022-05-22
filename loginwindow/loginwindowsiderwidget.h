#pragma once

#include <QWidget>

namespace Ui {
class LoginWindowSiderWidget;
}

class LoginWindowSiderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindowSiderWidget(QWidget *parent = nullptr);
    ~LoginWindowSiderWidget();

public:
    void setText(QString str);

signals:
    void clicked(bool check=false);

private:
    Ui::LoginWindowSiderWidget *ui;
};


