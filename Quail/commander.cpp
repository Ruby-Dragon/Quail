#include "commander.h"
#include "qdebug.h"

#include <utility>

#define PKEXEC "pkexec"
#define TAILSCALE "tailscale"
#define UP "up"

Commander::Commander(QObject *parent)
    : QObject{parent}
{

}

void Commander::TailscaleUp()
{
    //SendTailscaleOutput("Is it working?");

    QStringList args = QStringList() << TAILSCALE << UP;
    tailscale.start(PKEXEC, args);

    connect(&tailscale, SIGNAL(readyReadStandardOutput()), this, SLOT(GetTailscaleOutput()));

    //tailscale.waitForFinished();
    //qInfo() << "whathappened " << tailscale.error();
}

void Commander::TailscaleDown()
{

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