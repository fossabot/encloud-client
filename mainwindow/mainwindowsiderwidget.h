#pragma once

#include "common/globalmarco.h"
#include <QWidget>
#include <QToolButton>
namespace Ui {
class MainWindowSiderWidget;
}

class MainWindowSiderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowSiderWidget(QWidget *parent = nullptr);
    ~MainWindowSiderWidget();
protected:

private:
    Ui::MainWindowSiderWidget *ui;
    int  m_currenFunction;
signals:
    void newIndx(int indx);
    void newString(QString name);
public slots:

};

