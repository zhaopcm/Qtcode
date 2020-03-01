#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //在这里自定义的线程类对象不能继承父对象
    mythread = new MyThread;

    //必须把自定义的线程对象加入到Qthread中实现多线程的功能
    thread = new QThread(this);
    //加入线程中，从而实现多线程
    mythread->moveToThread(thread);

    connect(mythread, &MyThread::mysignal, this, &Widget::dealwithtime);

    connect(this, &Widget::threadisstart, mythread, &MyThread::dealwithstart);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonstart_clicked()
{

    //遇到复杂处理过程需要耗时5秒
    //于是需要多线程处理，将过程交给另一个线程
    //启动线程函数开始计数
    //mythread 没有start 函数，通过thread实现功能
    thread->start();

    //但是线程启动并没有启动自定义的线程函数，需要通过connect信号-槽，启动线程函数
    //因为connect在多线程的时候时queue模式，线程号与接收者时相同的
    emit threadisstart();
}

void Widget::dealwithtime(){
    time ++;
    ui->lcdNumber->display(time);
    qDebug()<<QThread::currentThread();
}

void Widget::on_buttonstop_clicked()
{
    mythread->stop();
    thread->quit();
    thread->wait();
    //即使这样线程也依然在进行。
    //线程函数是一个死循环，因此需要用到标志位
    //一个线程类只有一个函数因此不能再继续connect
}
