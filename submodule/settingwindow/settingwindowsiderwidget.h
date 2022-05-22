#pragma once

#include <QWidget>

namespace Ui {
class SettingWindowSiderWidget;
}

class SettingWindowSiderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindowSiderWidget(QWidget *parent = nullptr);
    ~SettingWindowSiderWidget();

private:
    Ui::SettingWindowSiderWidget *ui;
};

