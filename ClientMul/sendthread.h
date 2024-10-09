#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>

class SendThread : public QThread
{
    Q_OBJECT
public:
    explicit SendThread(QTcpSocket* ss, QObject *parent = nullptr);
    void run() override;
    void sendClientName(QString name);
    void sendChat(QString txt);
    void sendFile(QString path);

    //
    QTcpSocket* m_socket;
    bool runFlag=true;


signals:

};
enum type{
    clientName=0x01,
    chatTxt=0X02,
    file=0x03
};

#endif // SENDTHREAD_H
