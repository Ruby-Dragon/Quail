#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include "tailscale.h"

class Commander : public QObject
{
    Q_OBJECT
private:
    QString ExitNodeName;
    Tailscale tailscale;

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
