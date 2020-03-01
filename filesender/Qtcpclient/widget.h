#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_buttonconnect_clicked();
    void dealwithsig();

private:
    Ui::Widget *ui;

    QTcpSocket *tcpsocket = NULL;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;

    bool isstart = true;
};
#endif // WIDGET_H
