cmake_minimum_required(VERSION 3.27)
project(Music_Library_Transfer_App)

set(CMAKE_CXX_STANDARD 14)

set(CURL_DIR "/opt/homebrew/opt/curl")

include_directories(Appl)

add_executable(Music_Library_Transfer_App
        Appl/Converter.cpp
        Appl/Converter.h
        Appl/MusicProfile.cpp
        Appl/MusicProfile.h
        Appl/Platforms.h
        Appl/PlayList.cpp
        Appl/PlayList.h
        Appl/Song.cpp
        Appl/Song.h
        Appl/WebDomainAPI.cpp
        Appl/WebDomainAPI.h
        Appl/AppleMusicAPI.h
        Appl/AppleMusicAPI.cpp
        Appl/SpotifyMusicAPI.h
        Appl/SpotifyMusicAPI.cpp
        Appl/Server.h
        Appl/Server.cpp
        Appl/User.h
        Appl/User.cpp)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR}
        ${CURL_DIR}/include/curl
        ${CMAKE_SOURCE_DIR}/Libraries/json/include)
target_link_libraries(Music_Library_Transfer_App
        ${OPENSSL_LIBRARIES}
        ${CURL_DIR}/lib/libcurl.dylib)
