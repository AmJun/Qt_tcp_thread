#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QTcpServer>
#include "chatui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //
    void init();
    bool isWidgetInStackedWidget(QWidget *widgetToCheck);
    ~MainWindow();

private slots:
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    //
    void on_startserverBtn_clicked();
    //
    void updataClientName(QString name,unsigned int id);
    //
    void timEvent();
    void discon(unsigned int id);

private:
    Ui::MainWindow *ui;
    //
    QTimer* updateTimer;
    QTcpServer* m_s;
    //“客户端”与“聊天界面”的关联
    QMap<QListWidgetItem *,chatUI*> item;
    //
    unsigned int clientHistoryNumber=0;
};
#endif // MAINWINDOW_H
