#include <QApplication>
#include "mainwindow.h"
#include "physics/object.h"

int main(int argc, char** argv) {
#ifdef Q_OS_ANDROID
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    MainWindow mainWin;
    mainWin.show();
    return QApplication::exec();
}
