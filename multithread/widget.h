#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include<mythread.h>

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

    void on_buttonstop_clicked();

    void dealtimesig();

    void dealwithisdone();

private:
    Ui::Widget *ui;
    QTimer *timer;
    int time = 0;

    MyThread *mythread;
};
#endif // WIDGET_H
