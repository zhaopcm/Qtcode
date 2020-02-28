#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class tcpclient;
}

class tcpclient : public QWidget
{
    Q_OBJECT

public:
    explicit tcpclient(QWidget *parent = nullptr);
    ~tcpclient();

    QString showtime(QString show_info);

private slots:
    void on_button_connect_clicked();

    void on_button_exit_clicked();

    void on_button_send_clicked();

private:
    Ui::tcpclient *ui;
    QTcpSocket *tcp_client = NULL;
};

#endif // TCPCLIENT_H
