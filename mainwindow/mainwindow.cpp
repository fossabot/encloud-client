#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include <QStyleOption>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化窗体
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("欢迎使用!!!!");

    connect(ui->siderWdiget, &MainWindowSiderWidget::newIndx,
            ui->stackWidget, &MainWindowStackWidget::setCurrentPage);

    connect(ui->siderWdiget, &MainWindowSiderWidget::newString,
            ui->titleWdiget, &MainWindowTitleWidget::setTitleText);

    connect(ui->titleWdiget,&MainWindowTitleWidget::logoutBtnClicked,[this](){
        //TO-DO清除用户信息安全退出，并发出登出信息号
        emit this->accountLogouted();
    });

    connect(ui->titleWdiget,&MainWindowTitleWidget::accountBtnClicked,[](){
        //TO-DO创建窗口显示用户信息.
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event){
    stdoutput << "主窗口已关闭";
}

