#include "commander.h"
#include "qdebug.h"

#include <utility>

#define PKEXEC "pkexec"
#define TAILSCALE "tailscale"
#define UP "up"
#define DOWN "down"
#define EXITNODE "--exit-node"
#define IP_STRING "ip"
#define LOGOUT "logout"
#define STATUS "status"
#define TIMEOUT_TIME_MS 300000

Commander::Commander(QObject *parent)
    : QObject{parent}
{
    connect(&tailscale, SIGNAL(readyReadStandardOutput()), this, SLOT(GetTailscaleOutput()));
    connect(&tailscale, SIGNAL(readyReadStandardError()), this, SLOT(GetTailscaleOutput()));
    connect(&tailscale, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &Commander::TaskFinished);
    connect(&TimeoutTimer, SIGNAL(timeout()), this, SLOT(Timeout()));

    TimeoutTimer.setSingleShot(true);
}

void Commander::TailscaleUp()
{
    LastOperationText = "Tailscale up";

    QStringList args = QStringList() << TAILSCALE << UP;

    if (ExitNodeName != "")
    {
        SendTailscaleOutput("Using Exit Node: " + ExitNodeName);
        args << EXITNODE << ExitNodeName;

        LastOperationText += " with exit node \" " + ExitNodeName + "\"";
    }

    tailscale.start(PKEXEC, args);
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::TailscaleDown()
{
    QStringList args = QStringList() << TAILSCALE << DOWN;
    tailscale.start(PKEXEC, args);

    LastOperationText = "Tailscale down";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::IP()
{
    QStringList args = QStringList() << IP_STRING;
    tailscale.start(TAILSCALE, args);

    LastOperationText = "Tailscale IP";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::Logout()
{
    QStringList args = QStringList() << TAILSCALE << LOGOUT;
    tailscale.start(PKEXEC, args);

    LastOperationText = "Tailscale logout";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::Status()
{
    QStringList args = QStringList() << STATUS;
    tailscale.start(TAILSCALE, args);

    LastOperationText = "Tailscale status";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
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
            SendTailscaleOutput("Authentication failed. Please try again (hint: the password may be wrong)." );
            return;
        }

        if (ExitCode == 0)
        {
            SendTailscaleOutput(LastOperationText + " has completed successfully.");
            return;
        }
        SendTailscaleOutput(LastOperationText + " has failed. Are you connected to a tailnet?");
        return;
    }

    SendTailscaleOutput("PKEXEC failed.");
}

void Commander::Timeout()
{
    if (tailscale.state() != QProcess::NotRunning)
    {
        tailscale.terminate();
    }

    SendTailscaleOutput("Timed out while waiting for " + LastOperationText + ". (5 minutes)");
}
