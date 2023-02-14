/*
Copyright (C) 2022 Ruby-Dragon
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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

