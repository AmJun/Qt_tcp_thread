#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_serverBtn_clicked()
{
    bool ok = myPro.startDetached("../TransportTools/Server/ServerMul.exe");
    if(!ok){
        myPro.startDetached("./Server/ServerMul.exe");
    }
    exit(0);
}

void Widget::on_clientBtn_clicked()
{
    bool ok = myPro.startDetached("../TransportTools/Client.e/ClientMul.exe");
    if(!ok){
        myPro.startDetached("./Client.e/ClientMul.exe");
    }
    exit(0);
//    QString currPath = QDir::currentPath();

//    qDebug()<<currPath;
//    QFile file("../");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        return;
//    }
}
