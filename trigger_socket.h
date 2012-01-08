#ifndef TRIGGER_SOCKET_H
#define TRIGGER_SOCKET_H

#include <QUdpSocket>

class TriggerSocket : public QUdpSocket
{
    Q_OBJECT
public:
    explicit TriggerSocket(QObject *parent = 0);

signals:

public slots:

};

#endif // TRIGGER_SOCKET_H
