#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "product.h"
#include "ui_new_product.h"



#include <iostream>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}









