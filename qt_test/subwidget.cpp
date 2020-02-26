#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("I'm bro");

    b.setParent(this);
    b.setText("返回");
    resize(500,500);

    connect(&b, &QPushButton::clicked, this, &SubWidget::sendSlot);
    //按钮只是执行槽函数， 槽函数调用回调函数 发信号， 所以信号事子窗口发的
}

void SubWidget::sendSlot(){
    emit mysignal();
    emit mysignal(250, "I'm sub"); //信号属于谁，则是谁发的信号
}
