#include "pinger.h"


Pinger::Pinger(MainWindow &w)
{
    QObject::connect(&w, &MainWindow::emit_pinger_stop, this, &Pinger::receive_stop);
    start_loop();
}


bool Pinger::send_ping()
{
    //Create pipe - pipe_arr[0] is "reading end", pipe_arr[1] is "writing end"
    pipe(pipe_arr);

    if(fork() == 0) //child
    {
        dup2(pipe_arr[1], STDOUT_FILENO);
        execl("/sbin/ping", "ping", "-c 1", "192.168.178.21", static_cast<char*>(nullptr));  //linux specific
    }
    else //parent
    {
        wait(nullptr);
        read(pipe_arr[0], buf, buflen);
        std::cout << buf;
        std::cout << "Pinger function thread id: " << std::this_thread::get_id() << std::endl;
    }

    close(pipe_arr[0]);
    close(pipe_arr[1]);

    std::string buf_str = static_cast<std::string>(buf);
    int received_pos = buf_str.find("% packet loss");
    int last_comma_pos = buf_str.substr(0, received_pos).find_last_of(",")+1;
    int percent_packetloss = stoi(buf_str.substr(last_comma_pos, received_pos-last_comma_pos));

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
    receive_stop();

    {
    auto locked = std::unique_lock<std::mutex>(mutex);
    application_closing = false;
    }

    pinger_thread = std::thread([=]()
    {
        auto locked = std::unique_lock<std::mutex>(mutex);

        while(!application_closing)
        {
            std::cout << "Pinger loop thread number " << std::this_thread::get_id() << " working!" << std::endl;
            terminate.wait_for(locked, std::chrono::seconds(3));
            send_ping();
        }
    });
}


void Pinger::receive_stop()
{
    {
        // Set the predicate
        auto locked = std::unique_lock<std::mutex>(mutex);
        application_closing = true;
    }

    // Tell the thread the predicate has changed
    terminate.notify_one();

    if(pinger_thread.joinable())
    {
        pinger_thread.join();
    }
}
