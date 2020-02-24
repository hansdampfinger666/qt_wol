#include <config_parser.h>


Config::Config()
{
    myty_config mys_config;
    read_file();
}

void Config::read_file()
{
    std::string str;
    std::ifstream file("/home/al/Documents/QtCreatorProjects/wolqt/config");   // turn into variable (option in application)

    while(getline(file,str))
    {
        if(str.substr(0, myc_machine_len) == myc_machine_tag)
        {
            my_no_machines++;
            mys_config.names.push_back(trim_r(str.substr(myc_machine_len)));
            mys_config.macs.push_back("");
            mys_config.ips.push_back("");
            mys_config.ostype.push_back("");
            mys_config.ssh_pubkey_path.push_back("");
            mys_config.online.push_back(false);
        }
        else if(str.substr(0, myc_mac_len) == myc_mac_tag)
            mys_config.macs.at(my_no_machines - 1) = trim_r(str.substr(myc_mac_len));
        else if(str.substr(0, myc_ostype_len) == myc_ostype_tag)
            mys_config.ostype.at(my_no_machines - 1) = trim_r(str.substr(myc_ostype_len));
        else if(str.substr(0, myc_ssh_pubkey_len) == myc_ssh_pubkey_tag)
            mys_config.ssh_pubkey_path.at(my_no_machines - 1) = trim_r(str.substr(myc_ssh_pubkey_len));
    }
//    out();
}


std::string Config::trim_r (std::string str)
{
        return str = str.substr(0, str.find_last_not_of(" ")+1);
}


void Config::out()
{
    for(unsigned long i = 0; i < mys_config.names.size(); i++)
    {
        std::cout << mys_config.names.at(i) << "   "
                  << mys_config.macs.at(i) << "   "
                  << mys_config.ips.at(i) << "   "
                  << mys_config.ostype.at(i) << "   "
                  << mys_config.ssh_pubkey_path.at(i) << "   "
                  << mys_config.online.at(i) << "   "
                  << std::endl;
    }
    std::cout << std::endl;
}


void Config::out(int &i)
{
    std::cout << mys_config.names.at(i) << "   "
              << mys_config.macs.at(i) << "   "
              << mys_config.ips.at(i) << "   "
              << mys_config.ostype.at(i) << "   "
              << mys_config.ssh_pubkey_path.at(i) << "   "
              << mys_config.online.at(i) << "   "
              << std::endl;
}
