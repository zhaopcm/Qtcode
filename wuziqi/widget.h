#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //根据棋子数量判断下一次该下的棋，如果是黑则返回正确否则为负
    bool borw(int numb, int numw);
    bool win(QVector<QPair<int,int>> &piece, int thx, int thy);
    void maxlen(QVector<QPair<int,int>> &piece, int &len, int x, int y, int q);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Widget *ui;
    int piecex;
    int piecey;
    int thx; //当前点在棋盘横向第几格
    int thy; //当前点在棋盘纵向第几格
    bool bwin = false;
    bool wwin = false;
    bool isblack;
    QVector<QPair<int,int>>pieceblack;
    QVector<QPair<int,int>>piecewhite;
};
#endif // WIDGET_H
