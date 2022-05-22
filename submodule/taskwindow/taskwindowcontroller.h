#pragma once

#include <QWidget>

namespace Ui {
class TaskWindowController;
}

class TaskWindowController : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWindowController(QWidget *parent = nullptr);
    ~TaskWindowController();

private:
    Ui::TaskWindowController *ui;
};

