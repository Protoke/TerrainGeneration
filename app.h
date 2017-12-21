#ifndef APP_H
#define APP_H

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_app.h"
#include <QString>
#include <QTextStream>
#include "dialognew.h"

namespace Ui {
class App;
}

class App : public QMainWindow
{
	Q_OBJECT

public:
    //App(QWidget *parent = Q_NULLPTR);
    explicit App(QWidget *parent = 0);
    ~App();

public slots:

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_buttonDisplayMode_clicked();

private:
    Ui::App *ui;
    QString currentFile;
    DialogNew *dialogNew;
};

#endif // APP_H
