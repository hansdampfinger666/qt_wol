#ifndef PINGER_H
#define PINGER_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <config_parser.h>

#define BUFLEN 1024


class Pinger
{
public:

    //Methods
    void static discover_network(Config *);
    void static parse_arp_response(std::string, Config *);

//    void static send_ping(std::string *ip);
};

#endif // PINGER_H
