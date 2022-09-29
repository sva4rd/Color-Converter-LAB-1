#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    mainWidget = new Widget(this);
    setCentralWidget(mainWidget);
    statusBar()->show();

    setFont(*mainWidget->font);

    connect(mainWidget, &Widget::showStatus, this, &MainWindow::showMistakeMessage);
    connect(mainWidget, &Widget::clearStatus, this, &MainWindow::clearMistakeMessage);

    setWindowTitle("Color Converter");
    setMinimumSize(430, 430);
}

MainWindow::~MainWindow()
{
    delete mainWidget;
}

void MainWindow::showMistakeMessage()
{
    statusBar()->showMessage("Range boundaries were violated, the values were automatically rounded", 5000);
}

void MainWindow::clearMistakeMessage()
{
    statusBar()->clearMessage();
}
