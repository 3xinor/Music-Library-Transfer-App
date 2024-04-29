//
// Created by David Exinor on 2024-04-27.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_SERVER_H
#define MUSIC_LIBRARY_TRANSFER_APP_SERVER_H

#include <thread>

class Server {
private:
    int port;
    //httplib::Server server;
    std::thread server_thread;
public:
    Server(int port);

    // initializes server
    void init();

    // starts server
    void start();

    // stops server
    void stop();

    // thread function
    void threadFunction();
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_SERVER_H
