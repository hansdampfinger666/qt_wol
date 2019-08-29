#ifndef SENDER_H
#define SENDER_H

#include <vector>
#include <string>
#include <mainwindow.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <QObject>


class Sender : public QObject{

    Q_OBJECT

public:
    Sender(MainWindow&);

    template <typename T> static void cout_vec (std::vector<std::vector<T>>&);

public slots:
    void receive_todo(MainWindow::Todo_list&);

private:
    void send_wol(const std::string& hardware_addr, unsigned port, unsigned long bcast);
    std::string get_ether(const std::string& hardware_addr);
    unsigned get_hex_from_string(const std::string&);

    const unsigned port{60000};
    const unsigned long bcast{0xFFFFFFFF};

    class socket_handle{

        public:
            explicit socket_handle(int descriptor) : _descriptor(descriptor) {
                if (_descriptor < 0)
                    throw std::runtime_error("Failed to open socket");
            }
            socket_handle(const socket_handle&) = delete;
            socket_handle& operator=(const socket_handle&) = delete;

            int get() const {
                return _descriptor;
            }

            ~socket_handle() {
                close(_descriptor);
            }

        private:
            const int _descriptor;
    };
};

#endif // SENDER_H
