#include <mainwindow.h>
#include <config_parser.h>
#include <sender.h>
#include <QApplication>
#include <pinger.h>

#include <thread>


int main(int argc, char *argv[])
{
    Config m;
    QApplication a(argc, argv);
    MainWindow w (m.config);
    w.show();
    Pinger p (w);
    Sender s (w);
    a.exec();

    std::cout << "Main thread no " << std::this_thread::get_id() << " has stopped working" << std::endl;
}





