#ifndef CHATWORKER_H
#define CHATWORKER_H
//头
#include <QThread>
#include <QTcpSocket>
#include <QTimer>
//继承
class chatworker : public QThread
{
    Q_OBJECT
public:
    explicit chatworker(QTcpSocket* ms);
    //重写run
    void run() override;
    void writeData(QString data);
    void processFile();
    void processChat();
    void processName();

    QByteArray analyseBw();
    void analesedata();
    void stopThread();
    bool checkPath(const QString &drive, const QString &directoryName);

private:
    //线程工作标志
    bool runFlag = true;
    //创建套接字对象
    QTcpSocket* m_tcp;
//    //已接收文件字节数量
    long fileCount = 0;
    //客户端名称长度
    quint8 clientNameSizeValue;
    //当前文件的文件名 文件名长度 文件长度
    std::string filename;
    quint8 filenameSize;
    quint32 fileSize;
    //聊天数据长度
    quint16 dataSizeValue;
    //定时器
    QTimer* analyTimer;
    //数据缓存区
    QByteArray mReceivedData;
    //
    bool usable_flag=true;
    int flag = 0;
    int count_bw=0;
public slots:
    void process();
signals:
    void nameSignal(QString clientName);
    void chatSignal(QString chatContent);
    void fileSignal();
    void fileStartSignal(QString filename);
    void end();

};

#endif // CHATWORKER_H
