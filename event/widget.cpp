#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer_ID = this->startTimer(1000, Qt::VeryCoarseTimer);
    //mybutton的mousepress事件被重写，如果不把事件传回来此是没有信号的
    connect(ui->pushButton, &mybutton::clicked, [=](){qDebug()<<"+++++";});
    ui->clabel->installEventFilter(this);
    ui->clabel->setMouseTracking(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){
    qDebug()<<(char)event->key();

    if(event->key()== Qt::Key_A){
        qDebug()<<"按下了A";
    }
}

void Widget::timerEvent(QTimerEvent *event){
    static int sec = 0;
    ui->label->setText(QString("<center><h2>time is %1</h2></center>").arg(sec++));
    if(sec==5) killTimer(timer_ID);
}

void Widget::closeEvent(QCloseEvent *event){
    int ret = QMessageBox::question(this, "提示", "是否关闭窗口？");
    //如果不设置属性qtbox 默认为yes和no
    if(ret == QMessageBox::Yes){
        event->accept();
    }
    else{
        event->ignore();
        //信号传递给父组件
        qDebug()<<"已取消关闭";
    }
}

bool Widget::event(QEvent *e){
    //正常情况下，事件分发是枚举类型
    //switch (e->type()) {
      //  case QEvent::MouseMove :
        //此处e需要做强制类型转化转换成符合的类型
        //    QMouseEvent *ev = static_cast<QMouseEvent *>(e);
            //mouseMoveEvent(ev);
        //break;
        //case QEvent::MouseButtonPress :
          //  QMouseEvent *ev = static_cast<QMouseEvent *>(e);
            //mousePressEvent(ev);
        //break;
        /*
         *
         * case..
        */
    //}

    //正常情况下如果想要忽略时间时间
    if(e->type()==QEvent::Timer){
        //qDebug()<<"时间计时器已被忽略";
        //QTimerEvent *ev = static_cast<QTimerEvent *>(e);
        //timerEvent(ev);
        return true;
    }
    //对键盘信号进行处理
    else if(e->type()==QEvent::KeyPress){
        //只对B按键处理其他忽略,可以在WIDGET层再做一次过滤
        QKeyEvent *ev = (QKeyEvent *)e;
        if(ev->key()==Qt::Key_B){
            return QWidget::event(e);
        }
        return true;
    }
    else{
        //必须把信号传回给基类的时间分发器
        return QWidget::event(e);
        //可以发现return falsed后label中定义的事件函数功能被取消
        //为确保正常使用不要轻易return false;
        //return false;
    }
}

bool Widget::eventFilter(QObject *object, QEvent *event){
    if(object == ui->clabel){
        QMouseEvent *e = (QMouseEvent *)event;
        if(event->type()==QEvent::MouseMove){
            ui->clabel->setText(QString("<center><h2>THE POS:(%1, %2)</h2><center>").arg(e->x()).arg(e->y()));
        }
        else if(event->type()==QEvent::MouseButtonPress){
            ui->clabel->setText(QString("<center><h2>PRESSED POS:(%1, %2)</he><center>").arg(e->x()).arg(e->y()));
        }
    }
    return QWidget::eventFilter(object, event);
}
