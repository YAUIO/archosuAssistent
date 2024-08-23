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
    static void err(std::string const& error);
    static void err();
    static std::string execreturn(const char* cmd);
};

