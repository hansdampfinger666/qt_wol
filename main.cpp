#include <mainwindow.h>
#include <config_parser.h>
#include <sender.h>
#include <QApplication>
#include <pinger.h>

#include <thread>


int main(int argc, char *argv[])
{

    Pinger p;
    std::thread pinger_thread(&Pinger::start_loop, p);
    pinger_thread.join();


    Config m;
    QApplication a(argc, argv);
    MainWindow w (m.config);
    w.show();
    Sender s (w);
    a.exec();


}





