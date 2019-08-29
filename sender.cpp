#include <sender.h>


Sender::Sender(MainWindow &w){

    QObject::connect(&w, &MainWindow::emit_todo, this, &Sender::receive_todo);
}


void Sender::receive_todo(MainWindow::Todo_list& todo){

    if (!todo.wol.empty()){       // check if sender is receiving a WOL todo list

    std::cout << "Sender received the following WOL todo list:" << std::endl;
    cout_vec(todo.machines);

    for (std::vector<std::string> elem : todo.machines) {

        send_wol(elem[1], port, bcast);
        std::cout << "sending WOL signal to: " << elem[1] << " to port: " << port << " to bcast: " << bcast << std::endl;
    }
    }

    if (!todo.shutdown.empty()){        // check if sender is receiving a shutdown todo list

        std::cout << "Sender received the following shutdown todo list:" << std::endl;
        cout_vec(todo.machines);

        for (std::vector<std::string> elem : todo.machines) {

            std::cout << "sending shutdown signal to: " << elem[1] << " to port: " << port << " to bcast: " << bcast << std::endl;
        }
    }
}


void Sender::send_wol(const std::string& hardware_addr, unsigned port, unsigned long bcast){

    // Fetch the hardware address.
    const std::string ether_addr{get_ether(hardware_addr)};

    socket_handle packet{socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};

    // Build the message to send.
    //   (6 * 0XFF followed by 16 * destination address.)
    std::string message(6, 0xFF);
    for (size_t i = 0; i < 16; ++i) {
        message += ether_addr;
    }

    // Set socket options.
    const int optval{1};
    if (setsockopt(packet.get(), SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0) {
        throw std::runtime_error("Failed to set socket options");
    }

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









template <typename T> void Sender::cout_vec (std::vector<std::vector<T>> &vec){

    unsigned long rows = 1;
    rows = vec.size();

        for (unsigned long r = 0; r < rows; r++){

            for (std::string elem : vec[r] ){
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
}
