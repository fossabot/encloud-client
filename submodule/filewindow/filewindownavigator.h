#pragma once

#include "common/globalmarco.h"
#include <QWidget>
#include <QStack>

namespace Ui {
class FileWindowNavigator;
}

class FileWindowNavigator : public QWidget
{
    Q_OBJECT

public:
    explicit FileWindowNavigator(QWidget *parent = nullptr);
    ~FileWindowNavigator();

private:
    Ui::FileWindowNavigator *ui;
    QStack<QString>  m_backStack;
    QStack<QString>  m_forwardStack;
public slots:
    void setPath(QString newPath);
signals:
    void pathChanged(QString newPath);
};

