#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //去边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(0, 0, 500,500,QPixmap("../image/fu.png"));


}

void Widget::mouseMoveEvent(QMouseEvent *event){
    //已经得到相对与窗口的点击坐标，按压移动窗口
    if(event->buttons() & Qt::LeftButton){
        move(event->globalPos()-p);
    }
}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        close();
    }
    else if(event->button() == Qt::LeftButton){
        //计算窗口坐标差值
        //当前整个屏幕坐标减去窗口左上角坐标，得到鼠标点击相对屏幕坐标
        p = event->globalPos() - this->frameGeometry().topLeft();
    }
}
