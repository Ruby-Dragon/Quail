#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "commander.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Commander* commander = new Commander();

    QObject::connect(ui->UpButton, SIGNAL(clicked()), commander, SLOT(TailscaleUp()));
    QObject::connect(ui->DownButton, SIGNAL(clicked()), commander, SLOT(TailscaleDown()));
    QObject::connect(ui->LogoutButton, SIGNAL(clicked()), commander, SLOT(Logout()));
    QObject::connect(ui->IPButton, SIGNAL(clicked()), commander, SLOT(IP()));
    QObject::connect(ui->StatusButton, SIGNAL(clicked()), commander, SLOT(Status()));
    QObject::connect(ui->ExitNodeInput, SIGNAL(textEdited(QString)), commander, SLOT(UpdateExitNodeName(QString)));
    QObject::connect(commander, SIGNAL(SendTailscaleOutput(QString)), ui->OutputBrowser, SLOT(append(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

