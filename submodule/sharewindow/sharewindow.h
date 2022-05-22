#pragma once

#include <QWidget>

namespace Ui {
class ShareWindow;
}

class ShareWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShareWindow(QWidget *parent = nullptr);
    ~ShareWindow();

private:
    Ui::ShareWindow *ui;
};

