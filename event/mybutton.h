#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class mybutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mybutton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);

signals:

};

#endif // MYBUTTON_H
