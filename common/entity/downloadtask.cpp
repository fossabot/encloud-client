#include "downloadtask.h"
#include "common/networkmanager.h"
#include "common/cryptographymanager.h"
#include "common/messagemanager.h"
#include <QMap>
DownloadTask::DownloadTask(QObject *parent)
    : QObject{parent}
{

}

void DownloadTask::run(){
    emit  this->taskStarted(QDateTime::currentDateTime(), m_taskType);
    CryptographyManager *crytoMgr = CryptographyManager::self();
    QByteArray fileBytes_with_decipher =
            crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                          &this->buff->data(),
                          &this->fileKey,
                          NULL);
    QFile fileToSave(this->filePath+"/"+this->fileName);
    fileToSave.open(QIODevice::WriteOnly);
    fileToSave.write(fileBytes_with_decipher);
    emit this->taskFinished(QDateTime::currentDateTime(), m_taskType);
}

void DownloadTask::sendRequest(){
    emit  this->taskStarted(QDateTime::currentDateTime(), m_taskType);
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    MessageManager *msgMgr = MessageManager::self();
    NetworkManager *netMgr = NetworkManager::self();

    DownloadRequest request;
    request.setToken(dataMgr->token());
    request.setItemID(this->itemID);
    QJsonValue requestJson =  msgMgr->getDownloadRequestJson(&request);
    Reply *reply = netMgr->sendJson(QUrl(DOWNLOAD_FILE_PATH),requestJson);
    reply->setParent(this);
    connect(reply, &Reply::downloadProgress, this, [this](qint64 bytesdown, qint64 bytesTotals){
        stdoutput << "+++++++++" << bytesdown << "+++" << bytesTotals;
        emit this->downloadProgress((qint64)((double)bytesdown/bytesTotals*1000));
    });

    connect(reply,&Reply::readyReadBinary,this,[this](QIODevice *device){
        stdoutput << "有数据了";
        QBuffer *buff = new QBuffer();
        buff->setParent(this);
        buff->setData(device->readAll());
        this->buff = buff;
        emit this->taskFinished(QDateTime::currentDateTime(), m_taskType);
    });
}

const QByteArray &DownloadTask::getFileKey() const
{
    return fileKey;
}

void DownloadTask::setFileKey(const QByteArray &newFileKey)
{
    fileKey = newFileKey;
}

DownloadTask::TaskType DownloadTask::taskType() const
{
    return m_taskType;
}

void DownloadTask::setTaskType(DownloadTask::TaskType newTaskType)
{
    m_taskType = newTaskType;
}


const QByteArray &DownloadTask::getHash() const
{
    return hash;
}

void DownloadTask::setHash(const QByteArray &newHash)
{
    hash = newHash;
}

const QDateTime &DownloadTask::taskStartTime() const
{
    return m_taskStartTime;
}

void DownloadTask::setTaskStartTime(const QDateTime &newTaskStartTime)
{
    m_taskStartTime = newTaskStartTime;
}


const QString &DownloadTask::getItemID() const
{
    return itemID;
}

void DownloadTask::setItemID(const QString &newItemID)
{
    itemID = newItemID;
}

const QString &DownloadTask::getFileName() const
{
    return fileName;
}

void DownloadTask::setFileName(const QString &newFileName)
{
    fileName = newFileName;
}

const QString &DownloadTask::getFilePath() const
{
    return filePath;
}

void DownloadTask::setFilePath(const QString &newFilePath)
{
    filePath = newFilePath;
}
