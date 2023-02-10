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
#define PKEXEC_WRONG_PASSWORD 127

Commander::Commander(QObject *parent)
    : QObject{parent}
{
    //get output from tailscale and know when the process has ended
    connect(&tailscale, SIGNAL(readyReadStandardOutput()), this, SLOT(GetTailscaleOutput()));
    connect(&tailscale, SIGNAL(readyReadStandardError()), this, SLOT(GetTailscaleOutput()));
    connect(&tailscale, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &Commander::TaskFinished);

    connect(&TimeoutTimer, SIGNAL(timeout()), this, SLOT(Timeout()));

    TimeoutTimer.setSingleShot(true);
}

void Commander::TailscaleUp()
{
    ClearText();
    LastOperationText = "Tailscale up";

    QStringList args = QStringList() << TAILSCALE << UP;

    //check if there is an exit node entered in
    if (ExitNodeName != "")
    {
        //use that exit node
        SendTailscaleOutput("Using Exit Node: " + ExitNodeName);
        args << EXITNODE << ExitNodeName;

        //add to text so user knows if they input the wrong node which node was used
        LastOperationText += " with exit node \" " + ExitNodeName + "\"";
    }

    //PKEXEC prompts for root password because up, down, and logout require sudo
    tailscale.start(PKEXEC, args);
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::TailscaleDown()
{
    ClearText();
    QStringList args = QStringList() << TAILSCALE << DOWN;
    tailscale.start(PKEXEC, args);

    LastOperationText = "Tailscale down";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::IP()
{
    ClearText();
    //IP and status do not require root privileges
    QStringList args = QStringList() << IP_STRING;
    tailscale.start(TAILSCALE, args);

    LastOperationText = "Tailscale IP";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::Logout()
{
    ClearText();
    QStringList args = QStringList() << TAILSCALE << LOGOUT;
    tailscale.start(PKEXEC, args);

    LastOperationText = "Tailscale logout";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::Status()
{
    ClearText();
    QStringList args = QStringList() << STATUS;
    tailscale.start(TAILSCALE, args);

    LastOperationText = "Tailscale status";
    TimeoutTimer.start(TIMEOUT_TIME_MS);
}

void Commander::UpdateExitNodeName(QString Name)
{
    //if there is something input, use that
    if (Name != "")
    {
        ExitNodeName = std::move(Name);
        return;
    }
    ExitNodeName = "";
}

void Commander::GetTailscaleOutput()
{
    QString Output = tailscale.readAllStandardOutput();
    //debug, user should never see this
    qInfo() << Output << ", was output";

    SendTailscaleOutput(Output);
}

void Commander::TaskFinished(int ExitCode,QProcess::ExitStatus ExitStatus)
{
    if (ExitStatus == QProcess::NormalExit)
    {
        //127 is the current code to show wrong password in PKEXEC
        if (ExitCode == PKEXEC_WRONG_PASSWORD)
        {
            SendTailscaleOutput("Authentication failed. Please try again (hint: the password may be wrong)." );
            return;
        }

        if (ExitCode == 0)
        {
            SendTailscaleOutput(LastOperationText + " has completed successfully.");
            return;
        }

        //tailscale does not have exit codes that detail the actual error, so there is no way to know what the error was as far as I know
        SendTailscaleOutput(LastOperationText + " has failed. Are you connected to a tailnet?");
        return;
    }

    //something really weird must have happened
    SendTailscaleOutput("PKEXEC failed.");
}

//just in case
void Commander::Timeout()
{
    if (tailscale.state() != QProcess::NotRunning)
    {
        tailscale.terminate();
    }

    SendTailscaleOutput("Timed out while waiting for " + LastOperationText + ". (5 minutes)");
}
