#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>

#include "textPrint.h"

int main() {\
    std::string ib;

    if(getuid()) {
        throw std::runtime_error("You should run the program as sudo!");
    }

    tp::printHello();
    tp::div();
    fmt::print("This script will only work if you followed one of the following guides: \nhttps://telegra.ph/osu-low-latency-guide-02-03 [RU] \nhttps://telegra.ph/osu-low-latency-guide-ENG-10-12 [ENG]");
    if(!tp::yn("Do you agree that you followed the guide and take the responsibility on the damage to your system?",'N')) {
        throw std::runtime_error("User did not agree");
    }

    bool amdgpu = tp::yn("AMD GPU [Y] or NVIDIA GPU [n]");
    bool amdcpu = tp::yn("AMD CPU [Y] or INTEL CPU [n]");
    bool linuxzen = tp::yn("linux-zen core [Y] or other [n]");

    if(tp::yn("Do you want to install all osu dependencies [Y], or only configs [n]")) {

        fmt::println("sudo pacman -Sy git go wine winetricks lib32-gnutls lib32-libxcomposite");
        if (system("sudo pacman -Sy git go wine winetricks lib32-gnutls lib32-libxcomposite")!=0) {
            fmt::println("Error occured, skipping...");
        }

        if(amdgpu) {
            fmt::println("sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils");
            if (system("sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils")!=0) {
                fmt::println("Error occured, skipping...");
            }
        }else {
            fmt::println("sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils");
            if (system("sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils")!=0) {
                fmt::println("Error occured, skipping...");
            }
        }

        if (linuxzen) {
            fmt::println("sudo pacman -Sy linux-zen linux-zen-headers");
            if (system("sudo pacman -Sy linux-zen linux-zen-headers")!=0) {
                fmt::println("Error occured, skipping...");
            }
        }

        if (amdcpu) {
            fmt::println("amd-ucode");
            if (system("sudo pacman -Sy amd-ucode")!=0) {
                fmt::println("Error occured, skipping...");
            }
        }else {
            fmt::println("intel-ucode");
            if (system("sudo pacman -Sy intel-ucode")!=0) {
                fmt::println("Error occured, skipping...");
            }
        }
    }

}
