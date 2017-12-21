#include "dialognew.h"
#include "ui_dialognew.h"
#include <QMessageBox>

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);

    // accept only double in fields, with dot
    QDoubleValidator* validator = new QDoubleValidator(this);
    validator->setLocale(QLocale("England"));
    ui->pMinX->setValidator(validator);
    ui->pMinY->setValidator(validator);
    ui->pMaxX->setValidator(validator);
    ui->pMaxY->setValidator(validator);
    ui->hMinZ->setValidator(validator);
    ui->hMaxZ->setValidator(validator);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()), Qt::UniqueConnection);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()), Qt::UniqueConnection);
}

DialogNew::~DialogNew()
{
    delete ui;
}

void DialogNew::accept() {
    //QMessageBox::warning(this, "Error", "Each parameter requires a float value.");
    this->hide();
}

void DialogNew::reject() {
    this->hide();
}

