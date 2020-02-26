#include "mainwidget.h"
#include <QPushButton>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);
    b1.setText("^v^");
    b1.move(250,250);

    b2 = new QPushButton(this);
    b2->setText("haha");
    //按钮如果需要有反应 必须借助信号槽，是QT的核心

    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);
    /*
     *&b1: 信号发出者
     *&QPushButton::pressed 处理的信号
     *this: 信号接收者
     *&MainWidget::close: 槽函数，信号处理函数 接收的类名::槽函数
    */

    /* 自定义槽， 普通函数用法
     * Qt5：任意的成员函数，可以是普通全局函数，可以是静态函数
     * 槽函数需要和信号一致（参数、返回值）
     * 由于信号没有返回值， 所以槽函数也一定没有返回值
    */
    connect(b2, &QPushButton::released, this, &MainWidget::myslot);
    connect(b2, &QPushButton::released, &b1, &QPushButton::hide);

    /*
     * 信号：短信
     * 槽函数：接收短信的手机
    */

    setWindowTitle("boss");
    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.setGeometry(200,200,50,50);

    //w.show();
    resize(500,500);

    connect(&b3, &QPushButton::released, this, &MainWidget::changewindow);

    //此时mysignal重载

    void (SubWidget::*funsignal)() = &SubWidget::mysignal;
    connect(&w, funsignal, this, &MainWidget::dealwhithsubsignal);

    void (SubWidget::*withsignal)(int, QString) = &SubWidget::mysignal;
    connect(&w, withsignal, this, &MainWidget::dealsignal);

    //lambda表达式， 匿名函数对象
    //C++11新增加的特性
    //Qt配合信号一起使用非常方便

    b4 = new QPushButton(this);
    b4->setText("lambdasignal");
    b4->move(100,100);
    int a = 5, b = 10;

    // 里面当为“=” 默认为只读的 ， 如果想要修改传入参数的值需要加入关键字 mutable， 默认用=， 比较安全
    // this 指针: 类中所有成员以值传递方式
    // & ：外部所有局部变量 在这里一般不用以为在操作着 内存没有释放
    //connect(b4, &QPushButton::released, this, [=]() mutable {qDebug()<<"1111111"<<endl; b4->setText("lambdachanged"); a = 50; qDebug()<<a<<b<<endl; });

    //当有信号有参数时， 信号clicked(bool ischeck) 默认ischheck = false;
    connect(b4, &QPushButton::clicked, this, [=](bool ischeck) mutable {b4->setText("lambdachanged"); qDebug()<<ischeck<<endl; });
    //此时 signal中clicked的参数ischeck=false 传给槽函数参数 打印出来为false;


    //Qt4信号连接
    //Qt4槽函数必须有slots：关键字修饰
    //编译不报错，但是结果会不正确

    /*
    connect(&w, SIGNAL(mysignal()), this, SLOT(dealwhithsubsignal()));
    connect(&w, SIGNAL(mysignal(int, QString)), this, SLOT(dealsignal(int, QString)));
    */

}

MainWidget::~MainWidget()
{
}

void MainWidget::myslot(){
    b2->setText("ha ge chuizi");
}

void MainWidget::changewindow(){
    //子窗口显示本窗口隐藏；
    w.show();
    this->hide();
}

void MainWidget::dealwhithsubsignal(){
    this->show();
    w.hide();
}

void MainWidget::dealsignal(int a, QString str){

    //先转换成字节数组， toUtf8() QString->QByteArray
    //然后再转化成char*  .data()  QByteArray->char*
    qDebug()<< a <<str.toUtf8().data();
}


