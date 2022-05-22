#ifndef CONTROLPAGE_H
#define CONTROLPAGE_H

#include <QWidget>

namespace Ui {
class UploadControlPage;
}

class ControlPage : public QWidget{
    Q_OBJECT
public:
    explicit ControlPage(QWidget *parent = nullptr);
    ~ControlPage();

private:
    Ui::UploadControlPage *ui;

public slots:
    void addTask();
    void removeTask();
};

#endif // CONTROLPAGE_H
