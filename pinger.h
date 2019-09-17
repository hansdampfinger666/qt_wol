#ifndef PINGER_H
#define PINGER_H

#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <QObject>
#include <mainwindow.h>
#include <mutex>
#include <thread>
#include <condition_variable>


class Pinger : public QObject
{
    Q_OBJECT

public:
    Pinger(MainWindow&);
    void start_loop();
    std::thread pinger_thread;

public slots:
    void receive_stop();

private:
    bool send_ping();

    bool application_closing = false;
    bool state_changed;
    static const int buflen = 1024;
    int pipe_arr[2];
    char buf[buflen];
    std::mutex mutex;
    std::condition_variable terminate;
};

#endif // PINGER_H
