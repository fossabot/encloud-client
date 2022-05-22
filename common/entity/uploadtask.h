#pragma once
#include <QThread>
#include <QRunnable>
#include <QMap>
#include <QDateTime>
class UploadTask : public QObject, public QRunnable{
    Q_OBJECT
public:
    explicit UploadTask();
    enum TaskType{
        ENCIPHER,
        UPLOAD
    };

public:
    void run();
    void sendRequest();
    const QString &getDirectoryID() const;
    void setDirectoryID(const QString &newDirectoryID);
    const QString &getFilePath() const;
    void setFilePath(const QString &newFilePath);
    const QByteArray &getFileName() const;
    void setFileName(const QByteArray &newFileName);
    const QByteArray &getFileKey() const;
    void setFileKey(const QByteArray &newFileKey);
    const QByteArray &getHash() const;
    void setHash(const QByteArray &newHash);
    qint64 getSize() const;
    void setSize(qint64 newSize);
    QIODevice *getIODevice() const;
    void setIODevice(QIODevice *newIODevice);
    TaskType taskType() const;
    void setTaskType(TaskType newTaskType);
    const QDateTime &taskStartTime() const;
    void setTaskStartTime(const QDateTime &newTaskStartTime);

private:
    QString     directoryID;
    QString     filePath;
    QByteArray  fileName;
    QByteArray  fileKey;
    QByteArray  hash;
    qint64      size;
    QIODevice   *IODevice;

    QDateTime   m_taskStartTime;
    TaskType    m_taskType;
signals:
    void taskStarted(QDateTime beginDateTime, UploadTask::TaskType type);
    void uploadProgress(qint64 progress);
    void taskFinished(QDateTime beginDateTime, UploadTask::TaskType type);
};

