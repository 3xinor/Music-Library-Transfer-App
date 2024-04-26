cmake_minimum_required(VERSION 3.27)
project(Music_Library_Transfer_App)

set(CMAKE_CXX_STANDARD 14)

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
        Appl/AppleMusicAPI.cpp)
