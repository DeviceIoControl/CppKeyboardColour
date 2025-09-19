#ifndef SINGLEAPPINSTANCE_H
#define SINGLEAPPINSTANCE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class SingleAppInstance : public QObject {
    Q_OBJECT

public:
    explicit SingleAppInstance(QObject *parent = nullptr);
    bool tryToConnect();
    void startListening();
    ~SingleAppInstance();

signals:
    void newInstanceConnected();

private:
    QTcpServer *m_server;
    QTcpSocket *m_socket;
};

#endif // SINGLEAPPINSTANCE_H