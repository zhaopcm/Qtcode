#ifndef MYLABLE_H
#define MYLABLE_H

#include <QLabel>

class mylable : public QLabel
{
    Q_OBJECT
public:
    explicit mylable(QWidget *parent = nullptr);
protected:

    //自定义类重载事件函数，使实现额外功能
    //返回值类型和函数参数都不能修改
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    //进入窗口区域
    void enterEvent(QEvent *) override;
    //离开窗口区域
    void leaveEvent(QEvent *) override;
signals:

};

#endif // MYLABLE_H
