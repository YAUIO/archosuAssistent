#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>

#include "textPrint.h"

int main() {\
    std::string ib;
    std::string command;

    if (getuid()) {
        throw std::runtime_error("You should run the program as sudo!");
    }

    tp::printHello();
    tp::div();
    fmt::print(
        "This script will only work if you followed one of the following guides: \nhttps://telegra.ph/osu-low-latency-guide-02-03 [RU] \nhttps://telegra.ph/osu-low-latency-guide-ENG-10-12 [ENG]");
    if (!tp::yn("Do you agree that you followed the guide and take the responsibility on the damage to your system?",
                'N')) {
        throw std::runtime_error("User did not agree");
    }

    if (tp::yn("Do you want to install all osu dependencies [Y], or only configs [n]")) {

        bool amdgpu = tp::yn("AMD GPU [Y] or NVIDIA GPU [n]");
        bool amdcpu = tp::yn("AMD CPU [Y] or INTEL CPU [n]");
        bool linuxzen = tp::yn("linux-zen core [Y] or other [n]");

        if (!tp::yn("Do you have pipewire installed?")) {
            fmt::println(
                "sudo pacman -Sy pavucontrol pipewire pipewire-alsa pipewire-audio pipewire-jack pipewire-media-session pipewire-pulse libpipewire lib32-pipewire lib32-libpipewire gst-plugin-pipewire");
            if (system(
                    "sudo pacman -Sy pavucontrol pipewire pipewire-alsa pipewire-audio pipewire-jack pipewire-media-session pipewire-pulse libpipewire lib32-pipewire lib32-libpipewire gst-plugin-pipewire")
                != 0) {
                tp::err();
            }
        } else {
            bool pipms = tp::yn("Do you have pipewire-media-session [Y] or wireplumber [n] ?");
        }

        fmt::println("sudo pacman -Sy git go winetricks lib32-libxcomposite wine giflib lib32-giflib libpng lib32-libpng libldap lib32-libldap gnutls lib32-gnutls \
mpg123 lib32-mpg123 openal lib32-openal v4l-utils lib32-v4l-utils libpulse lib32-libpulse libgpg-error \
lib32-libgpg-error alsa-plugins lib32-alsa-plugins alsa-lib lib32-alsa-lib libjpeg-turbo lib32-libjpeg-turbo \
sqlite lib32-sqlite libxcomposite lib32-libxcomposite libxinerama lib32-libgcrypt libgcrypt lib32-libxinerama \
ncurses lib32-ncurses opencl-icd-loader lib32-opencl-icd-loader libxslt lib32-libxslt libva lib32-libva gtk3 \
lib32-gtk3 gst-plugins-base-libs lib32-gst-plugins-base-libs vulkan-icd-loader lib32-vulkan-icd-loader");
        if (system("sudo pacman -Sy git go winetricks lib32-libxcomposite wine giflib lib32-giflib libpng lib32-libpng libldap lib32-libldap gnutls lib32-gnutls \
mpg123 lib32-mpg123 openal lib32-openal v4l-utils lib32-v4l-utils libpulse lib32-libpulse libgpg-error \
lib32-libgpg-error alsa-plugins lib32-alsa-plugins alsa-lib lib32-alsa-lib libjpeg-turbo lib32-libjpeg-turbo \
sqlite lib32-sqlite libxcomposite lib32-libxcomposite libxinerama lib32-libgcrypt libgcrypt lib32-libxinerama \
ncurses lib32-ncurses opencl-icd-loader lib32-opencl-icd-loader libxslt lib32-libxslt libva lib32-libva gtk3 \
lib32-gtk3 gst-plugins-base-libs lib32-gst-plugins-base-libs vulkan-icd-loader lib32-vulkan-icd-loader") != 0) {
            tp::err();
        }

        if (amdgpu) {
            fmt::println("sudo pacman -Sy vulkan-radeon libva-mesa-driver xf86-video-ati xf86-video-amdgpu mesa");
            if (system("sudo pacman -Sy vulkan-radeon libva-mesa-driver xf86-video-ati xf86-video-amdgpu mesa") != 0) {
                tp::err();
            }
        } else {
            fmt::println("sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils");
            if (system("sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils") != 0) {
                tp::err();
            }
        }

        if (linuxzen) {
            fmt::println("sudo pacman -Sy linux-zen linux-zen-headers");
            if (system("sudo pacman -Sy linux-zen linux-zen-headers") != 0) {
                tp::err();
            }
        }

        if (amdcpu) {
            fmt::println("sudo pacman -Sy amd-ucode");
            if (system("sudo pacman -Sy amd-ucode") != 0) {
                tp::err();
            }
        } else {
            fmt::println("sudo pacman -Sy intel-ucode");
            if (system("sudo pacman -Sy intel-ucode") != 0) {
                tp::err();
            }
        }
    }

    std::string homedir;

    try {
        homedir = tp::execreturn("getent passwd $SUDO_USER | cut -d: -f6");
    }catch(std::exception & e) {
        tp::err(e.what());
        tp::err("Can't create configs!");
    }

    if(!homedir.empty()) {
        command = "mkdir -p " + homedir + "/.local/bin/";
        fmt::println("{}",command);
        if (system(command.c_str()) != 0) {
            tp::err();
        }


        command = "touch " + homedir + "/.local/bin/osu";
        fmt::println("{}",command);
        if (system(command.c_str()) != 0) {
            tp::err();
        }

        fmt::println("mkdir -p ~/.local/share/applications");
        if (system("mkdir -p ~/.local/share/applications") != 0) {
            tp::err();
        }

        fmt::println("touch ~/.local/share/applications/osu");
        if (system("touch ~/.local/share/applications/osu") != 0) {
            tp::err();
        }
    }
}
