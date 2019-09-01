#include <mainwindow.h>
#include <config_parser.h>
#include <sender.h>
#include <QApplication>

#include <pinger.h>


int main(int argc, char *argv[])
{
    Pinger p;

    Config m;
    QApplication a(argc, argv);
    MainWindow w (m.config);
    w.show();
    Sender s (w);
    a.exec();
}





