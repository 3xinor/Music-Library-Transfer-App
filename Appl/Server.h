//
// Created by David Exinor on 2024-04-27.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_SERVER_H
#define MUSIC_LIBRARY_TRANSFER_APP_SERVER_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

bool handleRequest(http::request<http::string_body>& request, tcp::socket& socket, std::string* spotifyAuthorizationCodePtr);

void runServer(int* running, std::string* spotifyAuthorizationCodePtr);


#endif //MUSIC_LIBRARY_TRANSFER_APP_SERVER_H
