#include "singleappinstance.h"
#include <QHostAddress>
#include <QCoreApplication>
#include <QDebug>

SingleAppInstance::SingleAppInstance(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this)), m_socket(new QTcpSocket(this)) {
        connect(m_server, &QTcpServer::newConnection, this, [=]() {
        QTcpSocket *clientSocket = m_server->nextPendingConnection();
        qDebug() << "New instance connected";
        emit newInstanceConnected();
        clientSocket->disconnectFromHost();
    });
}

bool SingleAppInstance::tryToConnect() {
    m_socket->connectToHost(QHostAddress::LocalHost, 4567);
    return m_socket->waitForConnected(100);
}

void SingleAppInstance::startListening() {
    if (!m_server->listen(QHostAddress::LocalHost, 4567)) {
        qCritical() << "Impossible de démarrer le serveur: " << m_server->errorString();
    }
}
SingleAppInstance::~SingleAppInstance()
{

}