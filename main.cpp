#include "MainWindow.h"

#include <QApplication>
#include "Model/Card.h"
#include "Template/container.h"
#include "Template/deepptr.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
