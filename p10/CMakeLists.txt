cmake_minimum_required(VERSION 3.30)
project(p10)

set(CMAKE_CXX_STANDARD 20)

add_executable(p10 main.cpp
        Dice.hpp
        Dice.cpp
        tools.hpp
        tools.cpp
        Enums.hpp
        Enums.cpp
        Player.hpp
        Player.cpp
        Column.hpp
        Column.cpp
        Game.cpp
        Game.hpp
        Board.hpp
        Board.cpp
        CList.cpp
        CList.hpp
        Exceptions.cpp
        Exceptions.hpp
)
