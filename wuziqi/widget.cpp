#include "widget.h"
#include "ui_widget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QVector>
#include <QPair>

#define cout qDebug()<<"["<<__FILE__<<" : "<<__LINE__<<"]"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(1000,1000);
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), QPixmap("://image/spa.jpg"));
    QPen pen(Qt::darkRed, 3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(pen);

    int x = width()/20;
    int y = height()/20;

    for(int i= x; i<=width()-x; ){
        painter.drawLine(i, y, i, height()-y);
        i += x;
    }

    for(int i= y; i<=height()-y; ){
        painter.drawLine(x, i, width()-x, i);
        i += y;
    }
    for(int i=0; i<pieceblack.count(); i++){
        int tmpx = pieceblack[i].first*50+25;
        int tmpy = pieceblack[i].second*50+25;
        painter.drawPixmap(tmpx, tmpy, 50, 50, QPixmap(":/image/black.png"));
    }
    for(int i=0; i<piecewhite.count(); i++){
        int tmpx = piecewhite[i].first*50+25;
        int tmpy = piecewhite[i].second*50+25;
        painter.drawPixmap(tmpx, tmpy, 50, 50, QPixmap("://image/write.png"));
    }
    if(bwin||wwin){
        QMessageBox box;
        if(wwin) box.setText("<h3>白棋胜利!</h3>");
        if(bwin) box.setText("<h3>黑棋胜利!</h3>");
        box.setInformativeText("<center>是否重新开始游戏?</center>");

        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int ret = box.exec();
        switch (ret) {
        case QMessageBox::Yes:
            pieceblack.clear();
            piecewhite.clear();
            bwin = false;
            wwin = false;
            update();
            break;
        case QMessageBox::No:
            close();
            break;
        default:
            break;
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        QMessageBox msgbox;
        msgbox.setWindowTitle("五子棋");
        msgbox.setInformativeText("<center><h3>是否退出游戏?</h3></center>");
        msgbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int ret = msgbox.exec();
        switch (ret) {
            case QMessageBox::Yes:
                close();
            break;
            case QMessageBox::No:
            break;
            default:
            break;
        }
    }
    else if(event->button()==Qt::LeftButton){
        thx = piecex/50;
        thy = piecey/50;
        QPair<int, int>pair(thx, thy);
        isblack = borw(pieceblack.count(), piecewhite.count());
        cout<<isblack<<"x:"<<piecex<<"y:"<<piecey;
        cout<<isblack<<pair.first<<" "<<pair.second;
        //判断条件右键触发点应该有容错//
        //所以用除所得整数作为索引值
        if(!pieceblack.contains(pair)&&!piecewhite.contains(pair)){
            if(isblack==true){
                pieceblack.push_back(pair);
                bwin = win(pieceblack, thx, thy);
            }
            else if(isblack==false){
                piecewhite.push_back(pair);
                wwin = win(piecewhite, thx, thy);
            }
        }
        update();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event){
    piecex = event->x()-25;
    piecey = event->y()-25;
    //始终返回棋子中心点的坐标
}

bool Widget::borw(int numb, int numw){
    if(numb>numw) return false;
    return true;
}

//判断五子棋是否赢就当是刷题
bool Widget::win(QVector<QPair<int, int> > &piece, int thx, int thy){
    int xlen = 1;
    maxlen(piece, xlen, thx, thy, 1);
    maxlen(piece, xlen, thx, thy, 2);
    int ylen = 1;
    maxlen(piece, ylen, thx, thy, 3);
    maxlen(piece, ylen, thx, thy, 4);
    int mlen = 1;
    maxlen(piece, mlen, thx, thy, 5);
    maxlen(piece, mlen, thx, thy, 6);
    int wlen = 1;
    maxlen(piece, wlen, thx, thy, 7);
    maxlen(piece, wlen, thx, thy, 8);

    if(xlen==5||ylen==5||mlen==5||wlen==5) return true;
    return false;
}

void Widget::maxlen(QVector<QPair<int, int> > &piece, int &len, int x, int y, int q){
    //右移
    if(q==1&&piece.contains(qMakePair(x+1, y))){
        len += 1;
        maxlen(piece, len, x+1, y, q);
    }
    //左移
    else if(q==2&&piece.contains(qMakePair(x-1, y))){
        len += 1;
        maxlen(piece, len, x-1, y, q);
    }
    //上移
    else if(q==3&&piece.contains(qMakePair(x, y+1))){
        len += 1;
        maxlen(piece, len, x, y+1, q);
    }
    //下移
    else if(q==4&&piece.contains(qMakePair(x, y-1))){
        len += 1;
        maxlen(piece, len, x, y-1, q);
    }
    //左上
    else if(q==5&&piece.contains(qMakePair(x-1, y-1))){
        len += 1;
        maxlen(piece, len, x-1, y-1, q);
    }
    //右下
    else if(q==6&&piece.contains(qMakePair(x+1, y+1))){
        len += 1;
        maxlen(piece, len, x+1, y+1, q);
    }
    //右上
    else if(q==7&&piece.contains(qMakePair(x+1, y-1))){
        len += 1;
        maxlen(piece, len, x+1, y-1, q);
    }
    //左下
    else if(q==8&&piece.contains(qMakePair(x-1, y+1))){
        len += 1;
        maxlen(piece, len, x-1, y+1, q);
    }
}



