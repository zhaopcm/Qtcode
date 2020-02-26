#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QCloseEvent>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    //event()是事件分发函数， 所有事件都可以由event进行分发和忽略；
    //evetn()函数参数类型是bool
    bool event(QEvent *e) override;

    //事件过滤器
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Ui::Widget *ui;
    int timer_ID;
};
#endif // WIDGET_H
