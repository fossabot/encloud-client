#pragma once
#include "common/globalmarco.h"
#include <QObject>
#include <QRunnable>
#include <QMap>
#include <QThread>
#include <QBuffer>
class DownloadTask : public QObject, public QRunnable{
    Q_OBJECT
public:
    explicit DownloadTask(QObject *parent = nullptr);
    enum TaskType{
        DOWNLOAD,
        DECIPHER
    };
public:
    void run();
    void sendRequest();

    const QString &getItemID() const;
    void setItemID(const QString &newItemID);
    const QString &getFileName() const;
    void setFileName(const QString &newFileName);
    const QString &getFilePath() const;
    void setFilePath(const QString &newFilePath);
    const QByteArray &getFileKey() const;
    void setFileKey(const QByteArray &newFileKey);
    TaskType taskType() const;
    void setTaskType(TaskType newTaskType);

    const QByteArray &getHash() const;
    void setHash(const QByteArray &newHash);
    const QDateTime &taskStartTime() const;
    void setTaskStartTime(const QDateTime &newTaskStartTime);

private:
    QString     itemID;
    QString     fileName;
    QByteArray  fileKey;
    QString     filePath;
    QBuffer     *buff;
    QByteArray  hash;

    QDateTime   m_taskStartTime;
    TaskType    m_taskType;
signals:
    void taskStarted(QDateTime beginDateTime, DownloadTask::TaskType type);
    void downloadProgress(qint64 progress);
    void taskFinished(QDateTime beginDateTime, DownloadTask::TaskType type);
};


