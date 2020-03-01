#include "widget.h"
#include "ui_widget.h"

#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::dealtimesig);
    mythread = new MyThread(this);
    connect(mythread, &MyThread::isDone, this, &Widget::dealwithisdone);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonstart_clicked()
{
    if(timer->isActive()==false){
        timer->start(1000);
    }
    qDebug()<<QThread::currentThread();
    //如果有一个很复杂处理过程需要耗时5秒
    //单线程
    //要想同时计时和做处理则需要多线程进行
    //QThread::sleep(5);
    mythread->start();

}


void Widget::on_buttonstop_clicked()
{
    timer->stop();
}

void Widget::dealtimesig(){
    time ++ ;

    ui->lcdNumber->display(time);
}

void Widget::dealwithisdone(){
    //软退出，等线程执行的程序执行完成之后再退出

    qDebug()<<"子线程执行完毕";
    mythread->quit();
    //回收线程
    mythread->wait();
    qDebug()<<"线程回收完毕";
}
