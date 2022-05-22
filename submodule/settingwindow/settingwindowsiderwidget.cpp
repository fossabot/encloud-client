#include "settingwindowsiderwidget.h"
#include "ui_settingwindowsiderwidget.h"

SettingWindowSiderWidget::SettingWindowSiderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindowSiderWidget)
{
    ui->setupUi(this);
}

SettingWindowSiderWidget::~SettingWindowSiderWidget()
{
    delete ui;
}
