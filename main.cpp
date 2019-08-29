#include <mainwindow.h>
#include <config_parser.h>
#include <sender.h>

#include <QApplication>




int main(int argc, char *argv[])
{
        Machines m;
        QApplication a(argc, argv);
        MainWindow w (m.no_machines, m.vtable);
        w.show();
        Sender s (w);
        a.exec();
}





