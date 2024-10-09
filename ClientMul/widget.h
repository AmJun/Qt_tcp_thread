#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "sendthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_bindServerBtn_clicked();

    void on_disconnectBtn_clicked();

    void on_sendBtn_clicked();

    void on_sendFileBtn_clicked();

private:
    QString myName;
    Ui::Widget *ui;
    QTcpSocket* m_socket;
    SendThread* thr;
};
#endif // WIDGET_H
