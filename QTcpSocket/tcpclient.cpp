#include "tcpclient.h"
#include "ui_tcpclient.h"

#include <QHostAddress>
#include <QDateTime>
#include <QDebug>

#define cout qDebug()

tcpclient::tcpclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcpclient)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    //动态分配内存空间
    tcp_client = new QTcpSocket(this);

    //一旦建立成功，通信套接字会触发connect信号
    connect(tcp_client, &QTcpSocket::connected,
    [=](){
        QString tmp = "已经成功和服务器建立连接";
        tmp = showtime(tmp);
        ui->history->setText(tmp);
    });

    connect(tcp_client,&QTcpSocket::readyRead,
    [=](){
        QString tmp = tcp_client->readAll().toStdString().data();
        tmp = showtime(tmp);
        ui->history->append(tmp);
    });
}

tcpclient::~tcpclient()
{
    delete ui;
}

void tcpclient::on_button_connect_clicked()
{
    QString serverip = ui->lineip->text();
    quint16 serverport = ui->lineport->text().toInt();

    //客户端主动和服务器建立连接
    tcp_client->connectToHost(QHostAddress(serverip), serverport);
    QString info = "服务器连接失败，请检查IP和端口号";
    info = showtime(info);
    if(tcp_client==NULL) ui->history->setText(info);
}

void tcpclient::on_button_exit_clicked()
{
    if(tcp_client==NULL) return;
    tcp_client->disconnectFromHost();
    tcp_client->close();
    tcp_client = NULL;
    ui->history->clear();
}

void tcpclient::on_button_send_clicked()
{
    if(tcp_client==NULL) return;
    QString str = ui->edit->toPlainText();
    tcp_client->write(str.toUtf8());
    str = showtime(str);
    ui->history->append(str);
    ui->edit->clear();
}

QString tcpclient::showtime(QString show_info){
    //创建时间显示
    QDateTime time = QDateTime::currentDateTime();
    QString data_time = time.toString("yyyy.MM.dd hh:mm:ss");
    QString info = QString("%1 : %2").arg(data_time).arg(show_info);
    return  info;
}
