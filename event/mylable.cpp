#include "mylable.h"
#include <QMouseEvent>
#include <QDebug>

mylable::mylable(QWidget *parent) : QLabel(parent)
{
    //默认追踪鼠标
    this->setMouseTracking(true);
}


void mylable::mousePressEvent(QMouseEvent *ev){
    int i = ev->x();
    int j = ev->y();

    //一般c语言输出string sprinf
    /*
     * QString str = QString("I'm %1, I'm %2 years old!").arg("zpc").arg(24);
     * I'm zpc, I'm 24 years old!
    */
    QString str = QString("<center><h2>The mouse pos:(%1, %2)</h2></center>").arg(i).arg(j);
    this->setText(str);

    if(ev->button()==Qt::LeftButton){
        qDebug()<<"left";
    }
    else if(ev->button()==Qt::RightButton){
        qDebug()<<"right";
    }
    else if(ev->button()==Qt::MidButton){
        qDebug()<<"middle";
    }
}

void mylable::mouseReleaseEvent(QMouseEvent *ev){
    this->setText(QString("<center><h2>The mouse release pos:(%1, %2)</h2></center>").arg(ev->x()).arg(ev->y()));
}
void mylable::mouseMoveEvent(QMouseEvent *ev){
    this->setText(QString("<center><h2>The mouse pos:(%1, %2)</h2></center>").arg(ev->x()).arg(ev->y()));
}

void mylable::leaveEvent(QEvent *){
    this->setText(QString("<center><h2>The mouse leaved</h2></center>"));
}

void mylable::enterEvent(QEvent *){
    this->setText(QString("<center><h2>The mouse rntered</h2></center>"));
}
