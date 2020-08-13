#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qactiongroup.h>
#include <QtCore/QAbstractTableModel>

#include "physics/world.h"

namespace Ui {
    class MainWindow;
}

enum class ShapeCreationType {
    None,
    Circle,
    Triangle
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void viewClicked(QPointF pos);

private slots:

    void on_testButton_pressed();

    void on_stepButton_pressed();

    void on_actionTriangle_triggered();
    void on_actionCircle_triggered();

private:
    void switchPropertiesModel(QAbstractTableModel* model);

    physics::World *world;
    QActionGroup *actionGroup;
    Ui::MainWindow *ui;
    ShapeCreationType currentCreation = ShapeCreationType::None;

};

#endif // MAINWINDOW_H
