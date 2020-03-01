#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    void threadpaint();

private:
signals:
    void updateimage(QImage);
};

#endif // MYTHREAD_H
