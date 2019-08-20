#ifndef MACHINES_H
#define MACHINES_H

#include <iostream>
#include <vector>
#include <fstream>


class Machines{

public:
    Machines();
    std::vector<std::vector<std::string>> vtable;
    int no_machines = 0;

    static const int no_config_params = 3;
    const std::string id_machine = "machine = ";
    const long len_id_machine = id_machine.length();
    const std::string id_mac = "mac = ";
    const long len_id_mac = id_mac.length();
    const std::string id_os = "ostype = ";
    const long len_id_os = id_os.length();

private:
    void read_file();
    std::string del_trailing_spaces (std::string);


    void cout_vec (std::vector< std::vector <std::string> > &);
};

#endif // MACHINES_H
