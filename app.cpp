#include "app.h"
#include <QFileDialog>
#include <QMessageBox>

App::App(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::App),
      currentFile("")
{
    ui->setupUi(this);

    // buttons connections
    connect(ui->buttonDisplayMode, SIGNAL(clicked()), this, SLOT(on_buttonDisplayMode_clicked()), Qt::UniqueConnection);

    // menu connections
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(on_actionNew_triggered()), Qt::UniqueConnection);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(on_actionOpen_triggered()), Qt::UniqueConnection);
}

App::~App() {
    delete ui;
}

void App::on_actionNew_triggered() {
    // file selection
    QString fileName = QFileDialog::getOpenFileName(this, "Choose the heightfield image");
    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"Error","No file opened.");
        currentFile = "";
        return;
    }

    // load file
    ui->glWidget->createTerrain(currentFile);

    // display image terrain
    QPixmap pixmapObject;
    if(pixmapObject.load(fileName)) {
        ui->label0->setPixmap(pixmapObject);
        ui->label0->setScaledContents(true);
        ui->label0->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }else {
        ui->label0->setText("Terrain image not found");
    }

    // close file
    file.close();
}

void App::on_actionOpen_triggered() {
    // file selection
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;

    // check extension/suffix
    QFileInfo infos(file);
    //QMessageBox::about(this, "Debug", infos.suffix());
    if (!file.open(QIODevice::ReadOnly | QFile::Text) || infos.suffix() != "obj") {
        QMessageBox::warning(this,"Error","No OBJ file opened.");
        currentFile = "";
        return;
    }

    // load obj file
    ui->glWidget->loadFile(currentFile);

    // get image terrain
    QString pathImgTerrain = infos.path() + "/" + infos.baseName() + ".jpg";
    QPixmap pixmapObject;
    if(pixmapObject.load(pathImgTerrain)) {
        ui->label0->setPixmap(pixmapObject);
        ui->label0->setScaledContents(true);
        ui->label0->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }else {
        ui->label0->setText("Terrain image not found");
    }


    // close file
    file.close();
}

void App::on_buttonDisplayMode_clicked()
{
    ui->glWidget->changeDisplayMode();
}
