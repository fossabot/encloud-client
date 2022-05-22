#pragma once

#include "common/globalmarco.h"
#include "common/globaldatamanager.h"
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    bool m_isMaxSize;
    Ui::MainWindow *ui;
signals:
    void accountLogouted();

};

