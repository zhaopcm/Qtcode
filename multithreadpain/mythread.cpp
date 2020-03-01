#include "mythread.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPoint>


MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::threadpaint(){

    //制定绘图对象
    QImage image(500,500, QImage::QImage::Format_RGB32);
    QPainter painter(&image);
    QPen pen;
    QBrush brush;
    pen.setColor(QColor(qRgb(105, 105, 105)));
    pen.setWidth(5);
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);

    //定义一个点的数组
    QPoint a[] = {
        QPoint(rand()%500, rand()%500),
        QPoint(rand()%500, rand()%500),
        QPoint(rand()%500, rand()%500),
        QPoint(rand()%500, rand()%500),
        QPoint(rand()%500, rand()%500),
    };

    painter.drawPolygon(a, 5);

    emit updateimage(image);

}
