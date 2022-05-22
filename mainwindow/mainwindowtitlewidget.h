#pragma once

#include "common/globalmarco.h"
#include <QWidget>

namespace Ui {
class MainWindowTitleWidget;
}

class MainWindowTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowTitleWidget(QWidget *parent = nullptr);
    ~MainWindowTitleWidget();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::MainWindowTitleWidget *ui;
    QPoint  m_pt;
    QWidget *m_parent;
    bool    m_isMaxSize;
public slots:
    void setTitleText(QString content);
signals:
    void closeBtnClicked();
    void showMaximizeBtnClicked();
    void showMinimumSizeClicked();
    void accountBtnClicked();
    void logoutBtnClicked();
};

