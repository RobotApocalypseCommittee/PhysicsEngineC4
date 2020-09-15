#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qactiongroup.h>
#include <QtCore/QAbstractTableModel>

#include "physics/world.h"
#include "ShapeManager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void viewClicked(QPointF pos);

private slots:

    void on_stepButton_pressed();

    void on_actionTriangle_triggered();

    void on_actionCircle_triggered();

    void on_sceneselection_changed();

private:
    void switchShape(std::shared_ptr<ShapeConstruct> shape);

    std::shared_ptr<physics::World> world;
    QActionGroup *actionGroup;
    Ui::MainWindow *ui;
    std::shared_ptr<ShapeConstruct> currentShape;
    std::vector<std::shared_ptr<ShapeConstruct>> shapes;

};

#endif // MAINWINDOW_H
