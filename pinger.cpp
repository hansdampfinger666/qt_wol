#include "pinger.h"

Pinger::Pinger()
{
    int pipe_arr[2];
    char buf[BUFLEN];

    //Create pipe - pipe_arr[0] is "reading end", pipe_arr[1] is "writing end"
    pipe(pipe_arr);

    if(fork() == 0) //child
    {
        dup2(pipe_arr[1], STDOUT_FILENO);
        execl("/sbin/ping", "ping", "-c 1", "8.8.8.8", (char*)NULL);
    }
    else //parent
    {
        wait(NULL);
        read(pipe_arr[0], buf, BUFLEN);
        printf("%s\n", buf);
    }

    close(pipe_arr[0]);
    close(pipe_arr[1]);
}

