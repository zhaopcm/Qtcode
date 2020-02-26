#include "mybutton.h"
#include <QDebug>
#include <QPushButton>

mybutton::mybutton(QWidget *parent) : QPushButton(parent)
//通过构造函数给基类传参
{

}

mybutton::~mybutton(){
    qDebug()<<"对象已经被析构"<<endl;
}
