#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QThread>
#include <QPaintEvent>
#include <QImage>
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

    void dealwithimage(QImage getimage);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Widget *ui;

    QThread *thread;
    MyThread *mythread;
    QImage image;

signals:
    void changeimage();
};
#endif // WIDGET_H
