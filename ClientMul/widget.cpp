#include "widget.h"
#include "ui_widget.h"
#include "sendthread.h"
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //
    ui->serverPortEdit->setText("8899");
    ui->serverAddrlineEdit->setText("127.0.0.1");
    //
    m_socket = new QTcpSocket();
    thr = new SendThread(m_socket);
    thr->start();
    //收数据
    connect(m_socket,&QTcpSocket::readyRead,this,[=]{
        QByteArray data = m_socket->readAll();
        ui->recetextBrowser->append("server:"+data);
    });
    //断开连接
    connect(m_socket,&QTcpSocket::disconnected,this,[=]{
        m_socket->close();
//        m_tcp->deleteLater();
        ui->bindServerBtn->setEnabled(true);
    });
    //连接
    connect(m_socket,&QTcpSocket::connected,this,[=]{
        ui->recetextBrowser->append("client:成功连接到服务器");
        //ui
        ui->bindServerBtn->setDisabled(true);
        thr->sendClientName(myName);
        //

    });
}

Widget::~Widget()
{
    delete ui;
}

//bind server
void Widget::on_bindServerBtn_clicked()
{
    //
    bool isOk;
    QString names = QInputDialog::getText(NULL,"客户机名称","更新名称",QLineEdit::Normal,myName,&isOk);
    if(isOk){
        //有效
        ui->nameLable->setText(names);
        myName = names;
    }
    //
    if(m_socket==NULL){
        m_socket = new QTcpSocket(this);
    }
    QString addr = ui->serverAddrlineEdit->text();
    unsigned short port = ui->serverPortEdit->text().toShort();
    //连接
    m_socket->connectToHost(addr,port);
}
//断开连接
void Widget::on_disconnectBtn_clicked()
{
    //close 导致disconnected信号发出
    m_socket->close();
}
//发送普通聊天信息
void Widget::on_sendBtn_clicked()
{
    if(!m_socket->isValid()){
        return;
    }
    QString data = ui->sendtextEdit->toPlainText();
    thr->sendChat(data);
    //
    ui->recetextBrowser->append("我："+data);

}

void Widget::on_sendFileBtn_clicked()
{
    if(!m_socket->isValid()){
        QMessageBox::information(this,"TIPS","先连接",QMessageBox::Ok);
        return;
    }
    //选择文件
    QString curPath = QDir::currentPath();  //获取当前应用程序的目录
    //   QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所以文件(*.*);;图片文件(*.jpg *.png *.tif *.gif)"; //文件过滤器（选择不同后缀的文件）
    QString filter = "所有文件(*.*);";
    QString aFileName = QFileDialog::getOpenFileName(this, "选择文件", curPath, filter);  //返回带路径的完整文件名
    if(aFileName.isEmpty()) return;
    //发送文件
    thr->sendFile(aFileName);
    //
    ui->recetextBrowser->append("发送文件："+aFileName);

}
