// #include <vld.h>

#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>
#include <QtNetwork/QHostAddress>
#include "includes/Client.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("image client app");
    parser.addHelpOption();

    parser.addPositionalArgument("port", "server port");
    parser.addPositionalArgument("imagePath", "image path");

    QCommandLineOption hostOption(QStringList() << "i" << "host",
        "host", "", "127.0.0.1");
    parser.addOption(hostOption);

    parser.process(app);
    
    Client client;

    client.connectToHost(QHostAddress(parser.value(hostOption)),
                         parser.positionalArguments()[0].toInt());

    client.transferImage(parser.positionalArguments()[1]);

    return 0;
}
