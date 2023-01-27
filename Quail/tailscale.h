#ifndef TAILSCALE_H
#define TAILSCALE_H

#include <QProcess>
#include <QObject>

class Tailscale : public QProcess
{
    Q_OBJECT
public:
    Tailscale();


};

#endif // TAILSCALE_H
