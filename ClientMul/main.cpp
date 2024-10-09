#include "widget.h"

#include <QApplication>


QString loadQss(){
    QFile file(":/style.qss");
    // 打开文件
    file.open(QFile::ReadOnly);
    // 读取文件内容，虽然 readAll 返回的是 QByteArray, 但是 QString 提供了QByteArray 版本的构造函数
    QString style = file.readAll();
    // 关闭文件
    file.close();
    return style;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(loadQss());
    Widget w;
    w.setWindowTitle("客户机");
    w.show();
    return a.exec();
}
