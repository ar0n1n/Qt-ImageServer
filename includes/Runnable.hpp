#include <QtCore/QRunnable>
#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>
#include <QtGui/QImage>

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