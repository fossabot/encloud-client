#pragma once

//server status
#define MISSING_SESSION 1
#define CHECK_CODE_ERROR 2
#define REGISTRATION_ERROR 3
#define REGISTRATION_SUCCESS 4
#define LOGIN_SUCCESS 5
#define LOGIN_FAILED 6
#define TOKEN_VERIFY_ERROR 7
#define MESSAGE_SYNC_SUCCESS 8
#define USER_SYNC_SUCCESS 9
#define ACCOUNT_SYNC_SUCCESS 10
#define DIRECTORY_SYNC_SUCCESS 11
#define RENAME_SUCCESS 12
#define UPLOAD_FILE_SUCCESS 13
#define RENAME_FALSE 14
#define MKDIR_SUCCESS 15
#define MKDIR_FALSE 16
#define DELETE_SUCCESS 17
#define DELETE_FALSE 18


//services path
#define LOGIN_PATH "http://server.rubitcat.cn:6666/encloud/user/login"
#define REGISTRATION_PATH "http://server.rubitcat.cn:6666/encloud/user/registration"
#define CHECK_CODE_PATH  "http://server.rubitcat.cn:6666/encloud/user/checkCode"
#define USER_SYNC_PATH "http://server.rubitcat.cn:6666/encloud/user/userSync"
#define ACCOUNT_SYNC_PATH "http://server.rubitcat.cn:6666/encloud/user/accountSync"
#define MESSAGE_SYNC_PATH  "http://server.rubitcat.cn:6666/encloud/user/messageSync"
#define DIRECTORY_SYNC_PATH "http://server.rubitcat.cn:6666/encloud/file/directory"
#define UPLOAD_FILE_PAHT  "http://server.rubitcat.cn:6666/encloud/file/uploadFile"
#define DOWNLOAD_FILE_PATH "http://server.rubitcat.cn:6666/encloud/file/downloadFile"
#define RENAME_PATH "http://server.rubitcat.cn:6666/encloud/file/rename"
#define MKDIR_PATH "http://server.rubitcat.cn:6666/encloud/file/mkdir"
#define DELETE_PATH "http://server.rubitcat.cn:6666/encloud/file/delete"

//file type
#define DIR_TYPE 1
#define FILE_TYPE 2

//commone include
#include <QObject>
#include <QDateTime>
#include <QDebug>


//debug control command
#define stdoutput qDebug() << "[" << __FILE__ << ":"  << __LINE__ << "] "

//typedefine
typedef QPair<QByteArray, QByteArray> KeyPair;
typedef QString StatusCode;
typedef QString   Token;

