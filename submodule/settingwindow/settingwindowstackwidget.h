#pragma once

#include <QWidget>

namespace Ui {
class SettingWindowStackWidget;
}

class SettingWindowStackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindowStackWidget(QWidget *parent = nullptr);
    ~SettingWindowStackWidget();

private:
    Ui::SettingWindowStackWidget *ui;
};

