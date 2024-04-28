//
// Created by David Exinor on 2024-04-27.
//

#include <iostream>
#include <thread>
#include "Server.h"
#include "httplib.h"

// Constructor
Server::Server(int port) {
    this->port = port;
}

// Create and initialize server
void Server::init() {
    server.Get("/authorize", [](const httplib::Request& request, httplib::Response& response) {
        // Extract query params from request
        // Extract query parameters from the request
        auto response_type = request.get_param_value("response_type");
        auto client_id = request.get_param_value("client_id");
        auto redirect_uri = request.get_param_value("redirect_uri");
        auto code_challenge_method = request.get_param_value("code_challenge_method");
        auto code_challenge = request.get_param_value("code_challenge");

        // print params to console
        std::cout << "response_type: " << response_type << std::endl;
        std::cout << "client_id: " << client_id << std::endl;
        std::cout << "redirect_uri: " << redirect_uri << std::endl;
        std::cout << "code_challenge_method: " << code_challenge_method << std::endl;
        std::cout << "code_challenge: " << code_challenge << std::endl;
    });
}

// start server
void Server::start() {
    std::cout << "Local Server has been initialized" << std::endl;
    server_thread = std::thread([this](){
        server.listen("localhost", port);
    });
}

// Stop server
void Server::stop() {
    server.stop(); // stop server gracefully
    if (server_thread.joinable()) {
        server_thread.join(); // join the server thread
    }
    std::cout << "Local Server has been terminated" << std::endl;
}
