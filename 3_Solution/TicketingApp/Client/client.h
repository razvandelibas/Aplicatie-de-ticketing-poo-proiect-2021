#pragma once

#include <QtWidgets/QWidget>
#include "ui_client.h"
#include"menu.h"

namespace Ui
{
    class Client;
}
class Client : public QMainWindow
{
    Q_OBJECT

public:
   explicit Client(QWidget *parent = Q_NULLPTR);
    ~Client();

private slots:
    void on_pushButton_login_clicked();
  
private:
    Ui::ClientClass *ui;
    menu* meniu;
};
