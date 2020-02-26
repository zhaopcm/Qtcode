#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QBitmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //x的起始坐标为0；
    x = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e){
    //widget也是一个画图设备
    QPainter p(this);
    //设置当前窗口背景
    //p.drawPixmap(0, 0, width(), height(), QPixmap("../image/timg.jpg"));
    p.drawPixmap(rect(), QPixmap("../image/timg.jpg"));

    //定义画笔
    QPen pen;
    pen.setWidth(5);//定义画笔宽度
    //设置颜色pen.setColor(Qt::red);
    pen.setColor(QColor(105,105,105)); //RGB设置颜色
    pen.setStyle(Qt::SolidLine);
    //把画笔给画家
    p.setPen(pen);

    QBrush brush; //设定画刷
    brush.setColor(Qt::darkRed);
    //brush.setStyle(Qt::Dense3Pattern);
    p.setBrush(brush);

    //p.drawLine(50,50,150,50);
    //p.drawLine(50,50,50,150);

    //画矩形
    p.drawRect(50,50,width()-100,height()-100);

    //p.drawEllipse(QPoint(150,150),100,100); //画原型

    //画雪花
    //p.drawPixmap(x,200,50,50,QPixmap("../image/snow.jpg"));
    p.drawPixmap(x,200,50,50,QBitmap("../image/snow.jpg"));
    //bitmap显示的是黑白图只有两个像素点


    //画图设备还有
    //QImage: 和平台无关，可以对图片进行修改，在线程中绘图（比如导航）
    //QPicture: 保存绘图的状态，存成2进制文件
    //QPixmap: 它针对屏幕有过优化，（通常使用）和平台相关，不能对图片进行修改

}

void Widget::on_pushButton_clicked()
{
    x += 50;
    if(x > width()) x = 0;

    //窗口刷新，让窗口重绘
    update();  //间接调用paintEvent()
}
