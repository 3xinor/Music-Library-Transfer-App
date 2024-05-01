//
// Created by David Exinor on 2024-04-27.
//

#include <iostream>
#include "Server.h"

bool handleRequest(http::request<http::string_body>& request, tcp::socket& socket, std::string* spotifyAuthorizationCodePtr) {
    // Extract the URL path and query parameters from requests
    std::string target = request.target();
    std::string query_params = target.substr(target.find('?') + 1);

    // Parse query params
    std::cout << "Callback Response from Spotify: " << query_params << std::endl;
    if (query_params != "") {
        // terminate the server thread, callback was received
        *spotifyAuthorizationCodePtr = std::move(query_params);
        return true;
    }
    return false;
}

void runServer(int* running, std::string* spotifyAuthorizationCodePtr) {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, {tcp::v4(), 8888});

    bool callbackReceived = false;
    while (*running && !callbackReceived) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        // read the HTTP request
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> request;
        boost::beast::http::read(socket, buffer, request);

        // Handle the request
        callbackReceived = handleRequest(request, socket, spotifyAuthorizationCodePtr);

        // close the socket
        socket.shutdown(tcp::socket::shutdown_send);
        boost_swap_impl::this_thread::sleep_for(boost_swap_impl::chrono::seconds(1));
    }
}