#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::mycomplexfun(){
    //在这边计时每隔1秒给对方发一个信号触发timeout
    //通过标志位控制线程结束
    while(istart){
        QThread::sleep(1);
        emit mysignal();
        qDebug()<<QThread::currentThread();
        if(istart == false) break;
    }
}


void MyThread::dealwithstart(){
    istart = true;
    mycomplexfun();
}


void MyThread::stop(){
    istart = false;
}
