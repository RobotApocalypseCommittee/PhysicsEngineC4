//
// Created by Attoa on 20/06/2020.
//

#include <QApplication>
#include <QMainWindow>

int main(int argc, char** argv) {
#ifdef Q_OS_ANDROID
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QMainWindow mainWin;
    mainWin.show();
    return QApplication::exec();
}
