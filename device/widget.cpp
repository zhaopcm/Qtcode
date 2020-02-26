#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*
    QPixmap pixmap(400,300);
    QPainter p(&pixmap);

    //画图设备定义了
    p.drawPixmap(0, 0, width(), height(), QPixmap("../image/timg.jpg"));

    //画图完成，但是没法显示，因此需要保存成一张图片

    pixmap.save("../image/bk.png");
    */

    /*
    //创建Qimage设备， Qimage可以指定图片通道，以透明传入具体看函数
    QImage image(QSize(400,300),QImage::Format_RGB32);
    QPainter p(&image);

    p.drawImage(QPoint(0,0), QImage("../image/snow.jpg"));
    //image 可以对像素点进行操作
    for(int i=0; i<50; i++){
        for(int j=0; j<50; j++){
            image.setPixel(i, j, qRgb(105,105,105));
        }
    }

    image.save("../image/snow1.png");
    */

    //设备为Qpicture
    /*
    QPicture pic;
    QPainter p;
    p.begin(&pic);
    p.drawPixmap(0,0,100,100,QPixmap("../image/snow.jpg"));
    p.end();
    pic.save("../image/snow2.png");
    */

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){

    /*
    QPicture pi;
    pi.load("../image/snow2.png");

    QPainter p(this);
    p.drawPicture(QPoint(100,100),pi);
    */


    QPixmap pix;
    pix.load("../image/timg.jpg");
    QPainter p(this);
    QImage im = pix.toImage();
    p.drawImage(0,0,im);

    QImage im2 = im;
    QPixmap pix2 = QPixmap::fromImage(im2);
    p.drawPixmap(100,0,pix2);

}
