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

#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QProcess>
#include <QTimer>

class Commander : public QObject
{
    Q_OBJECT
private:
    QString ExitNodeName;
    QProcess tailscale;

    QString LastOperationText;
    QTimer TimeoutTimer;

public:
    explicit Commander(QObject *parent = nullptr);

signals:
    void SendTailscaleOutput(QString Output);
    void ClearText();

public slots:
    void TailscaleUp();
    void TailscaleDown();
    void IP();
    void Logout();
    void Status();
    void UpdateExitNodeName(QString Name);
    void GetTailscaleOutput();
    void TaskFinished(int ExitCode,QProcess::ExitStatus ExitStatus);
    void Timeout();

};

#endif // COMMANDER_H
