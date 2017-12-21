#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class DialogNew;
}

class DialogNew : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNew(QWidget *parent = 0);
    ~DialogNew();

public slots:

private slots:
    void accept();
    void reject();

private:
    Ui::DialogNew *ui;
};

#endif // DIALOGNEW_H
