#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //动态分配内存空间
    udpsocket = new QUdpSocket(this);

    //获取端口号和IP地址
    quint16 port = 8888;

    udpsocket->bind(QHostAddress::AnyIPv4,port);
    //如果是组播则需要定义D类地址
    udpsocket->joinMulticastGroup(QHostAddress("224.0.0.2"));

    //当链接成功并且有数据到来时需要会自动触发readyRead()
    connect(udpsocket, &QUdpSocket::readyRead, this, &Widget::dealmsg);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButtonsend_clicked()
{
    QString str = ui->textEdit->toPlainText();
    quint16 port = ui->lineEditport->text().toInt();
    QString ipaddr = ui->lineEditip->text();
    udpsocket->writeDatagram(str.toUtf8().data(), (qint64)sizeof(str), QHostAddress(ipaddr), port);
    ui->textEdit->clear();
}

void Widget::on_pushButtonclose_clicked()
{
    udpsocket->close();
}

void Widget::dealmsg(){
    char data[1024] = {0};
    QHostAddress cliaddr;  //对方IP
    quint16 port;     //对方端口
    udpsocket->readDatagram(data, sizeof (data), &cliaddr, &port);
    QString info = QString("[%1, %2]  %3").arg(cliaddr.toString()).arg(port).arg(data);
    ui->textEdit->append(info);
}
