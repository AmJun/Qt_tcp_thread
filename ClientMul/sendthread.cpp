#include "sendthread.h"
#include <QDebug>
#include <QFileInfo>

SendThread::SendThread(QTcpSocket* ss,QObject *parent) : QThread(parent)
{
    m_socket = ss;
}

void SendThread::run()
{
    while(runFlag){
        exec();
    }
}
//发送name
void SendThread::sendClientName(QString name)
{
    QByteArray start;
    //2字节的报头  0x55aa
    start.append(static_cast<char>(0x55));
    start.append(static_cast<char>(0xAA));
    //1字节的报文类型 0x01
    start.append(type(clientName));
    //1字节
    unsigned int size = name.toUtf8().size();
       //将4字节的int转为char  size<256
    start.append(static_cast<char>(size));
    //填充4字节
    char padding[4]= {0,0,0,0};
    start.append(padding,4);
    //发送启动报文
    m_socket->write(start);
    qDebug() << start;
    QByteArray nn = name.toUtf8();
    m_socket->write(nn);


}

void SendThread::sendChat(QString txt)
{
    QByteArray chat;
    //2字节的报头  0x55aa
    chat.append(static_cast<char>(0x55));
    chat.append(static_cast<char>(0xAA));
    //1字节的报文类型 0x02
    chat.append(type(chatTxt));
    //2字节
    uint16_t size = txt.toUtf8().size();
    //将int转为char,占2个字节
    //大端模式  低字节在高地址
    chat.append(static_cast<char>(size & 0xFF));
    chat.append(static_cast<char>((size >> 8) & 0xFF));
    //填充3字节
    char padding[3]= {0,0,0};
    chat.append(padding,3);
    //发送报文
    m_socket->write(chat);
    qDebug() << chat;
    //发送数据
    QByteArray nn = txt.toUtf8();
    m_socket->write(nn);
}
void SendThread::sendFile(QString path)
{
    QFile files(path);
    if(!files.open(QFile::ReadOnly)){
        return;
    }
    QFileInfo fileInfo(path);
    QString fileName = fileInfo.fileName(); // 获取不带路径的文件名
    QByteArray filebw;
    //2字节的报头  0x55aa
    filebw.append(static_cast<char>(0x55));
    filebw.append(static_cast<char>(0xAA));
    //1字节的报文类型 0x03
    filebw.append(type(file));
    //4字节 fileSize
    uint32_t size = files.size();
    //大端模式  低字节在高地址
    filebw.append(static_cast<char>(size & 0xFF));
    filebw.append(static_cast<char>((size >> 8) & 0xFF));
    filebw.append(static_cast<char>((size >> 16) & 0xFF));
    filebw.append(static_cast<char>((size >> 24) & 0xFF));
    //1字节 fileNameSize
    uint8_t nameSize =  fileName.toUtf8().size();
    filebw.append(static_cast<char>(nameSize));
    //发送报文
    m_socket->write(filebw);
    //发送name
    m_socket->write(fileName.toUtf8());
    //发送文件
    QByteArray tempData;
    while(!files.atEnd()){
        tempData = files.readLine();
        m_socket->write(tempData);
    }
    //2024.10.8测试通过
    //2024.10.8测试符合要求

}
