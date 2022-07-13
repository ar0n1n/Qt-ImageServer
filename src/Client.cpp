#include "../includes/Client.hpp"

Client::Client(QObject *parent)
    : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(this, &Client::error, this, &Client::handleError);
}

void Client::connectToHost(const QHostAddress &ipAddress, quint16 port, int msecs)
{
    tcpSocket->connectToHost(ipAddress, port);

    if (tcpSocket->waitForConnected(msecs)) {
        qDebug() << "connected to server";
    }
    else {
        emit error(tcpSocket->error(), tcpSocket->errorString());
    }
}

void Client::disconnectFromHost()
{
    tcpSocket->disconnectFromHost();
}

bool Client::isConnected() const
{
    return tcpSocket->state() == QTcpSocket::ConnectedState;
}

void Client::handleError(int socketError, const QString& message)
{
    QMessageBox::critical(nullptr, tr("CLIENT ERROR"), tr(qPrintable(message)));
    qDebug() << "exiting" << message << socketError;
    exit(EXIT_FAILURE);
}

void Client::transferImage(const QString &imagePath)
{
    if (!isConnected()) {
        emit error(QTcpSocket::OperationError, "client in disconnected state");
        return;
    }

    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);

    QImage image (imagePath);

    out << (qint64)0 << image;
    out.device()->seek(0);
    out << (qint64)(byteArray.size() - sizeof(qint64));

    tcpSocket->write(byteArray);
    tcpSocket->waitForBytesWritten(-1);

    qDebug() << "sent:" << byteArray.size() << "bytes; image" << imagePath;

    byteArray.clear();
}

Client::~Client()
{
    tcpSocket->close();
}