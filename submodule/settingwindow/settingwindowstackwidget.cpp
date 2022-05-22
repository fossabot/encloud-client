#include "settingwindowstackwidget.h"
#include "ui_settingwindowstackwidget.h"

SettingWindowStackWidget::SettingWindowStackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindowStackWidget)
{
    ui->setupUi(this);
}

SettingWindowStackWidget::~SettingWindowStackWidget()
{
    delete ui;
}
