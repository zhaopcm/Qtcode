#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>
//以二进制操纵文件

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_read_button_clicked()
{
    //打开文件对话框取文件
    QString path = QFileDialog::getOpenFileName(this, "打开", "../txt/",
                tr("Text files (*.txt)"));

    //判断路径是否存在
    if(path.isEmpty()==false){
        //创建文件对象
        QFile file(path);

#if 0
        if(file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            QString array = in.readAll();
            ui->textEdit->setText(array);
        }
#endif
        //readline 不知道为啥不行
        if(file.open(QIODevice::ReadOnly)==true){
            QTextStream in(&file);
            QString line;
            while(!in.atEnd()){
                line += in.readLine()+"\n";
            }
            ui->textEdit->setText(line);

        }

        /*
        if(path.isEmpty()==false){
            bool isOK = file.open(QIODevice::ReadOnly);
            QByteArray line;
            if(isOK == true){
                while(!file.atEnd()){
                    line += file.readLine();
                }
                ui->textEdit->setText(line);
            }

            file.close();
        }
        */

    }
    //获取文件信息
    QFileInfo info(path);
    qDebug()<<"文件名"<<info.fileName()<<endl;
    qDebug()<<"文件长度"<<info.size()<<endl;
    qDebug()<<"文件后缀"<<info.suffix()<<endl;
    qDebug()<<"文件创建时间："<<info.created().toString("yyyy-MM-dd hh:mm:ss");

}

void Widget::on_write_button_clicked()
{
    //保存成文件
    QString path = QFileDialog::getSaveFileName(this, "保存到", "../txt/",tr("Text files(*.txt)"));

    if(!path.isEmpty()){
        QFile file(path);
        if(file.open(QIODevice::ReadWrite)==true){
            QTextStream in(&file);
            QString buffer = in.readAll();
            if(buffer.isEmpty()){
                buffer += ui->textEdit->toPlainText();
                //file.write(buffer.toUtf8());
                file.write(buffer.toLocal8Bit());
            }
            else{
                QString line;
                while(!in.atEnd()){
                    line += in.readLine() + "\n";
                }
                line += "\n";
                line += ui->textEdit->toPlainText();
                file.write(line.toLocal8Bit());
            }
        }
        file.close();
    }
}
