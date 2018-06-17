#include "view/Widget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //fixare l'icona
    //app.setWindowIcon(QIcon(":/images/kalk-icon.jpg"));
    Widget w;
    w.show();

    return app.exec();
}
