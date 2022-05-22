#pragma once

#include "common/globalmarco.h"
#include "common/cryptographymanager.h"
#include "common/messagemanager.h"
#include "common/networkmanager.h"
#include "common/globaldatamanager.h"
#include "common/storagemanager.h"
#include "common/entity/uploadtask.h"
#include "common/entity/downloadtask.h"
#include <QWidget>
#include <functional>

namespace Ui {
class FileWindow;
}

class FileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = nullptr);
    ~FileWindow();

private:
    void addDirectory(QString dirID,std::function<void (const QString&)> const callBack);
    void reloadDirectory(QString dirName, std::function<void (const QString&)> const callBack);
    void pathChangedProcess(QString newPath);
    void enterFolderProcess(const Directory *dir, const DirectoryItem* item);
    void uploadFileProcess(const Directory *dir,  QList<QString> filePaths);
    void downloadFileProcess(const Directory *dir, QList<const DirectoryItem*> itemList, QString localPath);
    void deleteFileProcess(const Directory *dir,  QList<const DirectoryItem*> itemList);
    void renameFileProcess(const Directory *dir,  const DirectoryItem *item, QString newName);
    void makeDirectoryProcess(const Directory *dir, QString dirName);
private:
    QMap<QString, Directory> m_directoryMap;

private:
    Ui::FileWindow *ui;



};

