#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_app.h"

class App : public QMainWindow
{
	Q_OBJECT

public:
	App(QWidget *parent = Q_NULLPTR);

private:
	Ui::AppClass ui;
};
