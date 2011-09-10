#ifndef SERVERPAIR_H
#define SERVERPAIR_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>

class ServerPair : public QThread
{
    Q_OBJECT
public:
    ServerPair(QTcpSocket* fromClient, QTcpSocket* toEndpoint);
    QTcpSocket* client;
    QTcpSocket* server;

signals:
    void selfDestruct(ServerPair* pair);

private slots:
    void lostConnection();
    void gotData();
    void rest10();

private:
    void run();

    bool alive;
};

#endif // SERVERPAIR_H
