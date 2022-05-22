#pragma once

#include <QWidget>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::SettingWindow *ui;
};

