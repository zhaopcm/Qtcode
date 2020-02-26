#include "mainwindow.h"

#include <QMenuBar>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel> //主要用来记录文字
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *mBar = menuBar();
        //添加菜单
    QMenu *pFile = mBar->addMenu("文件");
        //添加菜单项
    QAction *pNew = pFile->addAction("新建");
    connect(pNew, &QAction::triggered, [=](){qDebug()<<"新建被按下";});

    pFile->addSeparator(); //添加分割线；

    QAction *pOpen = pFile->addAction("打开");
    connect(pOpen, &QAction::triggered, [=](){qDebug()<<"打开被按下";});

    //QMenu *edit = mBar->addMenu("编辑");
    //工具栏, 本质上为菜单项的快捷方式
    QToolBar *toolbar = addToolBar("ToolBar");
        //工具栏添加快捷键
    toolbar->addAction(pNew);
    toolbar->addAction(pOpen);

        //添加按钮与工具栏结合
    QPushButton *b = new QPushButton(this);
    b->setText("@-@");
        //添加小控件
    toolbar->addWidget(b);
    connect(b, &QPushButton::released, [=](){b->setText("haha");});

    //状态栏
    QStatusBar *statusbar = statusBar();
    QLabel *lable = new QLabel(this);
    lable->setText("Normal text file");
    statusbar->addWidget(lable);
    statusbar->addWidget(new QLabel("safe", this));
    statusbar->addPermanentWidget(new QLabel("OK", this)); //从右往左添加

    //核心控件
    QTextEdit *text = new QTextEdit(this);
    setCentralWidget(text);

    //浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    QTextEdit *text1 = new QTextEdit(this);
    dock->setWidget(text1);
}

MainWindow::~MainWindow()
{
}

