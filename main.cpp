#include <mainwindow.h>
#include <config_parser.h>
#include <sender.h>
#include <QApplication>
#include <pinger.h>


int main(int argc, char *argv[])
{
    Config o_config;
    QApplication o_qapp(argc, argv);
    MainWindow o_window (&o_config);
    o_window.show();
    Sender o_sender (o_window, &o_config);
    o_qapp.exec();
}





