#pragma once

#include <QWidget>

namespace Ui {
class TaskWindow;
}

class TaskWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWindow(QWidget *parent = nullptr);
    ~TaskWindow();

private:
    Ui::TaskWindow *ui;
};

