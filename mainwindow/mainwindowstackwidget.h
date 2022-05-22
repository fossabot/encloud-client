#pragma once

#include <QWidget>

namespace Ui {
class MainWindowStackWidget;
}

class MainWindowStackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowStackWidget(QWidget *parent = nullptr);
    ~MainWindowStackWidget();

public slots:
    void setCurrentPage(int indx);

private:
    Ui::MainWindowStackWidget *ui;
};

