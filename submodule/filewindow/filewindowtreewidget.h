#pragma once

#include "common/globalmarco.h"
#include "common/entity/directory.h"
#include "common/entity/directoryitem.h"
#include <QWidget>
#include <QMap>
#include <QTreeWidgetItem>

namespace Ui {
class FileWindowTreeWidget;
}

class FileWindowTreeWidget : public QWidget{
    Q_OBJECT
public:
    explicit FileWindowTreeWidget(QWidget *parent = nullptr);
    ~FileWindowTreeWidget();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
private:
    Ui::FileWindowTreeWidget *ui;
    QMap<QString, QAction*> m_actionMap;
    const Directory   *m_currentDir;
    void  contextMenuActionProcess(int indx);
    void  doubleClickedActionProcess(QTreeWidgetItem *item, int column);
public slots:
    void setDirectory(const Directory *dir);
    void refresh();
    void clear();
signals:
    void enterFolder(const Directory *dir, const DirectoryItem* item);
    void downloadFile(const Directory *dir, QList<const DirectoryItem*> itemList, QString localPath);
    void deleteFile(const Directory *dir,  QList<const DirectoryItem*> itemList);
    void uploadFile(const Directory *dir,  QList<QString> filePaths);
    void renameFile(const Directory *dir,  const DirectoryItem *item, QString newName);
    void makeDirectory(const Directory *dir, QString dirName);
};

