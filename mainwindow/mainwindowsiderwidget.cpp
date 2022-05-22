#include "mainwindowsiderwidget.h"
#include "ui_mainwindowsiderwidget.h"
#include <QSignalMapper>

MainWindowSiderWidget::MainWindowSiderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindowSiderWidget)
{
    ui->setupUi(this);
    //设置按键
    m_currenFunction = 0;
    ui->fileBtn->setChecked(true);
    QSignalMapper* sm = new QSignalMapper(this);
    void (QSignalMapper::*p)(void) = &QSignalMapper::map;
    QToolButton* buttons[5] = {
        ui->fileBtn,ui->taskBtn,ui->shareBtn,
        ui->friendBtn,ui->groupBtn};
    for(int i = 0 ; i< 5 ;++i){
        connect(buttons[i], &QToolButton::clicked, sm, p);
        sm->setMapping(buttons[i], i);
    }
    connect(sm, &QSignalMapper::mappedInt, [this,buttons](int indx){
        stdoutput << indx;
        if(m_currenFunction != indx ){
           buttons[m_currenFunction]->setChecked(false);
           m_currenFunction = indx;
           emit this->newIndx(indx);
           emit this->newString(buttons[indx]->text());
        }
    });

}

MainWindowSiderWidget::~MainWindowSiderWidget()
{
    delete ui;
}

