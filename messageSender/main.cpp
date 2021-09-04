#include "interface.h"
#include "filehandler.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    interface w;
    w.show();

    return a.exec();
}
