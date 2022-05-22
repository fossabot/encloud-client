#include "taskwindowcontroller.h"
#include "ui_taskwindowcontroller.h"
TaskWindowController::TaskWindowController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWindowController)
{
    ui->setupUi(this);
}

TaskWindowController::~TaskWindowController()
{
    delete ui;
}
