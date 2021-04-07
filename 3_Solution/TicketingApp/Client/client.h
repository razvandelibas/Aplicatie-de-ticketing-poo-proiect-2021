#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_client.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);

private:
    Ui::ClientClass ui;
};
