#include "mainwindowtitlewidget.h"
#include "ui_mainwindowtitlewidget.h"
#include <QMouseEvent>
MainWindowTitleWidget::MainWindowTitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindowTitleWidget)
{
    //初始化
    ui->setupUi(this);
    this->showMinimized();
    m_parent = parent;
    m_isMaxSize = false;

    //处理最小化
    connect(ui->minBtn, &QToolButton::clicked, [=](){
        m_parent->showMinimized();
    });

    //处理最大化
    connect(ui->maxBtn, &QToolButton::clicked, [=](){
        stdoutput   << "大小状态" << m_isMaxSize;
        if(m_isMaxSize == false){
            m_parent->showMaximized();
            m_isMaxSize = true;
        }else{
            m_parent->showNormal();
            m_isMaxSize = false;
        }
    });

    //处理关闭
    connect(ui->closeBtn, &QToolButton::clicked, [=](){
        m_parent->close();
    });

    //处理用户
    connect(ui->accountBtn, &QToolButton::clicked, [=](){
       emit this->accountBtnClicked();
    });
    //处理登出
    connect(ui->logoutBtn, &QToolButton::clicked, [=](){
       emit this->logoutBtnClicked();
    });
}


MainWindowTitleWidget::~MainWindowTitleWidget()
{
    delete ui;
}
void MainWindowTitleWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        m_parent->move(event->globalPosition().toPoint() - m_pt);
    }
}

void MainWindowTitleWidget::mousePressEvent(QMouseEvent *event){
    // 如果鼠标左键按下
    if(event->button() == Qt::LeftButton){
        m_pt = event->globalPosition().toPoint() - m_parent->geometry().topLeft();
    }
}

void MainWindowTitleWidget::setTitleText(QString content){
    ui->titleLabel->setText(content);
}
