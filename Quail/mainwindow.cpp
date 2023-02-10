#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "commander.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Commander* commander = new Commander();

    //Inpput signals from clicking on buttons
    QObject::connect(ui->UpButton, SIGNAL(clicked()), commander, SLOT(TailscaleUp()));
    QObject::connect(ui->DownButton, SIGNAL(clicked()), commander, SLOT(TailscaleDown()));
    QObject::connect(ui->LogoutButton, SIGNAL(clicked()), commander, SLOT(Logout()));
    QObject::connect(ui->IPButton, SIGNAL(clicked()), commander, SLOT(IP()));
    QObject::connect(ui->StatusButton, SIGNAL(clicked()), commander, SLOT(Status()));

    //when the text is edited in the exit node box, update the stored exit node name
    QObject::connect(ui->ExitNodeInput, SIGNAL(textEdited(QString)), commander, SLOT(UpdateExitNodeName(QString)));

    //connect the output browser to the output from tailscale
    QObject::connect(commander, SIGNAL(SendTailscaleOutput(QString)), ui->OutputBrowser, SLOT(append(QString)));
    QObject::connect(commander, SIGNAL(ClearText()), ui->OutputBrowser, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

