#ifndef PINGER_H
#define PINGER_H

#include <sys/wait.h>
#include <unistd.h>
#include <iostream>


class Pinger
{
public:
    Pinger();

private:
    static const int buflen = 1024;
    int pipe_arr[2];
    char buf[buflen];
};

#endif // PINGER_H
