#ifndef MACHINES_H
#define MACHINES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <array>


class Config{

public:

    //Methods
    Config();
    void out();
    void out(int &);

    //Variables
//    std::vector<std::vector<std::string>> mys_config;
    int my_no_machines = 0;

    struct myty_config
    {
        std::vector<std::string> names {};
        std::vector<std::string> macs {};
        std::vector<std::string> ips {};
        std::vector<std::string> ostype {};
        std::vector<std::string> ssh_pubkey_path {};
        std::vector<std::string> ssh_user {};
        std::vector<bool> online {};
    };
    myty_config mys_config {};

    //Constants
    static const int myc_qty_params = 3;
    const std::string myc_machine_tag = "machine = ";
    const std::string myc_mac_tag = "mac = ";
    const std::string myc_ostype_tag = "ostype = ";
    const std::string myc_ssh_pubkey_tag = "ssh_pubkey_path = ";
    const std::string myc_ssh_user_tag = "ssh_user = ";
    const long myc_machine_len = myc_machine_tag.length();
    const long myc_mac_len = myc_mac_tag.length();
    const long myc_ostype_len = myc_ostype_tag.length();
    const long myc_ssh_pubkey_len = myc_ssh_pubkey_tag.length();
    const long myc_ssh_user_len = myc_ssh_user_tag.length();

private:

    //Methods
    void read_file();
    std::string trim_r(std::string);
};

#endif // MACHINES_H
