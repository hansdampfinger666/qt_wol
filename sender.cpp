#include <sender.h>


Sender::Sender(MainWindow &w, Config *config)
{
    myo_config = config;
    QObject::connect(&w, &MainWindow::emit_todo, this, &Sender::receive_todo);
}


void Sender::receive_todo(std::vector<unsigned long>& todo, bool& mode)
{
    if (mode == 1)
        send_wol(todo);
    else
        send_shutdown(todo);
}


//void Sender::send_wol(const std::string& hardware_addr, unsigned port, unsigned long bcast)
void Sender::send_wol(std::vector<unsigned long> &todo)
{
    for(unsigned int i = 0; i < todo.size(); i++)
    {
        const std::string ether_addr{get_ether(myo_config->mys_config.macs.at(todo.at(i)))};

        socket_handle packet{socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};

        // Build the message to send.
        //   (6 * 0XFF followed by 16 * destination address.)
        std::string message(6, 0xFF);

        for (size_t i = 0; i < 16; ++i)
            message += ether_addr;

        // Set socket options.
        const int optval{1};

        if (setsockopt(packet.get(), SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0)
            throw std::runtime_error("Failed to set socket options");

        // Set up address
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = bcast;
        addr.sin_port = htons(port);

        // Send the packet out.
        if (sendto(packet.get(), message.c_str(), message.length(), 0,
            reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
            throw std::runtime_error("Failed to send packet");
        }
    }
}


void Sender::send_shutdown(std::vector<unsigned long> &todo)
{
    for(unsigned long i = 0; i < todo.size(); i++)
    {
        int pipe_arr[2];
        char buf[BUFLEN];

        std::string ssh_app = "/sbin/ssh";
        std::string ssh = "ssh";
        std::string ssh_file;
        std::string ssh_opt_id_file = "-i";
        std::string ssh_server;
        std::string user = "root";
        std::string ssh_command = "poweroff";

//        const char *ssh_app_c = ssh_app.c_str();
//        const char *ssh_c = ssh.c_str();

//        const char *ssh_total_c = (ssh_opt_id_file + " " +
//                                   myo_config->mys_config.ssh_pubkey_path.at(todo.at(i)) + " " +
//                                   user + "@" + myo_config->mys_config.ips.at(todo.at(i)) + " " +
//                                   ssh_command).c_str();

        ssh_file = ssh_opt_id_file + " " + myo_config->mys_config.ssh_pubkey_path.at(todo.at(i));
        ssh_server = user + "@" + myo_config->mys_config.ips.at(todo.at(i));

        std::cout << ssh_app << std::endl;
        std::cout << ssh << std::endl;
        std::cout << ssh_file << std::endl;
        std::cout << ssh_server << std::endl;
        std::cout << ssh_command << std::endl;

        //Create pipe - pipe_arr[0] is "reading end", pipe_arr[1] is "writing end"
        pipe(pipe_arr);

        if(fork() == 0) //child
        {
            std::cout << " sending " << std::endl;

            dup2(pipe_arr[1], STDOUT_FILENO);

//            execl("/sbin/ssh", "ssh", "-i /home/al/.ssh/amd_freenas", "root@192.168.178.48", "poweroff", (char*)NULL);

            //"-i /home/al/.ssh/amd_freenas",

            execl(ssh_app.c_str(), ssh.c_str(), ssh_file.c_str(),
                  ssh_server.c_str(), ssh_command.c_str(), (char*)NULL);
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
}


std::string Sender::get_ether(const std::string& hardware_addr){

    std::string ether_addr;

    for (size_t i = 0; i < hardware_addr.length();) {
        // Parse two characters at a time.
        unsigned hex = get_hex_from_string(hardware_addr.substr(i, 2));
        i += 2;

        ether_addr += static_cast<char>(hex & 0xFF);

        // We might get a colon here, but it is not required.
        if (hardware_addr[i] == ':')
            ++i;
    }

    if (ether_addr.length() != 6)
        throw std::runtime_error(hardware_addr + " not a valid ether address");

    return ether_addr;
}


unsigned Sender::get_hex_from_string(const std::string& s)
{
    unsigned hex{0};

    for (size_t i = 0; i < s.length(); ++i) {
        hex <<= 4;
        if (isdigit(s[i])) {
            hex |= s[i] - '0';
        }
        else if (s[i] >= 'a' && s[i] <= 'f') {
            hex |= s[i] - 'a' + 10;
        }
        else if (s[i] >= 'A' && s[i] <= 'F') {
            hex |= s[i] - 'A' + 10;
        }
        else {
            throw std::runtime_error("Failed to parse hexadecimal " + s);
        }
    }
    return hex;
}
