#pragma once

#include "common/globalmarco.h"
#include "common/entity/directoryitem.h"
class Directory
{
public:
    Directory();

    const QString &getDirectoryID() const;
    void setDirectoryID(const QString &newDirectoryID);
    qint64 getItemCount() const;
    void setItemCount(qint64 newItemCount);
    const QDateTime &getCreateDate() const;
    void setCreateDate(const QDateTime &newCreateDate);
    const QDateTime &getAccessDate() const;
    void setAccessDate(const QDateTime &newAccessDate);
    const QDateTime &getModifyDate() const;
    void setModifyDate(const QDateTime &newModifyDate);
    const QList<DirectoryItem> &getItems() const;
    void setItems(const QList<DirectoryItem> &newItems);
    void setDirectorySize(qint64 newDirectorySize);
    qint64 getDirectorySize() const;
    const QByteArray &getDirectoryName() const;
    void setDirectoryName(const QByteArray &newDirectoryName);

private:
    QString                 directoryID;
    QByteArray              directoryName;
    qint64                  directorySize;
    qint64                  itemCount;
    QDateTime               createDate;
    QDateTime               accessDate;
    QDateTime               modifyDate;
    QList<DirectoryItem>    items;
};

