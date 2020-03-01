#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpsocket = new QTcpSocket(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonconnect_clicked()
{
    QHostAddress addr = QHostAddress(ui->lineEditIP->text());
    quint16 port = ui->lineEditport->text().toUInt();
    tcpsocket->connectToHost(addr, port);
    if(tcpsocket == NULL){
        ui->textEdit->setText("服务器连接失败");
    }
    else{
        connect(tcpsocket, &QTcpSocket::readyRead, this, &Widget::dealwithsig);
    }
}

void Widget::dealwithsig(){
    //ui->textEdit->setText("文件开始传输");
    QByteArray buf = tcpsocket->readAll();
    if(isstart == true){
        isstart = false;
        //初始化文件操作
        fileName = QString(buf).section("##", 0, 0);
        fileSize = QString(buf).section("##", 1, 1).toInt();
        ui->textEdit->append(QString("开始接收%1, 文件大小%2").arg(fileName).arg(fileSize));
        recvSize = 0;

        //打开文件
        file.setFileName(fileName);
        bool isok = file.open(QIODevice::WriteOnly);
        if(!isok){
            qDebug()<<"文件打开失败";
        }
    }
    else{
        qint64 len;
        len = file.write(buf);
        recvSize += len;
        qDebug()<<recvSize;
        qDebug()<<fileSize;
        qDebug()<<int(recvSize/fileSize);
        //ui->progressBar->setValue(int(recvSize/fileSize));
        if(recvSize == fileSize){
            QMessageBox::information(this, "提示", "文件传输已完成");
            ui->textEdit->append(QString("文件%1传输已完成").arg(fileName));
            file.close();
            tcpsocket->disconnectFromHost();
            isstart = true;
            fileSize = 0;
            fileName.clear();
        }
    }
}
