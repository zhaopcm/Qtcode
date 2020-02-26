#include "mybutton.h"
#include <QDebug>
mybutton::mybutton(QWidget *parent) : QPushButton(parent)
{

}

void mybutton::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        qDebug()<<"左键被按下";
        event->ignore();
        //ignore()函数是把信号传个父组件而不是父类
    }
    //在这里必须把事件传回到Qpushbutton基类，那么connect的事件才会发生，不然信号就会被忽略
    //不会触发clicked信号所以前面不打印
    else{
        QPushButton::mousePressEvent(event);
    }
    //一般改写事件接受时，注意把信号继续往下传递
    //QPushButton::mousePressEvent(event);
}
