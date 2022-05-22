#pragma once

#include "common/globaldatamanager.h"
#include <QWidget>
#include <QTimer>
#include <QThreadPool>
#include <QProgressBar>
#include <QQueue>
namespace Ui {
class UploadPage;
}

class UploadPage : public QWidget
{
    Q_OBJECT

public:
    explicit UploadPage(QWidget *parent = nullptr);
    ~UploadPage();

private:
    Ui::UploadPage          *ui;
    QTimer                  m_uploadCheckTimer;
    QTimer                  m_threadAvariableCheckTimer;
    QQueue<UploadTask*>     m_waitQueue;
    void uploadCheckTimeoutProcess();
    void threadCheckTimeoutProcess();
};


