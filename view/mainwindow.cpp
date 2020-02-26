#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //调用样式表
    ui->lineEdit_2->setStyleSheet("QLineEdit {"
                                  "border: 2px solid gray;"
                                  "border-radius: 10px;"
                                  "padding: 0 8px;"
                                  "background: yellow;"
                                  "selection-background-color: darkgray;"
                              "}");
    ui->lineEdit->setStyleSheet("QLineEdit {"
                                  "border: 2px solid gray;"
                                  "border-radius: 10px;"
                                  "padding: 0 8px;"
                                  "background: green;"
                                  "selection-background-color: darkgray;"
                              "}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

