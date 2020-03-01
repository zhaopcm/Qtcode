#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void sendfile();

private slots:
    void on_buttonchose_clicked();

    void on_buttonsend_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *tcpserver = NULL; //监听套接字
    QTcpSocket *tcpsocket = NULL;  //通信套接字

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;

    QTimer *timer;
    QString path;   //存储文件路径便于打开传输

};
#endif // WIDGET_H
