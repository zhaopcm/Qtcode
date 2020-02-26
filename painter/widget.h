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

private:
    Ui::Widget *ui;
    //定义一个初始坐标，便于图片刷新观察
    int x;
protected:
    //重写绘图事件
    //如果在窗口绘图，必须放在绘图事件里实现
    //绘图事件重新调用，当窗口需要重绘的时候
    void paintEvent(QPaintEvent *e);
private slots:
    void on_pushButton_clicked();
};
#endif // WIDGET_H
