#include "socketbuffermanager.h"
#include <iostream>

using namespace std;

SocketBufferManager::SocketBufferManager(QString target, bool server, int inPort, int outPort, bool debug) : QObject(0)
{
    this->debug = debug;

    this->outHost = target;
    this->outPort = outPort;

    this->connect(&this->listener, SIGNAL(newConnection()), this, SLOT(gotConnection()));
    this->listener.listen(server ? QHostAddress::Any : QHostAddress::LocalHost, inPort);

    if (this->debug)
    {
        cout << "DEBUG ENABLED" << endl;
    }
}

void SocketBufferManager::gotConnection()
{
    while (this->listener.hasPendingConnections())
    {
        QTcpSocket* incoming = this->listener.nextPendingConnection();

        QTcpSocket* outgoing = new QTcpSocket();
        outgoing->connectToHost(this->outHost, this->outPort);

        ServerPair* s = new ServerPair(incoming, outgoing);

        this->connect(s, SIGNAL(selfDestruct(ServerPair*)), this, SLOT(disconnected(ServerPair*)));
        this->sockets.append(s);

        if (this->debug)
        {
            cout << "Got Connection: " << incoming->peerAddress().toString().toAscii().data() << endl;
        }
    }
}

void SocketBufferManager::disconnected(ServerPair *pair)
{
    this->sockets.removeAll(pair);
    if (this->debug)
    {
        cout << "Disconnected" << endl;
    }
}
