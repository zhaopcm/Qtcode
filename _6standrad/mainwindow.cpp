#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menubar = menuBar();
    setMenuBar(menubar);

    QMenu *menu = menubar->addMenu("对话框");

    QAction *p1 = menu->addAction("模态对话框");
    //弹出强制对话框
    connect(p1, &QAction::triggered, [=](){QDialog dlg; dlg.exec(); qDebug()<<"success";});
    //非模态对话框
    QAction *p2 = menu->addAction("非模态对话框");
    //当前方法不好，因为继承了父对象，在整个窗口结束前会一直占用内存
    //connect(p2, &QAction::triggered, [=](){QDialog *mm = new QDialog(this); mm->show()/*dlg.show();不阻塞*/; qDebug()<<"success";});
    //但是不指定父对象，就无法自动释放内存，还好本身有一个属性
    connect(p2, &QAction::triggered, [=](){QDialog *mm = new QDialog; mm->setAttribute(Qt::WA_DeleteOnClose); mm->show()/*dlg.show();不阻塞*/; qDebug()<<"success";});

    QAction *p3 = menu->addAction("关于对话框");
    connect(p3, &QAction::triggered, [=](){QMessageBox::about(this, "about", "关于Qt") ;qDebug()<<"success";});

    QAction *p4 = menu->addAction("问题对话框");
    //问题对话框其实具有枚举属性， 通过选择属性更改选项
    //connect(p4, &QAction::triggered, [=](){QMessageBox::question(this, "question", "Are you OK?"); qDebug()<<"success";});
    connect(p4, &QAction::triggered, [=](){int res = QMessageBox::question(this, "question", "Are you OK?", QMessageBox::Ok|QMessageBox::Cancel);
        switch (res) {
        case QMessageBox::Ok:
            qDebug()<<"I'm OK";
        break;
        case QMessageBox::Cancel:
            qDebug()<<"No, I'm NOT";
        break;
        default:
            break;
        }
    });

    QAction *p5 = menu->addAction("文件对话框");
    //打开文件路径
    //第四个表示过率属性， 留下能识别的文件
    connect(p5, &QAction::triggered, [=](){QString path = QFileDialog::getOpenFileName(this, "open", "../",
        "soure(*.cpp *.h);;Text(*.txt);; all(*.*)");
        qDebug()<<path;}
    );
}

MainWindow::~MainWindow()
{
}

