#include <QApplication>
#include "registrywindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RegistryWindow window;
    window.show();
    return app.exec();
}
