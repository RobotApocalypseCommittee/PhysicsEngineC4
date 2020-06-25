#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "physics/world.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_testButton_pressed();

    void on_stepButton_pressed();

private:
    physics::World *world;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
