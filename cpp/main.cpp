#include "console.h"
#include "appearance.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Console w;
    w.show();


    return a.exec();
}
