#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>

class Commander : public QObject
{
    Q_OBJECT
private:
    std::string ExitNodeName;
public:
    explicit Commander(QObject *parent = nullptr);

signals:

public slots:
    void TailscaleUp(bool ExitNode = false);
    void TailscaleDown();
    void IP();
    void Logout();
    void Status();
    void UpdateExitNodeName(std::string Name);

};

#endif // COMMANDER_H
