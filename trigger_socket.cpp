#include "trigger_socket.h"

TriggerSocket::TriggerSocket(QObject *parent) :
    QUdpSocket(parent)
{
    bind(QHostAddress("127.0.0.1"), 63949);
}
