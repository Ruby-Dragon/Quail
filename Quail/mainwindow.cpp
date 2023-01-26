#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "commander.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Commander* commander = new Commander();

    QObject::connect(ui->UpButton, SIGNAL(clicked()), commander, SLOT(TailscaleUp));
}

MainWindow::~MainWindow()
{
    delete ui;
}

