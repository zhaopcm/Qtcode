#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run(){
    qDebug()<<QThread::currentThread();
    QThread::sleep(5);
    emit isDone();
}
