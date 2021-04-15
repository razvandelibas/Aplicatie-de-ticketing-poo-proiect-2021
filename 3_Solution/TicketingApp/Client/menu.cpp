#include "menu.h"

menu::menu(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::menu();
	ui->setupUi(this);
}


menu::~menu()
{
	delete ui;
}
