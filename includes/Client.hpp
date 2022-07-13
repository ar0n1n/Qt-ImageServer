#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtGui/QImage>
#include <QtWidgets/QMessageBox>

class Client : public QObject
{
   Q_OBJECT

    public:
        Client(QObject *parent = nullptr);
        ~Client();

        void connectToHost(const QHostAddress &ipAddress = QHostAddress::Any,
                           quint16 port = 0, int msecs = 30000);
        void transferImage(const QString &imagePath);
        void disconnectFromHost();
        bool isConnected() const;

    signals:
        void error(int socketError, const QString &message);

    private slots:
        void handleError(int socketError, const QString &message);

    private:
        QTcpSocket  *tcpSocket;
};