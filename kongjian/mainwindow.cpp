#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QCompleter>
#include <QStringList>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->botten1->setText("^v^");

    QString str = ui->lineEdit->text();
    qDebug()<<str;

    //设置内容
    ui->lineEdit->setText("请输入密码");

    //设置内容显示方位
    ui->lineEdit->setTextMargins(15,0,0,0);

    //设置内容显示方式
    ui->lineEdit->setEchoMode(QLineEdit::Normal);

    //设置模型，便于输入检测
    QStringList list;
    list << "I,m zpc" << "hello, word" << "Zpc is sb" << "Hehe";
    QCompleter *com = new QCompleter(list, this);
    com->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(com);

    ui->txtLable->setText("^v^");
    //设施图片
    ui->graphLable->setPixmap(QPixmap(":/prefix1/image.png"));
    //让图片自动适应大小
    ui->graphLable->setScaledContents(true);


    //创建动画,添加到资源文件
    QMovie *mygif = new QMovie(":/prefix1/mygif.gif");
    //添加动画
    ui->gifLable->setMovie(mygif);
    //启动动画
    mygif->start();
    ui->gifLable->setScaledContents(true);

    //创建url连接
    ui->urlLable->setText("<h3><a href=\"https://www.baidu.com\">百度一下</a></h3>");
    //允许打开连接时访问
    ui->urlLable->setOpenExternalLinks(true);

    //设置进度条
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(shownum());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_change_clicked()
{
    static int i = 0;
    ui->stackedWidget->setCurrentIndex(++i % 3);
}

int MainWindow::shownum(){
    this->progress = 50;
    return this->progress;
}
