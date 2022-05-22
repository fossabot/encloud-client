#pragma once

#include <QWidget>
#include "loginwindow.h"
namespace Ui {
class LoginTitleWidget;
}

class LoginTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginTitleWidget(QWidget *parent = nullptr);
    ~LoginTitleWidget();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::LoginTitleWidget *ui;
    QPoint m_pt;
    QWidget *m_parent;
};

