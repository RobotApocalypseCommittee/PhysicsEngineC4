#include <QLineEdit>
#include <QErrorMessage>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "physics/shapes/circle.h"
#include "physics/collision.h"
#include "physics/world.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_testButton_pressed() {
    bool ok = true;
    float c1Radius = findChild<QLineEdit *>("c1RadiusLineEdit")->text().toFloat(&ok);
    float c2Radius = findChild<QLineEdit *>("c2RadiusLineEdit")->text().toFloat(&ok);
    float c1Mass = findChild<QLineEdit *>("c1MassLineEdit")->text().toFloat(&ok);
    float c2Mass = findChild<QLineEdit *>("c2MassLineEdit")->text().toFloat(&ok);
    float c1XPos = findChild<QLineEdit *>("c1XPosLineEdit")->text().toFloat(&ok);
    float c1YPos = findChild<QLineEdit *>("c1YPosLineEdit")->text().toFloat(&ok);
    float c2XPos = findChild<QLineEdit *>("c2XPosLineEdit")->text().toFloat(&ok);
    float c2YPos = findChild<QLineEdit *>("c2YPosLineEdit")->text().toFloat(&ok);
    float c1XVel = findChild<QLineEdit *>("c1XVelLineEdit")->text().toFloat(&ok);
    float c1YVel = findChild<QLineEdit *>("c1YVelLineEdit")->text().toFloat(&ok);
    float c2XVel = findChild<QLineEdit *>("c2XVelLineEdit")->text().toFloat(&ok);
    float c2YVel = findChild<QLineEdit *>("c2YVelLineEdit")->text().toFloat(&ok);

    if (!ok) {
        auto errorMessage = new QErrorMessage(this);
        errorMessage->showMessage("Luhmao");
        return;
    }

    std::shared_ptr<physics::Circle> circ1(new physics::Circle(c1Radius));
    std::shared_ptr<physics::Circle> circ2(new physics::Circle(c2Radius));

    circ1->mass = c1Mass;
    circ2->mass = c2Mass;

    circ1->pos = {c1XPos, c1YPos};
    circ2->pos = {c2XPos, c2YPos};

    circ1->vel = {c1XVel, c1YVel};
    circ2->vel = {c2XVel, c2YVel};

    world = new physics::World();
    world->addObject(circ1);
    world->addObject(circ2);
}

void MainWindow::on_stepButton_pressed() {
    float timestep = 1e-4f;
    bool ok = true;
    int steps = findChild<QLineEdit *>("stepsLineEdit")->text().toInt(&ok);

    if (!ok) {
        auto errorMessage = new QErrorMessage(this);
        errorMessage->showMessage("Luhmao");
        return;
    }

    for (int i = 0; i < steps; i++) {
        world->step(timestep);

        //printf("circle 1 Pos: x: %f, y: %f\n", circ1->pos.x, circ1->pos.y);
        //printf("circle 2 Pos: x: %f, y: %f\n\n", circ2->pos.x, circ2->pos.y);
    }
}
