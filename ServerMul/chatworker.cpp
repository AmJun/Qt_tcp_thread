  #include "chatworker.h"
#include <QDir>
#include <QFile>

/*
    func：聊天室工作线程，处理接收到的数据及保存文件，向使用对象发出信号
*/
chatworker::chatworker(QTcpSocket* ms)
{
    m_tcp = ms;
}
//报文-三种类型的启动报文-8字节
// aa55(2字节)Type03(1字节)fizeSize（4字节）filenameSize(1字节) 16进制  文件类型 8个字节
// aa55(2字节)Type01(1字节)ClientNameSize(1字节)补0  连接时收到的第一包-客户端标识
// aa55(2字节)Type02（1字节)size(2字节)补0(剩余字节)
void chatworker::run()
{
    analyTimer = new QTimer(this);
    //收数据
    connect(m_tcp,&QTcpSocket::readyRead,this,[=]{
        mReceivedData.append(m_tcp->readAll());
    });
 //
    connect(analyTimer,&QTimer::timeout,this,&chatworker::process);
    connect(m_tcp,&QTcpSocket::disconnected,this,&chatworker::stopThread);
    analyTimer->start(20);
    //使线程进入消息循环
    while(runFlag){
        exec();
    }
}
//发送数据
void chatworker::writeData(QString data)
{
    if(m_tcp->isValid()){
        m_tcp->write(data.toUtf8());
    }
}
//文件
void chatworker::processFile()
{
    static bool startFlag = false;
    static QFile* file;
//    static  long fileCount = 0;
    //创建文件对象
    if((!startFlag)&&(mReceivedData.size()>=filenameSize)){
        QByteArray fileNameBytes = mReceivedData.mid(0, filenameSize);
        mReceivedData.remove(0,filenameSize);  //
        QString fileName = QString::fromUtf8(fileNameBytes.constData(), fileNameBytes.size());
        //检测目录
        if(checkPath("D:/","toolsDownload")){
            QString PATH = "D:/toolsDownload/";
            fileName = PATH+fileName;
        }
        // 使用提取的文件名创建 QFile 对象
        file = new QFile(fileName);
        if(!file->isOpen()){
            file->open(QFile::WriteOnly);
        }
        emit fileStartSignal(fileName);
        startFlag = true;
    }
    //开始写入数据
    if(startFlag){
        qDebug()<<fileCount;
        //结束标志
        if(fileSize != fileCount){
            //缓冲区取数据
            long needCount = fileSize-fileCount;
            if(needCount<mReceivedData.size()){
                 QByteArray Bytes = mReceivedData.mid(0, needCount);
                 mReceivedData.remove(0,needCount);
                 //
                 file->write(Bytes);
                 fileCount += needCount;
            }
            else {
                file->write(mReceivedData);
                fileCount += mReceivedData.size();
                mReceivedData.clear();
            }
            //TODO
            //发送文件进度
            //...emit
        }
        else{
            startFlag = false;
            fileCount = 0;
            file->close();
            emit fileSignal();
            //结束文件写入
            flag=0;
        }
    }
}
//聊天信息
void chatworker::processChat()
{
    //查找缓冲区
    qDebug()<<"this is test:"<<mReceivedData;
    if(mReceivedData.size()>=dataSizeValue){
        QByteArray databytes = mReceivedData.mid(0,dataSizeValue);
        mReceivedData.remove(0,dataSizeValue);  //
        //发送信号
        emit chatSignal(QString::fromUtf8(databytes));
        //恢复
        flag=0;
    }
    //长度不够-等待
    else{
        return;
    }

}
//客户端名称
void chatworker::processName()
{
    //查找缓冲区
    if(mReceivedData.size()>=clientNameSizeValue){
        QByteArray cname = mReceivedData.mid(0,clientNameSizeValue);
        mReceivedData.remove(0,clientNameSizeValue);  //
        //发送信号
        emit nameSignal(QString::fromUtf8(cname));
        //恢复
        flag=0;
    }
    //长度不够-等待
    else{
        return;
    }
}

void chatworker::process()
{
    //启动帧
    QByteArray BW;
    if(flag==0){
        BW = analyseBw();
        //无效数据
        if(BW.size() != 8){
            return;
        }

        // 解析帧标识（1个字节）
        QByteArray mark = BW.mid(2, 1);
        quint8 markValue = static_cast<quint8>(mark[0]);
        if(markValue==0x01){
            //解析客户端名称大小 1字节
            QByteArray clientNameSize = BW.mid(3,1);
            clientNameSizeValue = static_cast<quint8>(clientNameSize[0]);
            flag=1;
        }
        else if (markValue==0x02) {
            //解析待接收的数据长度 2字节
            QByteArray dataSize = BW.mid(3,2);
            dataSizeValue = (static_cast<quint8>(dataSize[0])) | static_cast<quint8>(dataSize[1]<<8);
            qDebug()<<"datasizeValue:"<<dataSizeValue;
            flag=2;
        }
        else if (markValue==0x03) {
            //解析待接收文件大小
            fileSize =  (static_cast<quint8>(BW[3])) |
                                (static_cast<quint8>(BW[4]) << 8) |
                                (static_cast<quint8>(BW[5]) << 16) |
                                (static_cast<quint8>(BW[6]) << 24);
            //解析待接收文件名大小
            filenameSize = static_cast<quint8>(BW[7]);
            flag=3;
        }
        else{
            return;
        }
    }
    else if (flag==1) {
        processName();
    }
    else if (flag==2) {
        processChat();
    }
    else if (flag==3) {
        processFile();
    }
    else {
        return;
    }


}

QByteArray chatworker::analyseBw()
{
    QByteArray bw;
    bool findHeader = false;
    //处理启动报文数据
    //usable_flag 标识读取是否完整
    if(usable_flag){
//        qDebug()<<"mrecevicedata:"<<mReceivedData;
        while((mReceivedData.size()-count_bw)>1){
            QByteArray header = mReceivedData.mid(count_bw,2);
            quint16 headerValue = (static_cast<quint8>(header[0]) << 8) | static_cast<quint8>(header[1]);
            if(headerValue == 0x55AA){
                findHeader = true;
                break;
            }
            count_bw += 1;
         }
    }
    if(findHeader || usable_flag==false){
        if((mReceivedData.size()-count_bw)>=8){
            bw.append(mReceivedData.mid(count_bw,8));
//            qDebug()<<"bw:"<<bw;
//                //校验不通过
//                if(checkSum(bw)==false){
//                    bw.clear();
//                }
            mReceivedData.remove(0,count_bw+8);  //清除缓冲区中被拿走的数据
            count_bw = 0;
            usable_flag = true;

        }
        //长度不够-读到报头
        else{
            usable_flag = false;
        }
    }
    //findHeader == false
    else{
        //长度不够-未读到报头 !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    return bw;
}

void chatworker::stopThread()
{
    emit end();
    m_tcp->deleteLater();
    analyTimer->stop();
    runFlag = false;
}

bool chatworker::checkPath(const QString &drive, const QString &directoryName)
{
    //检查盘符
     QDir driveDir(drive + "/");
     if(!driveDir.exists()){
         return false;
     }
     // 构建完整的目录路径
     QString fullPath = drive + "/" + directoryName;
     QDir dir(fullPath);

     // 检查目录是否存在
     if (!dir.exists()) {
         // 如果目录不存在，尝试创建目录
         if (!dir.mkpath(fullPath)) {
             qWarning() << "Failed to create directory:" << fullPath;
             return false;
         } else {
             qDebug() << "Directory created:" << fullPath;
         }
     } else {
         qDebug() << "Directory already exists:" << fullPath;
     }

     return true;
}

////校验和计算
//bool MainWindow::checkSum(QByteArray& data){
//// 计算校验和
//char checksum = 0;
//for(int i = 2; i < 70; ++i) {
//    checksum += data[i];
//}
//// 比对校验和
//if(checksum == data[70]) {
//    // 校验和匹配，处理数据
//    return true;
//} else {
//    // 校验和不匹配，处理错误
//    qDebug() << "校验和不匹配，数据可能出错！";
//    return false;
//}
//}
//
