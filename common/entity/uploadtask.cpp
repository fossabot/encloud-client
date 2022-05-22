#include "uploadtask.h"
#include "common/globalmarco.h"
#include "common/cryptographymanager.h"
#include "common/messagemanager.h"
#include "common/networkmanager.h"
#include "common/globaldatamanager.h"
#include "common/message/uploadFileRequest.h"
#include "common/message/uploadfileresponse.h"
#include <QBuffer>
#include <QApplication>
UploadTask::UploadTask(){

}

void UploadTask::run(){
    //任务初始化
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    CryptographyManager *crytoMgr = CryptographyManager::self();

    emit this->taskStarted(QDateTime::currentDateTime(), m_taskType);
    this->m_taskStartTime = QDateTime::currentDateTime();
    //初始化
    QFileInfo fileInfo =  QFileInfo(filePath);
    QFile file =  QFile(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray fileBytes =  file.readAll();
    file.close();
    //文件初始化处理
    this->fileName =  fileInfo.fileName().toUtf8();
    this->fileName =  crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                  &this->fileName,
                                  &dataMgr->account().getMainKey(),NULL).toBase64();
    this->fileKey = crytoMgr->symKeyGenerate(CryptographyManager::AES_128_ECB);
    this->hash = crytoMgr->calcHashCode(CryptographyManager::MD5,&fileBytes).toBase64();
    this->size = fileInfo.size();

    QBuffer *buffIODevice = new QBuffer();
    buffIODevice->moveToThread(QApplication::instance()->thread());//转回主线程
    buffIODevice->setParent(this);
    QByteArray fileBytes_with_encipher =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                          &fileBytes,
                          &this->fileKey,NULL);
    buffIODevice->setData(fileBytes_with_encipher);
    this->IODevice = buffIODevice;

    //加密文件秘钥
    this->fileKey =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                        &this->fileKey,
                        &dataMgr->account().getMainKey(),
                        NULL).toBase64();
    emit this->taskFinished(QDateTime::currentDateTime(), m_taskType);
}

void UploadTask::sendRequest(){
    emit this->taskStarted(QDateTime::currentDateTime(), m_taskType);
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    MessageManager *msgMgr = MessageManager::self();
    NetworkManager *netMgr = NetworkManager::self();
    CryptographyManager *crytoMgr = CryptographyManager::self();

    //封装报文
    UploadFileRequest request;
    request.setDirectoryID(this->directoryID);
    request.setFileName(this->fileName);
    request.setFileKey(this->fileKey);
    request.setSize(this->size);
    request.setHash(this->hash);
    request.setIODevice(this->IODevice);
    QHttpMultiPart *requestMultiPart = msgMgr->getUploadMultiPart(&request);
    requestMultiPart->setParent(this);
    this->IODevice->open(QIODevice::ReadOnly);
    //发送数据
    Reply *reply = netMgr->sendMultiPart(QUrl(UPLOAD_FILE_PAHT),requestMultiPart);
    reply->setParent(this);
    connect(reply, &Reply::uploadProgress, this, [this](qint64 bytesSend, qint64 bytesTotals){
        emit this->uploadProgress((qint64)((double)bytesSend/bytesTotals*1000));
    });

    connect(reply,&Reply::readyReadJson, this, [this, msgMgr,reply](QJsonValue responseJson){
        stdoutput << "上传操作服务器返回json: " << responseJson;
//            UploadFileResponse response;
//            msgMgr->phraseUploadResponseJson(&responseJson, &response);
        emit this->taskFinished(QDateTime::currentDateTime(), m_taskType);
    });
}


QIODevice *UploadTask::getIODevice() const
{
    return IODevice;
}

void UploadTask::setIODevice(QIODevice *newIODevice)
{
    IODevice = newIODevice;
}

UploadTask::TaskType UploadTask::taskType() const
{
    return m_taskType;
}

void UploadTask::setTaskType(TaskType newTaskType)
{
    m_taskType = newTaskType;
}

const QDateTime &UploadTask::taskStartTime() const
{
    return m_taskStartTime;
}

void UploadTask::setTaskStartTime(const QDateTime &newTaskStartTime)
{
    m_taskStartTime = newTaskStartTime;
}


const QString &UploadTask::getDirectoryID() const
{
    return directoryID;
}

void UploadTask::setDirectoryID(const QString &newDirectoryID)
{
    directoryID = newDirectoryID;
}

const QString &UploadTask::getFilePath() const
{
    return filePath;
}

void UploadTask::setFilePath(const QString &newFilePath)
{
    filePath = newFilePath;
}

const QByteArray &UploadTask::getFileName() const
{
    return fileName;
}

void UploadTask::setFileName(const QByteArray &newFileName)
{
    fileName = newFileName;
}

const QByteArray &UploadTask::getFileKey() const
{
    return fileKey;
}

void UploadTask::setFileKey(const QByteArray &newFileKey)
{
    fileKey = newFileKey;
}

const QByteArray &UploadTask::getHash() const
{
    return hash;
}

void UploadTask::setHash(const QByteArray &newHash)
{
    hash = newHash;
}

qint64 UploadTask::getSize() const
{
    return size;
}

void UploadTask::setSize(qint64 newSize)
{
    size = newSize;
}

