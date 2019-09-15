#include "pinger.h"

Pinger::Pinger()
{
    //Create pipe - pipe_arr[0] is "reading end", pipe_arr[1] is "writing end"
    pipe(pipe_arr);

    if(fork() == 0) //child
    {
        dup2(pipe_arr[1], STDOUT_FILENO);
        execl("/sbin/ping", "ping", "-c 1", "192.168.178.1", static_cast<char*>(nullptr));  //linux specific
    }
    else //parent
    {
        wait(nullptr);
        read(pipe_arr[0], buf, buflen);
        std::cout << buf;
    }

    close(pipe_arr[0]);
    close(pipe_arr[1]);
}

