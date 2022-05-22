#pragma once

#include "common/globalmarco.h"
#include "common/message/regrequest.h"
#include "common/message/regresponse.h"
#include "common/message/loginrequest.h"
#include "common/message/loginresponse.h"
#include "common/message/uploadFileRequest.h"
#include "common/message/uploadfileresponse.h"
#include "common/message/downloadrequest.h"
#include "common/message/downloadresponse.h"
#include "common/message/requestbase.h"
#include "common/message/accountsyncresponse.h"
#include "common/message/usersyncresponse.h"
#include "common/message/messagesyncresponse.h"
#include "common/message/directoryrequest.h"
#include "common/message/directoryresponse.h"
#include "common/message/renamerequest.h"
#include "common/message/renameresponse.h"
#include "common/message/deleterequest.h"
#include "common/message/deleteresponse.h"
#include "common/message/mkdirrequest.h"
#include "common/message/mkdirresponse.h"
#include "common/entity/account.h"
#include "common/entity/file.h"
#include "common/entity/group.h"
#include "common/entity/message.h"
#include "common/entity/share.h"
#include "common/entity/user.h"
#include "common/entity/directory.h"
#include "common/entity/directoryitem.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHttpMultiPart>


class MessageManager : public QObject{
    Q_OBJECT

//非静态成员
private:
    explicit MessageManager(QObject *parent = nullptr);

public:
    QJsonValue getRegRequestJson(RegRequest *info);
    void       phraseRegResponseJson(QJsonValue *responJson, RegResponse *response);

    QJsonValue getLoginRequestJson(LoginRequest *info);
    void       phraseLoginResponseJson(QJsonValue *responJson,LoginResponse *response);

    QJsonValue getRequestBaseJson(RequestBase *info);
    void       phraseUserSyncResponseJson(QJsonValue *responseJson, UserSyncResponse* response);
    void       phraseAccountSyncResponseJson(QJsonValue *responseJson, AccountSyncResponse* response);
    void       phraseMessageSyncResponseJson(QJsonValue *responseJson, MessageSyncResponse* response);

    QJsonValue getDirectoryRequestJson(DirectoryRequest *info);
    void       phraseDirectoryResponseJson(QJsonValue *responseJson, DirectoryResponse *response);

    QJsonValue getRenameRequestJson(RenameRequest *info);
    void       phraseRenameResponseJson(QJsonValue *responseJson, RenameResponse *response);


    QHttpMultiPart* getUploadMultiPart(UploadFileRequest *info);
    void       phraseUploadResponseJson(QJsonValue *responseJson, UploadFileResponse *response);

    QJsonValue getDownloadRequestJson(DownloadRequest *info);
    void       phraseDownloadResponse(QJsonValue *responseJson, DownloadResponse *response);

    QJsonValue getMkdirRequestJson(MkdirRequest *info);
    void       phraseMkdirResponseJson(QJsonValue *responseJson, MkdirResponse *response);

    QJsonValue getDeleteRequestJson(DeleteRequest *info);
    void       phraseDeleteResponseJson(QJsonValue *responseJson, DeleteResponse *response);

private:
    void fillRequestBaseFields(QJsonObject *jsonObject, RequestBase *info);
    void phraseResponseBaseFields(QVariantMap *map, ResponseBase *response);
    void phraseAccountFields(QVariantMap *map, Account * account);
    void phraseUserFields(QVariantMap *map, User *user);
    void phraseFileFields(QVariantMap *map, File *file);
    void phraseShareFields(QVariantMap *map, Share *share);
    void phraseMessageFields(QVariantMap *map, Message *message);
    void phraseDirectoryFilds(QVariantMap *map, Directory *directory);
    void phraseDirectoryItemFilds(QVariantMap *map, DirectoryItem *item);

//静态成员
public:
    static MessageManager *self();
private:
    static MessageManager *s_msgMgr;

 };

