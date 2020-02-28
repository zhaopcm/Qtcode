#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

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
    void on_pushButtonsend_clicked();

    void on_pushButtonclose_clicked();

    void dealmsg();

private:
    Ui::Widget *ui;
    QUdpSocket *udpsocket = NULL;
};
#endif // WIDGET_H
