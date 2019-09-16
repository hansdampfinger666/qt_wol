#ifndef PINGER_H
#define PINGER_H

#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <thread>


class Pinger
{
public:
    Pinger();
    [[ noreturn ]] void start_loop();
    void (Pinger::*ptr_start_loop)() = &Pinger::start_loop;


private:
    bool send_ping();


    bool state_changed;
    static const int buflen = 1024;
    int pipe_arr[2];
    char buf[buflen];
};

#endif // PINGER_H
