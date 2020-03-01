#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    //在4.7之前的版本线程处理函数必须重载run，现在更加灵活但也只能定义一个处理函数
    void mycomplexfun();
    void dealwithstart();
    void stop();

private:
    bool istart = true;

signals:
    void mysignal();

};

#endif // MYTHREAD_H
