#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置无边框属性
    setWindowFlag(Qt::FramelessWindowHint);

    //背景透明
    //setAttribute(Qt::WA_TranslucentBackground);

    //不能指定父对象
    mythread = new MyThread;

    //定义Qthread对象，使用多线程函数
    //指定父对象便于回收
    thread = new QThread(this);

    //将mythread递交给thread从而完成多线程启动和调用
    mythread->moveToThread(thread);

    thread->start();
    connect(this, &Widget::changeimage, mythread, &MyThread::threadpaint);
    connect(mythread, &MyThread::updateimage, this, &Widget::dealwithimage);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        emit changeimage();
    }
    else if(event->button() == Qt::RightButton){
        int ret = QMessageBox::question(this, "提示", "<center><h2>是否关闭？</h2></center>");
        switch (ret) {
        case QMessageBox::Yes :
            thread->quit();
            thread->wait();
            delete  mythread;
            close();
            break;
        case QMessageBox::No :
            break;
        default:
            break;
        }

    }
}

void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 0, image);
    image = QImage(500,500, QImage::QImage::Format_RGB32);
}

void Widget::dealwithimage(QImage getimage){
    image = getimage;
    update();
}
