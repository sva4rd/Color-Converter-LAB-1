#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class Widget;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Widget *mainWidget;

private slots:
    void showMistakeMessage();
    void clearMistakeMessage();
};

#endif // MAINWINDOW_H
