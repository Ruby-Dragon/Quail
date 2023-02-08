#include "commander.h"
#include "qdebug.h"

#include <utility>

#define PKEXEC "pkexec"
#define TAILSCALE "tailscale"
#define UP "up"
#define DOWN "down"
#define EXITNODE "--exit-node"

Commander::Commander(QObject *parent)
    : QObject{parent}
{
    connect(&tailscale, SIGNAL(readyReadStandardOutput()), this, SLOT(GetTailscaleOutput()));
    connect(&tailscale, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &Commander::TaskFinished);
}

void Commander::TailscaleUp()
{
    //SendTailscaleOutput("Is it working?");

    LastOperationText = "Tailscale up";

    QStringList args = QStringList() << TAILSCALE << UP;

    if (ExitNodeName != "")
    {
        SendTailscaleOutput("Using Exit Node: " + ExitNodeName);
        args << EXITNODE << ExitNodeName;

        LastOperationText += " with exit node \" " + ExitNodeName + "\"";
    }

    tailscale.start(PKEXEC, args);

    //tailscale.waitForFinished();
    //qInfo() << "whathappened " << tailscale.error();
}

void Commander::TailscaleDown()
{
    QStringList args = QStringList() << TAILSCALE << DOWN;
    tailscale.start(PKEXEC, args);

    connect(&tailscale, SIGNAL(readyReadStandardOutput()), this, SLOT(GetTailscaleOutput()));
}

void Commander::IP()
{

}

void Commander::Logout()
{

}

void Commander::Status()
{

}

void Commander::UpdateExitNodeName(QString Name)
{
    if (Name != "")
    {
        ExitNodeName = std::move(Name);
        return;
    }
    ExitNodeName = nullptr;
}

void Commander::GetTailscaleOutput()
{
    QString Output = tailscale.readAllStandardOutput();
    qInfo() << Output << ", was output";
    SendTailscaleOutput(Output);
}

void Commander::TaskFinished(int ExitCode,QProcess::ExitStatus ExitStatus)
{
    if (ExitStatus == QProcess::NormalExit)
    {
        if (ExitCode == 127)
        {
            SendTailscaleOutput("Authentication Failed. Please try again (hint: the password may be wrong)." );
            return;
        }

        if (ExitCode == 0)
        {
            SendTailscaleOutput(LastOperationText + " has completed successfully.");
            return;
        }
        SendTailscaleOutput(LastOperationText + " has completed normally. Exit Code: " + QString::number(ExitCode));
        return;
    }

    SendTailscaleOutput(LastOperationText + " has failed.");
}
