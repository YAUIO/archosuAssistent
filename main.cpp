#include <fstream>
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

    bool amdgpu = tp::yn("AMD GPU [Y] or NVIDIA GPU [n]");

    if (tp::yn("Do you want to install all osu dependencies [Y], or only configs [n]")) {

        bool amdcpu = tp::yn("AMD CPU [Y] or INTEL CPU [n]");
        bool linuxzen = tp::yn("linux-zen core [Y] or other [n]");

        if (!tp::yn("Do you have pipewire installed?")) {
            command = "sudo pacman -Sy pavucontrol pipewire pipewire-alsa pipewire-audio pipewire-jack pipewire-media-session pipewire-pulse libpipewire lib32-pipewire lib32-libpipewire gst-plugin-pipewire";
            fmt::println("{}",command);
            if (system(command.c_str())!= 0) {
                tp::err();
            }
        } else {
            bool pipms = tp::yn("Do you have pipewire-media-session [Y] or wireplumber [n] ?");
        }

        command = "sudo pacman -Sy git go winetricks lib32-libxcomposite wine giflib lib32-giflib libpng lib32-libpng libldap lib32-libldap gnutls lib32-gnutls \
mpg123 lib32-mpg123 openal lib32-openal v4l-utils lib32-v4l-utils libpulse lib32-libpulse libgpg-error \
lib32-libgpg-error alsa-plugins lib32-alsa-plugins alsa-lib lib32-alsa-lib libjpeg-turbo lib32-libjpeg-turbo \
sqlite lib32-sqlite libxcomposite lib32-libxcomposite libxinerama lib32-libgcrypt libgcrypt lib32-libxinerama \
ncurses lib32-ncurses opencl-icd-loader lib32-opencl-icd-loader libxslt lib32-libxslt libva lib32-libva gtk3 \
lib32-gtk3 gst-plugins-base-libs lib32-gst-plugins-base-libs vulkan-icd-loader lib32-vulkan-icd-loader";
        fmt::println("{}",command);
        if (system(command.c_str()) != 0) {
            tp::err();
        }

        if (amdgpu) {
            command = "sudo pacman -Sy vulkan-radeon libva-mesa-driver xf86-video-ati xf86-video-amdgpu mesa lib32-mesa";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
                tp::err();
            }
        } else {
            command = "sudo pacman -Sy nvidia-dkms nvidia-settings nvidia-utils lib32-nvidia-utils";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
                tp::err();
            }
        }

        if (linuxzen) {
            command = "sudo pacman -Sy linux-zen linux-zen-headers";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
                tp::err();
            }
        }

        if (amdcpu) {
            command = "sudo pacman -Sy amd-ucode";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
                tp::err();
            }
        } else {
            command = "sudo pacman -Sy intel-ucode";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
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

        command = "ls " + homedir + "/.local/bin";
        std::string write_to = "/.local/bin/osu";
        if (tp::execreturn(command.c_str()).contains("osu")) {
            if(tp::yn("osu! launch script exists. Proceeding will overwrite it. Overwrite?")) {
                command = "rm -f " + homedir + "/.local/bin/osu";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }

                command = "touch " + homedir + "/.local/bin/osu";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }
            } else {
                command = "rm -f " + homedir + "/.local/bin/archosu";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }

                fmt::println("Writing to a different file");
                command = "touch " + homedir + "/.local/bin/archosu";
                write_to = "/.local/bin/archosu";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }
            }
        }

        fmt::println("Creating osu! startup config");
        std::fstream bin;
        bin.open(homedir+write_to);
        if (amdgpu) {
            bin << "#!/usr/bin/env bash\n\
#export PATH=\"/opt/wine-osu/bin:$PATH\" #custom WINE ArchLinux\n\
export PATH=\"$HOME/wine-osu/bin:$PATH\" #custom WINE new\n\
\n\
export WINEARCH=win32\n\
export WINEPREFIX=\"$HOME/.wineosu\"\n\
export WINEFSYNC=1\n\
\n\
export STAGING_AUDIO_DURATION=13333 #1.333ms at 48KHz\n\
export STAGING_AUDIO_PERIOD=13333 #1.333ms at 48KHz\n\
\n\
export vblank_mode=0 #For AMD, Intel and others\n\
#export __GL_SYNC_TO_VBLANK=0 #For NVIDIA \n\
\n\
cd ~/osu\n\
#wine --version\n\
wine \"osu!.exe\" #-devserver gatari.pw";
        }else {
            bin << "#!/usr/bin/env bash\n\
#export PATH=\"/opt/wine-osu/bin:$PATH\" #custom WINE ArchLinux\n\
export PATH=\"$HOME/wine-osu/bin:$PATH\" #custom WINE new\n\
\n\
export WINEARCH=win32\n\
export WINEPREFIX=\"$HOME/.wineosu\"\n\
export WINEFSYNC=1\n\
\n\
export STAGING_AUDIO_DURATION=13333 #1.333ms at 48KHz\n\
export STAGING_AUDIO_PERIOD=13333 #1.333ms at 48KHz\n\
\n\
#export vblank_mode=0 #For AMD, Intel and others\n\
export __GL_SYNC_TO_VBLANK=0 #For NVIDIA \n\
\n\
cd ~/osu\n\
#wine --version\n\
wine \"osu!.exe\" #-devserver gatari.pw";;
        }
        bin.close();
        fmt::println("Changing osu! startup config permissions");
        command = "chmod 777 " + homedir + write_to;
        if (system(command.c_str())) {
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
