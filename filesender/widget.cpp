#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <QFile>

#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化界面在连接未建立前两个按钮都是不能按得
    ui->buttonsend->setEnabled(false);
    ui->buttonchose->setEnabled(false);

    //设置定时器防止黏包
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        //关闭定时器
        timer->stop();
        sendfile();
    });

    //给监听套接字初始化内存空间
    tcpserver = new QTcpServer(this);

    //监听所有地址，设置服务器端口为8888
    tcpserver->listen(QHostAddress::Any, 8888);
    connect(tcpserver, &QTcpServer::newConnection, [=](){
        tcpsocket = tcpserver->nextPendingConnection();  //取出通信套接字
        QString addr = QString(tcpsocket->peerAddress().toString());
        quint16 port = tcpsocket->peerPort();
        ui->textEdit->setText(QString("[%1, %2]:成功接入服务器").arg(addr).arg(port));

        //一旦成功接入服务器再次设定按钮状态，选择文件按钮有效
        ui->buttonchose->setEnabled(true);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonchose_clicked()
{
    //初始化
    fileName.clear();
    fileSize = 0;
    sendSize = 0;
    //打开文件对话框
    path = QFileDialog::getOpenFileName(this, "打开", "../", "Any files (*)");
    //判断路径是否有效
    if(!path.isEmpty()){
        file.setFileName(path);
        QFileInfo info(path);
        //如果文件能够成功打开
        if(file.open(QIODevice::ReadOnly)){
            fileName = info.fileName();
            fileSize = info.size();
            cout<<QString("[name:%1, length:%2]:文件打开成功");
            ui->textEdit->append(QString("<center><h2>[name:%1, length:%2]:准备传输</h2></center>").arg(fileName).arg(fileSize));

            //让发送文件按键有效
            ui->buttonsend->setEnabled(true);
        }
    }
    else{
        cout << "打开文件无效";
    }
}

void Widget::on_buttonsend_clicked()
{
    //只有有客户端连接并且，选中文件才能点击send按键

    //发送文件信息，因为对方要知道文件信息重新创建文件
    //组包格式为文件名：文件大小

    //但是为了防止黏包在文件信息包后必须设置一个延时
    qint16 infolen = 0;
    QString info = QString("%1##%2").arg(fileName).arg(fileSize);
    infolen = tcpsocket->write(info.toUtf8());
    if(infolen>0){
        timer->start(20);
        cout<<"计时器已经工作";
    }
    else{
        cout<<"头部信息发送失败 91";
        ui->buttonsend->setEnabled(false);
    }

}

void Widget::sendfile(){
    //发送文件
    //file.setFileName(path);
    qint64 len;
    do{
        char buf[4*1024] = {0};
        len = 0;
        len = file.read(buf, sizeof(buf));
        tcpsocket->write(buf, len);
        sendSize += len;
    }while(len>0);
    if(sendSize == fileSize) {
        ui->textEdit->append("文件发送成功");
        cout<<sendSize;
    }
    file.close();
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
}
