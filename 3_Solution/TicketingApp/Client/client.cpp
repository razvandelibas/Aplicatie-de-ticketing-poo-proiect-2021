#include "client.h"
//#include "stdafx.h"
#include <QMessageBox>

Client::Client(QWidget *parent) : QMainWindow(parent), ui(new Ui::ClientClass)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username == "test" && password == "test")
    {
        QMessageBox::information(this, "Login", "V-ati autentificat cu succes!");
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username sau parola gresite.");
    }
}
