#include "../includes/Runnable.hpp"

LoadImageTask::LoadImageTask(qintptr socketDescriptor)
    : socketDescriptor(socketDescriptor)
{
}

void LoadImageTask::run()
{
    QTcpSocket tcpSocket;
    tcpSocket.setSocketDescriptor(socketDescriptor);

    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_5_15);

    QSharedPointer<QImage> image (new QImage());
    qint64 bytesToReceive = 0;

    do {
        if (!tcpSocket.waitForReadyRead()) {
            emit workerError(tcpSocket.error(), tcpSocket.errorString());
            return;
        }

        if (bytesToReceive == 0) {
            if (tcpSocket.bytesAvailable() < (int)sizeof(qint64))
                continue;
            in >> bytesToReceive;
            qDebug() << "bytes to receive:" << bytesToReceive;
        }

    } while (tcpSocket.bytesAvailable() < bytesToReceive);

    in >> *image;

    qDebug() << "transfer completed";

    if (!image->isNull()) {
        emit imageReady(image);
    }
    else if (bytesToReceive) {
        qDebug() << "image corrupted; skipping";
    }
}
