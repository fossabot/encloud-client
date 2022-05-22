#include "uploadpage.h"
#include "ui_uploadpage.h"

UploadPage::UploadPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadPage)
{
    ui->setupUi(this);
    m_uploadCheckTimer.start(1000);
    m_threadAvariableCheckTimer.start(1000);
    connect(&m_uploadCheckTimer ,&QTimer::timeout,
            this, &UploadPage::uploadCheckTimeoutProcess);
    connect(&m_threadAvariableCheckTimer ,&QTimer::timeout,
            this, &UploadPage::threadCheckTimeoutProcess);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

UploadPage::~UploadPage(){
    delete ui;
}

void UploadPage::uploadCheckTimeoutProcess(){
    //初始化任务
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    for(int i = 0; i < 5 ;++i){
        UploadTask * task =  dataMgr->takeUploadTask();
        if(task == NULL) break;
        QTreeWidgetItem * item = new QTreeWidgetItem();
        QProgressBar * progressBar = new QProgressBar();//TO-DO是否会被自动删除有待考究
        QTimer *taskTimer = new QTimer();

        item->setText(0,task->getFileName());
        item->setText(1,"等待中");
        item->setText(2,"等待中");
        item->setText(4,"等待中");
        item->setData(0,Qt::UserRole,QVariant::fromValue<UploadTask*>(task));
        progressBar->setMinimum(0);
        progressBar->setMaximum(1000);
        ui->treeWidget->addTopLevelItem(item);
        ui->treeWidget->setItemWidget(item,3,progressBar);

        connect(taskTimer,&QTimer::timeout, this, [task,item](){
            qint64 seconds = task->taskStartTime().secsTo(QDateTime::currentDateTime());
            QString timeString = QString("%1:%2:%3").arg(seconds/3600).arg(seconds%3600/60).arg(seconds%3600%60);
            item->setText(4,timeString);
        });

        connect(task, &UploadTask::taskStarted, this, [this,task,taskTimer,item](QDateTime startDateTime, UploadTask::TaskType type){
            if(type == UploadTask::ENCIPHER){
                item->setText(1,"加密中");
                item->setText(2,startDateTime.toString());
            }
            if(type == UploadTask::UPLOAD){
                item->setText(1,"上传中");
                item->setText(4, "0:0:0");
                taskTimer->start(1000);
            }
        });

        connect(task, &UploadTask::uploadProgress, this, [task,progressBar](qint64 progress){
            progressBar->setValue(progress);
        });

        connect(task, &UploadTask::taskFinished, this, [this,task,taskTimer,item](QDateTime startDateTime, UploadTask::TaskType type){
            if(type == UploadTask::ENCIPHER){
                item->setText(1,"加密已完成");
            }
            if(type == UploadTask::UPLOAD){
                item->setText(1,"上传已完成");
                taskTimer->stop();
                task->deleteLater();
                taskTimer->deleteLater();
            }
        });
        this->m_waitQueue.enqueue(task);
    }
}

void UploadPage::threadCheckTimeoutProcess(){
    QThreadPool *threadPool = QThreadPool::globalInstance();
    while(!m_waitQueue.isEmpty()
        && threadPool->activeThreadCount() < threadPool->maxThreadCount())
    {
        UploadTask * task =  m_waitQueue.dequeue();
        task->setAutoDelete(false);
        task->setTaskType(UploadTask::ENCIPHER);
        connect(task,&UploadTask::taskFinished, this, [=](QDateTime startDateTime, UploadTask::TaskType type){
            if(type == UploadTask::ENCIPHER){
                task->setTaskType(UploadTask::UPLOAD);
                task->sendRequest();
            }
        });
        threadPool->start(task);
    }
}

