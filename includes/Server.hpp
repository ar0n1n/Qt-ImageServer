#pragma once

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QThreadPool>
#include <QtNetwork/QTcpServer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

#include "Runnable.hpp"

class Server : public QTcpServer
{
    Q_OBJECT

    public:
        Server(quint32 maxImages = 16, QObject *parent = nullptr);
        ~Server();

        void start(const QHostAddress& address = QHostAddress::Any, quint16 port = 0);

    protected:
        void incomingConnection(qintptr socketDescriptor) override;

    private:
        QThreadPool threadPool;
        QVector<QLabel *> ringBuffer;
        quint32 _insertPos;

    signals:
        void error(int socketError, const QString& message);

    private slots:
        void displayImage(QImageSharedPtr image, const QSize& size = QSize(500, 500));
        void handleError(int errorCode, const QString& message);
};
