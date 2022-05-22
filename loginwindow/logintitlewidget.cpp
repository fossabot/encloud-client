#include "logintitlewidget.h"
#include "ui_logintitlewidget.h"
#include <QMouseEvent>

LoginTitleWidget::LoginTitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginTitleWidget)
{
    ui->setupUi(this);
    this->m_parent = parent;
    connect(ui->minimizeBtn, &QToolButton::clicked , [=](bool checked){
       m_parent->showMinimized();
    });
    connect(ui->closeBtn, &QToolButton::clicked , [=](bool checked){
       m_parent->close();
    });
}

LoginTitleWidget::~LoginTitleWidget(){
    delete ui;
}

void LoginTitleWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        m_parent->move(event->globalPosition().toPoint() - m_pt);
    }
}

void LoginTitleWidget::mousePressEvent(QMouseEvent *event){
    // 如果鼠标左键按下
    if(event->button() == Qt::LeftButton){
        m_pt = event->globalPosition().toPoint() - m_parent->geometry().topLeft();
    }
}
