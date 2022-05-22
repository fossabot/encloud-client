#include "filewindow.h"
#include "ui_filewindow.h"

#include <QDebug>

FileWindow::FileWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);

    connect(ui->navigator, &FileWindowNavigator::pathChanged,
            this, &FileWindow::pathChangedProcess);

    connect(ui->fileBrower, &FileWindowTreeWidget::enterFolder,
            this, &FileWindow::enterFolderProcess);
    connect(ui->fileBrower, &FileWindowTreeWidget::downloadFile,
            this, &FileWindow::downloadFileProcess);
    connect(ui->fileBrower, &FileWindowTreeWidget::uploadFile,
            this, &FileWindow::uploadFileProcess);
    connect(ui->fileBrower, &FileWindowTreeWidget::deleteFile,
            this, &FileWindow::deleteFileProcess);
    connect(ui->fileBrower, &FileWindowTreeWidget::renameFile,
            this, &FileWindow::renameFileProcess);
    connect(ui->fileBrower, &FileWindowTreeWidget::makeDirectory,
            this, &FileWindow::makeDirectoryProcess);


    //添加主目录
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    addDirectory(dataMgr->account().getRootDirID(),[this](const QString &dirName){
        stdoutput <<  "添加目录成功,目录名: " <<  dirName;
        ui->fileBrower->setDirectory(&m_directoryMap[dirName]);
        ui->navigator->setPath(dirName);
    });
}

FileWindow::~FileWindow(){
    delete ui;

}

void FileWindow::addDirectory(QString dirID,std::function<void (const QString&)> const callBack){
    //初始化
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    MessageManager *msgMgr = MessageManager::self();
    NetworkManager *netMgr = NetworkManager::self();

    //封装请求报文
    DirectoryRequest request;
    request.setDirID(dirID);
    request.setToken(dataMgr->token());
    QJsonValue requestJson =  msgMgr->getDirectoryRequestJson(&request);
    Reply * reply =  netMgr->sendJson(QUrl(DIRECTORY_SYNC_PATH),requestJson);

    //处理响应报文
    connect(reply, &Reply::readyReadJson, this, [this,reply,callBack](QJsonValue responseJson){
        //初始化
        GlobalDataManager *dataMgr = GlobalDataManager::self();
        MessageManager *msgMgr = MessageManager::self();
        CryptographyManager *crytoMgr = CryptographyManager::self();

        //解析响应
        DirectoryResponse response;
        msgMgr->phraseDirectoryResponseJson(&responseJson, &response);
        stdoutput << "目录json" << responseJson;
        stdoutput << "服务器信息" << response.getDate();
        stdoutput << "获取目录信息" << response.getDirectory().getDirectoryName();
        const Directory &dir = response.getDirectory();

        //解密目录
        Directory newDir = dir;
        QList<DirectoryItem> newDirItems;
        DirectoryItem temp;
        if(dir.getDirectoryName() != "/"){
            QByteArray dirNameBytes_with_encipher = QByteArray::fromBase64(dir.getDirectoryName());
            QByteArray dirNameBytes =
                    crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                                          &dirNameBytes_with_encipher,
                                          &dataMgr->account().getMainKey(),
                                          NULL);
            newDir.setDirectoryName(dirNameBytes);
        }


        for(const DirectoryItem &item : dir.getItems()){
            temp = item;
            temp.setItemName(QByteArray::fromBase64(temp.getItemName()));
            temp.setItemKey(QByteArray::fromBase64(item.getItemKey()));
            temp.setItemName(crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                                                   &temp.getItemName(),
                                                   &dataMgr->account().getMainKey(),
                                                   NULL));
            temp.setItemKey(crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                                                  &temp.getItemKey(),
                                                  &dataMgr->account().getMainKey(),
                                                  NULL));
            newDirItems.append(temp);
        }
        newDir.setItems(newDirItems);

        //添加到集合中
        m_directoryMap.insert(newDir.getDirectoryName(),newDir);
        reply->deleteLater();
        if(callBack != NULL){
            callBack(newDir.getDirectoryName());
        }
    });
}

void FileWindow::reloadDirectory(QString dirName, const std::function<void (const QString &)> callBack){
    QString dirID = m_directoryMap[dirName].getDirectoryID();
    m_directoryMap.remove(dirName);
    addDirectory(dirID,callBack);
}


void FileWindow::pathChangedProcess(QString newPath){
    stdoutput << "pathChanged: " <<  newPath;
    if(m_directoryMap.contains(newPath)){
        reloadDirectory(newPath,[this](QString dirName){
            ui->fileBrower->setDirectory(&m_directoryMap[dirName]);
        });
        return;
    }
    //TO-DO: 实现自定义path的获取
    stdoutput << "自定义path未实现, 将在将来支持";

}

void FileWindow::enterFolderProcess(const Directory *dir, const DirectoryItem *item){
    if(m_directoryMap.contains(item->getItemName())){
        ui->fileBrower->setDirectory(&m_directoryMap[item->getItemName()]);
        ui->navigator->setPath(item->getItemName());
        return ;
    }
    addDirectory(item->getItemID(),[this](const QString dirName){
        stdoutput <<  "添加目录成功,目录名: " <<  dirName;
        stdoutput << "+++++++++++++" << m_directoryMap[dirName].getDirectoryID();
        ui->fileBrower->setDirectory(&m_directoryMap[dirName]);
        ui->navigator->setPath(dirName);
    });
}

void FileWindow::uploadFileProcess(const Directory *dir, QList<QString> filePaths){
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    for(QString filePath :filePaths){
        UploadTask * task = new UploadTask();
        task->setDirectoryID(dir->getDirectoryID());
        task->setFilePath(filePath);
        task->setFileName(filePath.split("/").last().toUtf8());
        dataMgr->addUploadTask(task);
    }
}

void FileWindow::downloadFileProcess(const Directory *dir, QList<const DirectoryItem *> itemList, QString localPath){
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    for(const DirectoryItem * item : itemList){
        if(item->getItemType() == DIR_TYPE){
            //TO-DO: 遍历文件夹并添加到下载队列
        }
        if(item->getItemType() == FILE_TYPE){
            //初始化
            DownloadTask * task = new DownloadTask();
            task->setItemID(item->getItemID());
            task->setFilePath(localPath);
            task->setFileName(item->getItemName());
            task->setHash(item->getItemHash());
            task->setFileKey(item->getItemKey());
            dataMgr->addDownloadTask(task);
        }
    }

}

void FileWindow::deleteFileProcess(const Directory *dir, QList<const DirectoryItem *> itemList){
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    MessageManager *msgMgr = MessageManager::self();
    NetworkManager *netMgr = NetworkManager::self();
    DeleteRequest request;
    for(const DirectoryItem * item : itemList){
        request.setToken(dataMgr->token());
        request.setType(item->getItemType());
        request.setDirectoryID(dir->getDirectoryID());
        request.setItemID(item->getItemID());
        QJsonValue requestJson =  msgMgr->getDeleteRequestJson(&request);
        Reply *reply = netMgr->sendJson(QUrl(DELETE_PATH), requestJson);
        connect(reply,&Reply::readyReadJson,this,[this,msgMgr,dir](QJsonValue responseJson){
            stdoutput  << "服务器返回消息" <<responseJson;
            DeleteResponse response;
            msgMgr->phraseDeleteResponseJson(&responseJson, &response);
            if(response.getStatusCode() == DELETE_SUCCESS){
                //reloadDirectory(dir->getDirectoryName(),[this](QString dirName){
                //    ui->fileBrower->setDirectory(&m_directoryMap[dirName]);
                //});
                //TO-DO已知问题，每次请求然后更新目录会有一定几率导致客户端崩溃，采用手动刷新按钮解决
            }
        });
    }

}

void FileWindow::renameFileProcess(const Directory *dir, const DirectoryItem *item, QString newName){
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    MessageManager *msgMgr = MessageManager::self();
    NetworkManager *netMgr = NetworkManager::self();
    CryptographyManager *crytoMgr = CryptographyManager::self();

    QByteArray newNameBytes = newName.toLocal8Bit();

    QByteArray newName_with_encipher =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                  &newNameBytes,
                                  &dataMgr->account().getMainKey(),
                                  NULL);
    RenameRequest request;
    request.setToken(dataMgr->token());
    request.setType(item->getItemType());
    request.setItemID(item->getItemID());
    request.setDirectoryID(dir->getDirectoryID());
    request.setNewName(newName_with_encipher.toBase64());
    QJsonValue requestJson =  msgMgr->getRenameRequestJson(&request);
    Reply * reply =  netMgr->sendJson(QUrl(RENAME_PATH),requestJson);
    connect(reply,&Reply::readyReadJson,this,[this,msgMgr,dir,item](QJsonValue responseJson){
        stdoutput << responseJson;
        RenameResponse response;
        msgMgr->phraseRenameResponseJson(&responseJson,&response);
        if(response.getStatusCode() == RENAME_SUCCESS){
            reloadDirectory(dir->getDirectoryName(),[this](QString dirName){
                ui->fileBrower->setDirectory(&m_directoryMap[dirName]);
             });
            if(item->getItemType() == DIR_TYPE){
                reloadDirectory(item->getItemName(),NULL);
            }
        }
    });

}

void FileWindow::makeDirectoryProcess(const Directory *dir, QString dirName){
    GlobalDataManager *dataMgr = GlobalDataManager::self();
    MessageManager *msgMgr = MessageManager::self();
    NetworkManager *netMgr = NetworkManager::self();
    CryptographyManager *crytoMgr = CryptographyManager::self();
    QByteArray dirNameBytes;
    QByteArray pDirNameBytes =  dir->getDirectoryName();

    stdoutput << "+++++" << dirName;
    //处理文件名
    if(dir->getDirectoryName() == "/"){
        dirNameBytes = QString("/").append(dirName).toUtf8();
    }else{
        dirNameBytes = pDirNameBytes.append("/").append(dirName.toUtf8());
    }
    stdoutput << dirNameBytes.data();
    QByteArray dirNameBytes_with_encipher =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                  &dirNameBytes,
                                  &dataMgr->account().getMainKey(),
                                  NULL);
    MkdirRequest request;
    request.setToken(dataMgr->token());
    request.setDirectoryID(dir->getDirectoryID());
    request.setDirectoryName(dirNameBytes_with_encipher.toBase64());
    QJsonValue requestJson = msgMgr->getMkdirRequestJson(&request);

    Reply *reply = netMgr->sendJson(QUrl(MKDIR_PATH),requestJson);
    connect(reply,&Reply::readyReadJson, [this, msgMgr,dir](QJsonValue responseJson){
        stdoutput  << "服务器消息:" << responseJson;
        MkdirResponse response;
        msgMgr->phraseMkdirResponseJson(&responseJson,&response);
        if(response.getStatusCode() == MKDIR_SUCCESS){
            reloadDirectory(dir->getDirectoryName(),[this](QString dirName){
                ui->fileBrower->setDirectory(&m_directoryMap[dirName]);
            });
        }
    });
}

