#include "chatui.h"
#include "ui_chatui.h"
#include "chatworker.h"

chatUI::chatUI(QTcpSocket* socket,unsigned int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatUI)
{
    ui->setupUi(this);
    ID = id;
    //构建线程对象
    worker = new chatworker(socket);
    worker->start();

    //连接信号与槽
    connect(worker,&chatworker::nameSignal,this,&chatUI::updateName);
    connect(worker,&chatworker::chatSignal,this,&chatUI::updateChat);
    connect(worker,&chatworker::fileSignal,this,&chatUI::updateFile);
    connect(worker,&chatworker::fileStartSignal,this,&chatUI::startFile);
    connect(worker,&chatworker::end,this,&chatUI::endUI);
}
//客户端名称
void chatUI::updateName(QString clientName)
{
    //携带ID发送
    emit nameSignals(clientName,ID);
    //
    Cname = clientName;
}
//聊天信息
void chatUI::updateChat(QString chatTxt)
{
    //
    ui->textBrowser->append(Cname+":"+chatTxt);
    //
}
//
void chatUI::updateFile()
{
    ui->textBrowser->append("下载完成");
}
//
void chatUI::startFile(QString filename)
{

    ui->textBrowser->append("开始下载："+filename);
}
//告诉主线程该ID类死亡
void chatUI::endUI()
{
    emit endSignal(ID);
}

void chatUI::setId(unsigned int id)
{
    ID = id;
}

unsigned int chatUI::getId()
{
    return ID;
}

chatUI::~chatUI()
{
    //关闭线程对象
    worker->stopThread();
    worker->quit();
    delete ui;
}
//向客户端发送文本
void chatUI::on_sendBtn_clicked()
{
     QString data = ui->sendBox->toPlainText();
     //交给工作线程
     worker->writeData(data);
     //
     ui->textBrowser->append("我："+data);
}
