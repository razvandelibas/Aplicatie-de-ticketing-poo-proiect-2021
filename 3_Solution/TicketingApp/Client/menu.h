#pragma once

#include <QWidget>
#include "ui_menu.h"


class menu : public QWidget, public Ui::menu
{
	Q_OBJECT

public:
	menu(QWidget *parent = Q_NULLPTR);
	~menu();

private:
	Ui::menu *ui;
};
