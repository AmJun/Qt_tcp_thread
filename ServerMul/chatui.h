#ifndef CHATUI_H
#define CHATUI_H


#include <QWidget>
#include "chatworker.h"
#include <QTcpSocket>

namespace Ui {
class chatUI;
}

class chatUI : public QWidget
{
    Q_OBJECT

public:
    explicit chatUI(QTcpSocket* socket, unsigned int id,QWidget *parent = nullptr);
    void setId(unsigned int id);
    unsigned int getId();
    ~chatUI();

private slots:
    void on_sendBtn_clicked();
    void updateName(QString clientName);
    void updateChat(QString chatTxt);
    void updateFile();
    void startFile(QString filename);
    void endUI();

private:
    Ui::chatUI *ui;
    chatworker* worker;
    unsigned int ID;
    QString Cname;
signals:
    void nameSignals(QString name,unsigned int ID);
    void endSignal(unsigned int id);
};

#endif // CHATUI_H
