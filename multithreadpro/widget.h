#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <mythread.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_buttonstart_clicked();

    void dealwithtime();
    void on_buttonstop_clicked();

signals:
    void threadisstart();
    void tostop();

private:
    Ui::Widget *ui;
    int time = 0;
    QThread *thread;
    MyThread *mythread;
};
#endif // WIDGET_H
