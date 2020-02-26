#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void myslot();

    void changewindow();

    void dealwhithsubsignal();

    void dealsignal(int, QString);

private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;
    QPushButton *b4;
    SubWidget w;
};
#endif // MAINWIDGET_H
