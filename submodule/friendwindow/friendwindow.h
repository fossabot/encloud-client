#pragma once

#include <QWidget>

namespace Ui {
class FriendWindow;
}

class FriendWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FriendWindow(QWidget *parent = nullptr);
    ~FriendWindow();

private:
    Ui::FriendWindow *ui;
};

