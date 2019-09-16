#include "pinger.h"

Pinger::Pinger()
{
//    ptr_start_loop = &Pinger::start_loop;

}

bool Pinger::send_ping()
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

    std::string buf_str;
    int received_pos;
    int last_comma_pos;
    int percent_packetloss;

    buf_str = static_cast<std::string>(buf);
    received_pos = buf_str.find("% packet loss");
    last_comma_pos = buf_str.substr(0, received_pos).find_last_of(",")+1;
    percent_packetloss = stoi(buf_str.substr(last_comma_pos, received_pos-last_comma_pos));

    std::cout << "% of packets lost: " << percent_packetloss << std::endl;

    switch(percent_packetloss)
    {
    case 100:
        return false;
    case 0:
        return true;
    default:
        return false;
    }

}


void Pinger::start_loop()
{
    while(true)
    {
//        state_changed = send_ping();
        std::cout << "Function pointer and thread is working!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }
}
