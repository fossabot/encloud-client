#pragma once

#include "common/globalmarco.h"
#include <QDateTime>
class Group{
public:
    explicit Group();
    qint64 getGroupID() const;
    void setGroupID(qint64 newGroupID);
    const QString &getGroupName() const;
    void setGroupName(const QString &newGroupName);
    const QDateTime &getCreateDate() const;
    void setCreateDate(const QDateTime &newCreateDate);

private:
    qint64      groupID;
    QString     groupName;
    QDateTime       createDate;
signals:

};

