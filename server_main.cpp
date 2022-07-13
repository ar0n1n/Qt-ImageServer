#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>
#include <QtNetwork/QHostAddress>
#include "includes/Server.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    QCommandLineParser parser;
    parser.setApplicationDescription("image server app");
    parser.addHelpOption();
 
    QCommandLineOption hostOption(QStringList() << "i" << "host",
                                  "host", "", "127.0.0.1");
    parser.addOption(hostOption);

    QCommandLineOption portOption(QStringList() << "p" << "port",
                                  "port", "", "1234");
    parser.addOption(portOption);

    parser.process(app);

    Server server;
    server.start(QHostAddress(parser.value(hostOption)),
                 parser.value(portOption).toInt());

    return app.exec();
}