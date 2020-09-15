#include <QLineEdit>
#include <QErrorMessage>
#include <QGraphicsScene>
#include <QCheckBox>
#include <utility>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../threading/safequeue.h"
#include "GraphicsScene.h"


QGraphicsScene *scene;


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionCircle);
    actionGroup->addAction(ui->actionTriangle);
    actionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);
    scene = new GraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->propertiesView->verticalHeader()->hide();
    ui->propertiesView->horizontalHeader()->hide();
    world = std::make_shared<physics::World>();
    scene->setSceneRect(-10, -10, 20, 20);
    ui->graphicsView->fitInView(-10, -10, 20, 20, Qt::KeepAspectRatio);
    ui->graphicsView->scale(1, -1);
    connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::on_sceneselection_changed);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_stepButton_pressed() {
    float timestep = 1e-4f;
    bool ok = true;
    int steps = findChild<QLineEdit *>("stepsLineEdit")->text().toInt(&ok);
    bool has_gravity = findChild<QCheckBox *>("gravityCheckBox")->isChecked();

    if (!ok) {
        auto errorMessage = new QErrorMessage(this);
        errorMessage->showMessage("Luhmao");
        return;
    }

    world->setGravity(has_gravity ? physics::Vec2{0, -9.8f} : physics::Vec2{0, 0});

    for (int i = 0; i < steps; i++) {
        world->step(timestep);

        //printf("circle 1 Pos: x: %f, y: %f\n", circ1->pos.x, circ1->pos.y);
        //printf("circle 2 Pos: x: %f, y: %f\n\n", circ2->pos.x, circ2->pos.y);
    }
    for (auto &s: shapes) {
        s->updateFromPhysics();
    }
}

void MainWindow::on_actionTriangle_triggered() {
    switchShape(std::make_shared<TriangleShapeConstruct>(world));
}

void MainWindow::on_actionCircle_triggered() {
    switchShape(std::make_shared<CircleShapeConstruct>(world));
}

void MainWindow::viewClicked(QPointF pos) {
    if (currentShape && currentShape->isPreCreation()) {
        // Time to create a circle!!!
        auto *item = currentShape->createInScene(*scene, pos);
        item->setPos(pos);
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item->setData(0, QVariant::fromValue(currentShape));
        shapes.push_back(currentShape);
        for (auto a:actionGroup->actions()) {
            a->setChecked(false);
        }
    }
}

void MainWindow::on_sceneselection_changed() {
    auto x = scene->selectedItems();
    if (!x.empty()) {
        switchShape(x[0]->data(0).value<std::shared_ptr<ShapeConstruct>>());
    }
}

void MainWindow::switchShape(std::shared_ptr<ShapeConstruct> shape) {
    auto oldCurrentShape = currentShape;
    currentShape = std::move(shape);

    auto *oldModel = ui->propertiesView->model();
    ui->propertiesView->setModel(currentShape->createModel().release());
    delete oldModel;

    ui->propertiesView->resizeColumnsToContents();
    ui->propertiesView->horizontalHeader()->setStretchLastSection(true);
}
