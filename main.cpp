#include "MainWindow.h"

#include <QApplication>
#include "Model/Card.h"
#include "Template/container.h"
#include "Template/deepptr.h"
#include "Controller/controller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Container<DeepPtr<Card>> mod;
    Controller c(mod);
    MainWindow w(&c);
    c.setView(&w);
    w.show();
    return a.exec();
}
