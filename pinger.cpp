#include "pinger.h"

void Pinger::discover_network(Config *config)
{
    int pipe_arr[2];
    char buf[BUFLEN];

    //Create pipe - pipe_arr[0] is "reading end", pipe_arr[1] is "writing end"
    pipe(pipe_arr);

    if(fork() == 0) //child
    {
        dup2(pipe_arr[1], STDOUT_FILENO);
        execl("/sbin/arp", "arp", "-a", (char*)NULL);
    }
    else //parent
    {
        wait(NULL);
        read(pipe_arr[0], buf, BUFLEN);
        printf("%s\n", buf);
    }

    close(pipe_arr[0]);
    close(pipe_arr[1]);

    std::ostringstream buf_str;
    buf_str << buf;

    parse_arp_response(buf_str.str(), config);
}


void Pinger::parse_arp_response(std::string buf, Config *config)
{
    for (unsigned long i = 0; i < config->mys_config.macs.size(); i++)
    {
        unsigned long found_mac_at = buf.find(config->mys_config.macs.at(i), 0);

        if (found_mac_at != std::string::npos)
        {
            config->mys_config.online.at(i) = true;
            config->mys_config.ips.at(i) = buf.substr(buf.substr(0, found_mac_at).find_last_of("(") + 1,
                                           buf.substr(0, found_mac_at).find_last_of(")") -
                                           buf.substr(0, found_mac_at).find_last_of("(") - 1);
        }
    }
}


void Pinger::send_ping(std::string *ip)
{
    int pipe_arr[2];
    char buf[BUFLEN];

    //Create pipe - pipe_arr[0] is "reading end", pipe_arr[1] is "writing end"
    pipe(pipe_arr);

    if(fork() == 0) //child
    {
        dup2(pipe_arr[1], STDOUT_FILENO);
        execl("/sbin/ping", "ping", "-c 1", &ip, (char*)NULL);
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
