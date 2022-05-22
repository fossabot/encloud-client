#pragma once

#include <QWidget>

namespace Ui {
class CompletedPage;
}

class CompletedPage : public QWidget
{
    Q_OBJECT

public:
    explicit CompletedPage(QWidget *parent = nullptr);
    ~CompletedPage();

private:
    Ui::CompletedPage *ui;

public slots:
//    addRecord()
};

