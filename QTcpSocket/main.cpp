#include "widget.h"
#include "tcpclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    tcpclient w2;
    w2.show();


    return a.exec();
}
