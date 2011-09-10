#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QFile>
#include <iostream>
#include "socketbuffermanager.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args;
    for (int i = 1; i < argc; i++)
    {
        args << QString(argv[i]);
    }

    QString host = "";
    int portIn = -1;
    int portOut = -1;
    bool server = false;

    QHash<QString, QString> props;

    foreach (QString arg, args)
    {
        QStringList pa = arg.split("=");
        QString prop = pa.first();
        QString val = pa.last();

        props.insert(prop, val);
    }

    cout << "SocketBuffer v1.1" << endl;
    cout << "(c)2011 Nick Rakoczy\n" << endl;

    if (props.contains("-interactive") || props.contains("-i"))
    {
        QFile scan;
        QByteArray buffer;
        scan.open(stdin, QFile::ReadOnly);

        cout << "Starting in Interactive Mode\n" << endl;

        cout << "Target Host Address or IP Address>" << flush;
        buffer = scan.readLine();
        host = QString(buffer);

        cout << "Target Host Port [int]>" << flush;
        buffer = scan.readLine();
        portOut = QString(buffer).toInt();

        cout << "Listen Port [int]>" << flush;
        buffer = scan.readLine();
        portIn = QString(buffer).toInt();

        cout << "Server Mode [y|n]>" << flush;
        buffer = scan.readLine();
        server = QString(buffer).startsWith("y");

        scan.close();
    }
    else if ((props.contains("-target") || props.contains("-t")) && (props.contains("-port") || props.contains("-p")) && (props.contains("-listen") || props.contains("-l")))
    {
        host = (props.contains("-target") ? props["-target"] : props["-t"]);
        portOut = (props.contains("-port") ? props["-port"] : props["-p"]).toInt();
        portIn = (props.contains("-listen") ? props["-listen"] : props["-l"]).toInt();
        server = props.contains("-server") || props.contains("-s");
        cout << "Starting in non-Interactive Mode\n" << endl;
        cout << "Target Host: " << host.toAscii().data() << ":" << QString::number(portOut).toAscii().data() << "\n";
        cout << "Listening Port: " << QString::number(portIn).toAscii().data() << "\n";
        cout << "Mode: " << (server ? "Server" : "Client") << endl;
    }
    else
    {
        cout << "usage: SocketBuffer [options]\n" << endl;
        cout << "Options:" << endl;
        cout << "   -t=* | -target=*:" << endl;
        cout << "      The hostname or ip address of the server you want to connect to." << endl;
        cout << "   -p=* | -port=*:" << endl;
        cout << "      The port on the server you are connecting to." << endl;
        cout << "   -l=* | -listen=*:" << endl;
        cout << "      The port on this computer that will be forwarding." << endl;
        cout << "   -s | -server:" << endl;
        cout << "      Acts as a server. Listen on all interfaces, not just localhost." << endl;
        cout << "   -i | -interactive:" << endl;
        cout << "      Starts the program in interactive mode. [not valid with any other parameters]" << endl;
        return 0;
    }

    cout << "\n\nPress Ctrl+C to quit" << flush;
    bool debug = props.contains("-debug");
    new SocketBufferManager(host, server, portIn, portOut, debug);

    a.exec();
    return 0;
}
