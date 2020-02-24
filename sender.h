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
#include <config_parser.h>


class Sender : public QObject{

    Q_OBJECT

public:

    //Methods
    Sender(MainWindow&, Config *);
    Config *myo_config;

public slots:
    void receive_todo(std::vector<unsigned long>&, bool&);

private:

    //Methods
    void send_wol(std::vector<unsigned long> &);
    std::string get_ether(const std::string &hardware_addr);
    unsigned get_hex_from_string(const std::string &);
    void send_shutdown(std::vector<unsigned long> &);

    //Constants
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
