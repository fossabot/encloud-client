#pragma once

#include <QWidget>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

private:
    Ui::RegisterWindow *ui;

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

protected:
    void paintEvent(QPaintEvent *event);


private:
    void registrationProcess();

signals:
    void registrationSuccess(QPair<QString,QString> pair);

};

