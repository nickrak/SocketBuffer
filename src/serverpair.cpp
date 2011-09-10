#include "serverpair.h"
#include "socketbuffermanager.h"

#include <iostream>

using namespace std;

ServerPair::ServerPair(QTcpSocket *fromClient, QTcpSocket *toEndpoint) :
    QThread(0)
{
    this->alive = true;
    this->client = fromClient;
    this->server = toEndpoint;

    this->connect(this->client, SIGNAL(disconnected()), this, SLOT(lostConnection()));
    this->connect(this->server, SIGNAL(disconnected()), this, SLOT(lostConnection()));

    this->connect(this->client, SIGNAL(readyRead()), this, SLOT(gotData()));
    this->connect(this->server, SIGNAL(readyRead()), this, SLOT(gotData()));
}

void ServerPair::lostConnection()
{
    if (this->alive)
    {
        this->alive = false;
        this->client->close();
        this->server->close();
    }
    this->selfDestruct(this);
}

void ServerPair::rest10()
{
    this->start(QThread::LowPriority);
    this->wait();
}

void ServerPair::gotData()
{
    QByteArray buffer;
    while (this->client->bytesAvailable() > 0 || this->server->bytesAvailable())
    {
        this->rest10();
        if (this->client->bytesAvailable() > 0)
        {
            buffer.resize(this->client->bytesAvailable());
            this->client->read(buffer.data(), buffer.size());
            this->server->write(buffer);
        }
        if (this->server->bytesAvailable() > 0)
        {
            buffer.resize(this->server->bytesAvailable());
            this->server->read(buffer.data(), buffer.size());
            this->client->write(buffer);
        }
    }
}

void ServerPair::run()
{
    this->usleep(100);
}
