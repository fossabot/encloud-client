#include "uploadFileRequest.h"

UploadFileRequest::UploadFileRequest()
{

}

const QString &UploadFileRequest::getDirectoryID() const
{
    return directoryID;
}

void UploadFileRequest::setDirectoryID(const QString &newDirectoryID)
{
    directoryID = newDirectoryID;
}

const QByteArray &UploadFileRequest::getFileName() const
{
    return fileName;
}

void UploadFileRequest::setFileName(const QByteArray &newFileName)
{
    fileName = newFileName;
}

const QByteArray &UploadFileRequest::getFileKey() const
{
    return fileKey;
}

void UploadFileRequest::setFileKey(const QByteArray &newFileKey)
{
    fileKey = newFileKey;
}

const QString &UploadFileRequest::getHash() const
{
    return hash;
}

void UploadFileRequest::setHash(const QString &newHash)
{
    hash = newHash;
}

qint64 UploadFileRequest::getSize() const
{
    return size;
}

void UploadFileRequest::setSize(qint64 newSize)
{
    size = newSize;
}

QIODevice *UploadFileRequest::getIODevice() const
{
    return IODevice;
}

void UploadFileRequest::setIODevice(QIODevice *newIODevice)
{
    IODevice = newIODevice;
}

