#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QProcess>

class Commander : public QObject
{
    Q_OBJECT
private:
    QString ExitNodeName;

public:
    explicit Commander(QObject *parent = nullptr);

signals:

public slots:
    void TailscaleUp(bool ExitNode = false);
    void TailscaleDown();
    void IP();
    void Logout();
    void Status();
    void UpdateExitNodeName(QString Name);
    void GetTailscaleOutput(QProcess Process);

};

#endif // COMMANDER_H
