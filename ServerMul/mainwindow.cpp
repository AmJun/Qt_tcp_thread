#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatui.h"
#include <QMap>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    //服务器对象
    m_s = new QTcpServer(this);
    //
    //客户端连接时
    connect(m_s,&QTcpServer::newConnection,this,[=](){
                //返回下一个等待处理的scoket
                QTcpSocket *clientSocket = m_s->nextPendingConnection();
                //处理该socket
                QListWidgetItem* user = new QListWidgetItem();
                chatUI* window = new chatUI(clientSocket,clientHistoryNumber);
                //接收客户端名称的槽
                connect(window,&chatUI::nameSignals,this,&MainWindow::updataClientName);
                item.insert(user,window);
                clientHistoryNumber += 1;
                connect(window,&chatUI::endSignal,this,&MainWindow::discon);
            });
    //
    updateTimer = new QTimer();
    connect(updateTimer,&QTimer::timeout,this,&MainWindow::timEvent);
    updateTimer->start(20);

}

void MainWindow::init()
{
    ui->portLine_2->setText("8899");
}

bool MainWindow::isWidgetInStackedWidget(QWidget *widgetToCheck)
{
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
            QWidget *widgetInStack = ui->stackedWidget->widget(i);
            if (widgetInStack == widgetToCheck) {
                return true; // 找到了匹配的小部件
            }
        }
        return false; // 没有找到匹配的小部件
}

MainWindow::~MainWindow()
{
    delete ui;
}

//更新光标选中的用户页面
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //不在容器中
    if(!item.contains(current)){
        return;
    }
    chatUI* w = item.value(current);
    //新增的w添加到stack里
    if(!isWidgetInStackedWidget(w)){
        ui->stackedWidget->addWidget(w);
    }
    ui->stackedWidget->setCurrentWidget(w);
    ui->stackedWidget->show();
}
//开启服务器监听
void MainWindow::on_startserverBtn_clicked()
{
    unsigned int port = ui->portLine_2->text().toUInt();
    //监听本地主机的任何网卡
    m_s->listen(QHostAddress::Any,port);
    //
    ui->startserverBtn->setDisabled(true);
}

void MainWindow::updataClientName(QString name, unsigned int id)
{
    //
//    qDebug()<<"go21313......."<<name<<id;
    QListWidgetItem* target;
    //迭代器遍历
    for(const auto &window : item){
        if(window->getId() == id){
            target = item.key(window);
            target->setText(name);
            ui->listWidget->addItem(target);
        }
    }
    //

}
//定时器事件
void MainWindow::timEvent()
{
    if(!m_s->isListening()){
        return;
    }
    ui->clientOnlineNumberLable->setText("当前客户机在线数量："+QString::number(item.size()));
    //
    ui->listWidget->show();
}

void MainWindow::discon(unsigned int id)
{
    //获取当前断开连接的socket对象
//    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QListWidgetItem* target;
    //迭代器遍历
    for(const auto &window : item){
        if(window->getId() == id){

            target = item.key(window);
            //
            ui->stackedWidget->removeWidget(window);
            ui->listWidget->removeItemWidget(target);
            delete(target);
            item.remove(target);
        }
    }
//        //清除对象
//        clientSocket->deleteLater();

}
