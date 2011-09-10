#ifndef SOCKETBUFFERMANAGER_H
#define SOCKETBUFFERMANAGER_H

#include <QObject>
#include <QStringList>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>

#include "serverpair.h"

class SocketBufferManager : public QObject
{
    Q_OBJECT

public:
    SocketBufferManager(QString target, bool server, int inPort, int outPort, bool debug);

private slots:
    void gotConnection();
    void disconnected(ServerPair* pair);

private:
    QTcpServer listener;
    QList<ServerPair*> sockets;

    QString outHost;
    int outPort;

    bool debug;

};

#endif // SOCKETBUFFERMANAGER_H
