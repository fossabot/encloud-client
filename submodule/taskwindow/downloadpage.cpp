#include "downloadpage.h"
#include "ui_downloadpage.h"

DownloadPage::DownloadPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadPage)
{
    ui->setupUi(this);
    m_downloadCheckTimer.start(1000);
    m_threadAvariableCheckTimer.start(1000);
    connect(&m_downloadCheckTimer ,&QTimer::timeout,
            this, &DownloadPage::downloadCheckTimeoutProcess);
    connect(&m_threadAvariableCheckTimer ,&QTimer::timeout,
            this, &DownloadPage::threadCheckTimeoutProcess);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

DownloadPage::~DownloadPage()
{
    delete ui;
}

void DownloadPage::downloadCheckTimeoutProcess(){
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    for(int i = 0; i < 5 ;++i){
        DownloadTask * task =  dataMgr->takeDownloadTask();
        if(task == NULL) break;
        QTreeWidgetItem * item = new QTreeWidgetItem();
        QProgressBar * progressBar = new QProgressBar();
        QTimer *taskTimer = new QTimer();
        item->setText(0,task->getFileName());
        item->setText(1,"等待中");
        item->setText(2,"等待中");
        item->setText(4,"等待中");
        item->setText(5,task->getFilePath()+task->getFileName());
        item->setData(0,Qt::UserRole,QVariant::fromValue<DownloadTask*>(task));
        progressBar->setMinimum(0);
        progressBar->setMaximum(1000);
        ui->treeWidget->addTopLevelItem(item);
        ui->treeWidget->setItemWidget(item,3,progressBar);

        connect(taskTimer,&QTimer::timeout, this, [task,item](){
            qint64 seconds = task->taskStartTime().secsTo(QDateTime::currentDateTime());
            QString timeString = QString("%1:%2:%3").arg(seconds/3600).arg(seconds%3600/60).arg(seconds%3600%60);
            item->setText(4,timeString);
        });

        connect(task, &DownloadTask::taskStarted, this, [this,task,taskTimer,item](QDateTime startDateTime, DownloadTask::TaskType type){
            if(type == DownloadTask::DOWNLOAD){
                item->setText(1,"下载中");
                item->setText(2,startDateTime.toString());
                item->setText(4, "0:0:0");
                taskTimer->start(1000);
            }
            if(type == DownloadTask::DECIPHER){
                item->setText(1,"解密中");
            }
        });

        connect(task, &DownloadTask::downloadProgress, this, [task,progressBar](qint64 progress){
            stdoutput  << progress;
            progressBar->setValue(progress);
        });

        connect(task, &DownloadTask::taskFinished, this, [this,task,taskTimer,item](QDateTime dateTime, DownloadTask::TaskType type){
            if(type == DownloadTask::DOWNLOAD){
                item->setText(1,"下载已完成");
            }
            if(type == DownloadTask::DECIPHER){
                item->setText(1,"解密已完成");
                taskTimer->stop();
                taskTimer->deleteLater();
                task->deleteLater();
            }
        });
        this->m_waitQueue.enqueue(task);
    }
}

void DownloadPage::threadCheckTimeoutProcess(){
    QThreadPool *threadPool = QThreadPool::globalInstance();
    while(!m_waitQueue.isEmpty()
        && threadPool->activeThreadCount() < threadPool->maxThreadCount())
    {
        stdoutput << "hello world" ;
        DownloadTask * task =  m_waitQueue.dequeue();
        task->setAutoDelete(false);
        task->setTaskType(DownloadTask::DOWNLOAD);
        connect(task,&DownloadTask::taskFinished, this, [=](QDateTime endDateTime, DownloadTask::TaskType type){
            if(type == DownloadTask::DOWNLOAD){
//                stdoutput << "+++++++++hello world";
                task->setTaskType(DownloadTask::DECIPHER);
                threadPool->start(task);
            }
        });
        task->sendRequest();
    }
}
