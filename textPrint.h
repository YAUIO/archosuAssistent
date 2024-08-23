#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <thread>

struct tp {
    static void printHello();
    static void printHelloBig();
    static void div();
    static bool yn(std::string const& question, char const& preffered);
    static bool yn(std::string const& question);
    static bool exec(std::string const& command);
};

