#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>

class CheckCodeLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CheckCodeLabel(QWidget *parent = nullptr);
private:
    void setCheckCode();
private:
    void mousePressEvent(QMouseEvent *ev);
signals:

};

