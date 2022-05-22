#include "filewindownavigator.h"
#include "ui_filewindownavigator.h"
#include <QDebug>

FileWindowNavigator::FileWindowNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWindowNavigator)
{
    ui->setupUi(this);
    auto goProccess = [this](){
        QString currentUri = ui->pathLied->text();
        if(currentUri != m_backStack.top()){
           m_backStack.push(currentUri);
        }
        emit this->pathChanged(currentUri);
    };
    connect(ui->goBtn, &QToolButton::clicked, this, goProccess);
    connect(ui->pathLied, &QLineEdit::returnPressed,this, goProccess);

    connect(ui->homeBtn, &QToolButton::clicked,this, [this](){
        if(ui->pathLied->text() != "/"){
           m_backStack.push("/");
        }
        ui->pathLied->setText("/");
        emit this->pathChanged("/");
    });

    connect(ui->refreshBtn, &QToolButton::clicked, this,[this](){
        emit this->pathChanged(ui->pathLied->text());
    });

    connect(ui->backBtn, &QToolButton::clicked,this,[this](){
        if(m_backStack.size() > 1){
            m_forwardStack.push(m_backStack.pop());
            ui->pathLied->setText(m_backStack.top());
            emit this->pathChanged(m_backStack.top());
        }
    });

    connect(ui->forwardBtn,&QToolButton::clicked,this,[this](){
        if(m_forwardStack.size() >0){
            m_backStack.push(m_forwardStack.pop());
            ui->pathLied->setText(m_backStack.top());
            emit this->pathChanged(m_backStack.top());
        }
    });
}

FileWindowNavigator::~FileWindowNavigator(){
    delete ui;
}

void FileWindowNavigator::setPath(QString newPath){
    m_backStack.push(newPath);
    ui->pathLied->setText(newPath);
}
