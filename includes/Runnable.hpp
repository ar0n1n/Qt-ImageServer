#pragma once

#include <QtCore/QDataStream>
#include <QtCore/QRunnable>
#include <QtGui/QImage>
#include <QtNetwork/QTcpSocket>

typedef QSharedPointer<QImage> QImageSharedPtr;
Q_DECLARE_METATYPE(QImageSharedPtr);

class LoadImageTask : public QObject, public QRunnable
{
   Q_OBJECT

    public:
        LoadImageTask(qintptr socketDescriptor);

    protected:
        void run();

    private:
        qintptr socketDescriptor;

    signals:
        void imageReady(QImageSharedPtr image, const QSize& size = QSize(500, 500));
        void workerError(int socketError, const QString& message);

};
