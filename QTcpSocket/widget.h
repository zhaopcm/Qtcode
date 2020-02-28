#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString showtime(QString show_info);

private slots:
    void on_sendbutton_clicked();

    void on_exitbutton_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *tcpserver = NULL;    //监听套接字
    QTcpSocket *tcpsocket = NULL;   //通信套接字
};
#endif // WIDGET_H
