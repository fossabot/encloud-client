#pragma once

#include "common/globaldatamanager.h"
#include <QWidget>
#include <QTimer>
#include <QThreadPool>
#include <QProgressBar>
#include <QQueue>

namespace Ui {
class DownloadPage;
}

class DownloadPage : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadPage(QWidget *parent = nullptr);
    ~DownloadPage();

private:
    Ui::DownloadPage *ui;
    QTimer                  m_downloadCheckTimer;
    QTimer                  m_threadAvariableCheckTimer;
    QQueue<DownloadTask*>   m_waitQueue;
    void downloadCheckTimeoutProcess();
    void threadCheckTimeoutProcess();
};

