#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("服务端");
    resize(500,500);

    //如果创建指针，必须动态分配内存空间
    //再构造函数中继承父对象，在父对象内存空间被回收的时候也可以自动被回收
    tcpserver = new QTcpServer(this);
    tcpserver->listen(QHostAddress::Any, 8888);

    //如果成功建立tcpsever会触发newConnertion的信号，否则阻塞在这里
    connect(tcpserver, &QTcpServer::newConnection, [=](){
        //取出及建立成功的通信套接字
        tcpsocket = tcpserver->nextPendingConnection();
        QString add = tcpsocket->peerAddress().toString();
        quint16 port = tcpsocket->peerPort();
        QString his = QString("[%1, %2]建立连接成功").arg(add).arg(port);
        ui->history->setText(his);
        //接收函数必须写在这里因为tcpsocket在函数在connect后会被初始化
        //当对方有数据成功发送过来，会触发readyread(), 实际表示再次阻塞在数据转化完成等待接受
        connect(tcpsocket, &QTcpSocket::readyRead,
        [=](){
            QString info = tcpsocket->readAll().toStdString().data();
            info = showtime(info);
            ui->history->append(info);
        });
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_sendbutton_clicked()
{
    if(tcpsocket==NULL) return;
    QString str = ui->edit->toPlainText();
    tcpsocket->write(str.toUtf8().data());
    str = showtime(str);
    ui->history->append(str);
    ui->edit->clear();
}

void Widget::on_exitbutton_clicked()
{
    if(tcpsocket==NULL) return;
    //主动断开连接
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    //清空窗口
    ui->history->clear();
}

QString Widget::showtime(QString show_info){
    //创建时间显示
    QDateTime time = QDateTime::currentDateTime();
    QString data_time = time.toString("yyyy.MM.dd hh:mm:ss");
    QString info = QString("%1 : %2").arg(data_time).arg(show_info);
    return  info;
}
