#include "mainwidget.h"
#include "mybutton.h"
#include <QPushButton>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //主窗口的坐标系统对应于屏幕(0,0) 表示屏幕左上角
   move(300, 300);
   resize(500,500);
   //当程序结束，如果指定父对象，如果是动态分配空间，在程序结束时，内存会自动释放
   QPushButton *b1 = new QPushButton(this);
   b1->setText("^v^");
   b1->move(100,100);
   b1->resize(200,100);

   QPushButton *b2 = new QPushButton(b1);
   b2->setText("@_@");
   b2->move(10,10);

   mybutton *b3 = new mybutton(this);
   b3->setText("hah");
   //按钮被析构，1，指定父对象后 2，直接或间接继承于QObjet
   //子对象如果是动态分配空间的我们不需要手动delete,系统会自动释放
}

MainWidget::~MainWidget()
{
}

