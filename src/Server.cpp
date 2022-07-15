#include "../includes/Server.hpp"

Server::Server(quint32 maxImages, QObject *parent)
    : QTcpServer(parent), _insertPos(0)
{

    qRegisterMetaType<QImageSharedPtr>("QImageSharedPtr");

    connect(this, &Server::error, this, &Server::handleError);
    ringBuffer.resize(maxImages);
}

void Server::start(const QHostAddress& ipAddress, quint16 port)
{
    if (listen(ipAddress, port)) {
        qDebug() << "server listening on" << ipAddress.toString() << port;
    }
    else {
        emit error(serverError(), errorString());
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    LoadImageTask *task = new LoadImageTask(socketDescriptor);
    task->setAutoDelete(true);

    connect(task, &LoadImageTask::imageReady, this, &Server::displayImage);
    connect(task, &LoadImageTask::workerError, this, &Server::handleError);

    qDebug() << "incoming connection" << socketDescriptor;

    threadPool.start(task);
}

void Server::displayImage(QSharedPointer<QImage> image, const QSize& size)
{
    if (!ringBuffer[_insertPos]) {
        ringBuffer[_insertPos] = new QLabel();
    }

    ringBuffer[_insertPos]->setPixmap(
       QPixmap::fromImage(*image)
        .scaled(size, Qt::KeepAspectRatio)
    );

    ringBuffer[_insertPos]->show();
    _insertPos = ++_insertPos % ringBuffer.size();
}

void Server::handleError(int errorCode, const QString& message)
{
    QMessageBox::critical(nullptr, tr("SERVER ERROR"), tr(qPrintable(message)));
    qDebug() << "exiting" << message << errorCode;
    exit(EXIT_FAILURE);
}

Server::~Server()
{
    qDeleteAll(ringBuffer);
}
