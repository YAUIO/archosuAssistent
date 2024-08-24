#include <fstream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>

#include "textPrint.h"

int main() {\
    std::string ib;
    std::string command;
    std::string username;
    int quantum;
    int sad;
    bool pipms = true;

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
            pipms = tp::yn("Do you have pipewire-media-session [Y] or wireplumber [n] ?");
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
        username = homedir.substr(homedir.find_last_of('/')+1);
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
        }else {
            command = "touch " + homedir + "/.local/bin/osu";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
                tp::err();
            }
        }

        if(tp::yn("Is your CPU worse then Ryzen 5 3700?")) {
            quantum = 128;
            sad = 26666;
        } else {
            quantum = 64;
            sad = 13333;
        }

        fmt::println("Creating osu! startup config");
        std::ofstream bin;
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
export STAGING_AUDIO_DURATION=" + std::to_string(sad) + " #1.333ms at 48KHz\n\
export STAGING_AUDIO_PERIOD=" + std::to_string(sad) + " #1.333ms at 48KHz\n\
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
export STAGING_AUDIO_DURATION=" + std::to_string(sad) + " #1.333ms at 48KHz\n\
export STAGING_AUDIO_PERIOD=" + std::to_string(sad) + " #1.333ms at 48KHz\n\
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
        command = "chmod +x " + homedir + write_to;
        if (system(command.c_str())) {
            tp::err();
        }


        command = "chmod 777 " + homedir + write_to;
        if (system(command.c_str())) {
            tp::err();
        }

        command = "sudo chown  " + username + " " + homedir + write_to;
        if (system(command.c_str())) {
            tp::err();
        }

        std::string bindir = write_to;

        fmt::println("Creating desktop entry");

        fmt::println("mkdir -p ~/.local/share/applications");
        if (system("mkdir -p ~/.local/share/applications") != 0) {
            tp::err();
        }


        command = "ls " + homedir + "/.local/share/applications";
        write_to = "/.local/share/applications/osu.desktop";
        if (tp::execreturn(command.c_str()).contains("osu.desktop")) {
            if(tp::yn("osu! desktop entry. Proceeding will overwrite it. Overwrite?")) {
                command = "rm -f " + homedir + "/.local/share/applications/osu.desktop";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }

                command = "touch " + homedir + "/.local/share/applications/osu.desktop";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }
            } else {
                command = "rm -f " + homedir + "/.local/share/applications/archosu.desktop";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }

                fmt::println("Writing to a different file");
                command = "touch " + homedir + "/.local/share/applications/archosu.desktop";
                write_to = "/.local/share/applications/archosu.desktop";
                fmt::println("{}",command);
                if (system(command.c_str()) != 0) {
                    tp::err();
                }
            }
        }else {
            command = "touch " + homedir + "/.local/share/applications/osu.desktop";
            fmt::println("{}",command);
            if (system(command.c_str()) != 0) {
                tp::err();
            }
        }

        fmt::println("Changing osu! startup config permissions");
        command = "chmod +x " + homedir + write_to;
        if (system(command.c_str())) {
            tp::err();
        }

        command = "chmod 777 " + homedir + write_to;
        if (system(command.c_str())) {
            tp::err();
        }

        command = "sudo chown  " + username + " " + homedir + write_to;
        if (system(command.c_str())) {
            tp::err();
        }

        std::ofstream share;
        share.open(homedir+write_to);
        if(write_to.contains("archosu") && bindir.contains("archosu")) {
            share << "[Desktop Entry]\n\
Type=Application\n\
Comment=archosu!\n\
Exec=.local/bin/archosu\n\
GenericName=archosu!\n\
Name=archosu!\n\
StartupNotify=true";
        }else if (bindir.contains("archosu")) {
            share << "[Desktop Entry]\n\
Type=Application\n\
Comment=osu!\n\
Exec=.local/bin/archosu\n\
GenericName=osu!\n\
Name=osu!\n\
StartupNotify=true";
        } else {
            share << "[Desktop Entry]\n\
Type=Application\n\
Comment=osu!\n\
Exec=.local/bin/osu\n\
GenericName=osu!\n\
Name=osu!\n\
StartupNotify=true";
        }
        share.close();

        tp::div();
        command = "ls " + homedir + "/.local/config/pipewire";
        if (!tp::execreturn(command.c_str()).empty()) {
            if(!tp::yn("Script need to overwrite pipewire configs for osu! to work. Do you agree?")){
                throw std::runtime_error("User did not agree");
            }
        }

        command = "mkdir -p" + homedir + "/.config/pipewire && cp -r /usr/share/pipewire/* " + homedir + "/.config/pipewire/";
        fmt::println("{}",command);
        if (system(command.c_str()) != 0) {
            tp::err();
        }

        if(pipms) {
            std::ofstream alsa;
            alsa.open(homedir + ".config/pipewire/media-session.d/alsa-monitor.conf");
            alsa << "# ALSA monitor config file for PipeWire version 0.4.2 #\n\
#\n\
# Copy and edit this file in /etc/pipewire/media-session.d/\n\
# for system-wide changes or in\n\
# ~/.config/pipewire/media-session.d/ for local changes.\n\
\n\
properties = {\n\
    # Create a JACK device. This is not enabled by default because\n\
    # it requires that the PipeWire JACK replacement libraries are\n\
    # not used by the session manager, in order to be able to\n\
    # connect to the real JACK server.\n\
    #alsa.jack-device = false\n\
\n\
    # Reserve devices.\n\
    #alsa.reserve = true\n\
}\n\
\n\
rules = [\n\
    # An array of matches/actions to evaluate.\n\
    {\n\
        # Rules for matching a device or node. Each dictionary in this array\n\
        # specifies the property to match as key and a string or regex match\n\
        # as value. A successful match requires all dictionary keys (i.e.\n\
        # properties) to match.\n\
        #\n\
        # Actions are are executed for the object if at least one successful\n\
        # match exists.\n\
        #\n\
        # Regular expressions are prefixed with the ~ (tilde) character,\n\
        # otherwise a standard string comparison is used.\n\
        # The special value \"null\" matches against empty properties.\n\
        matches = [\n\
            {\n\
                # This matches all cards. These are regular expressions\n\
                # so \".\" matches one character and \".*\" matches many.\n\
                device.name = \"~alsa_card.*\"\n\
            }\n\
        ]\n\
        actions = {\n\
            # Actions can update properties on the matched object.\n\
            update-props = {\n\
                # Use ALSA-Card-Profile devices. They use UCM or\n\
                # the profile configuration to configure the device\n\
                # and mixer settings.\n\
                api.alsa.use-acp = true\n\
\n\
                # Use UCM instead of profile when available. Can be\n\
                # disabled to skip trying to use the UCM profile.\n\
                #api.alsa.use-ucm = true\n\
\n\
                # Don't use the hardware mixer for volume control. It\n\
                # will only use software volume. The mixer is still used\n\
                # to mute unused paths based on the selected port.\n\
                #api.alsa.soft-mixer = false\n\
\n\
                # Ignore decibel settings of the driver. Can be used to\n\
                # work around buggy drivers that report wrong values.\n\
                #api.alsa.ignore-dB = false\n\
\n\
                # The profile set to use for the device. Usually this is\n\
                # \"default.conf\" but can be changed with a udev rule\n\
                # or here.\n\
                #device.profile-set = \"profileset-name.conf\"\n\
\n\
                # The default active profile. Is by default set to \"Off\".\n\
                #device.profile = \"default profile name\"\n\
\n\
                # Automatically select the best profile. This is the\n\
                # highest priority available profile. This is disabled\n\
                # here and instead implemented in the session manager\n\
                # where it can save and load previous preferences.\n\
                api.acp.auto-profile = false\n\
\n\
                # Automatically switch to the highest priority available\n\
                # port. This is disabled here and implemented in the\n\
                # session manager instead.\n\
                api.acp.auto-port = false\n\
\n\
                # Other properties can be set here.\n\
                #device.nick = \"My Device\"\n\
            }\n\
        }\n\
    }\n\
    {\n\
        matches = [\n\
            {\n\
                # Matches all sources. These are regular expressions\n\
                # so \".\" matches one character and \".*\" matches many.\n\
                node.name = \"~alsa_input.*\"\n\
            }\n\
            {\n\
                # Matches all sinks.\n\
                node.name = \"~alsa_output.*\"\n\
            }\n\
        ]\n\
        actions = {\n\
            update-props = {\n\
                #node.nick                       = \"My Node\"\n\
                #node.nick                       = null\n\
                #priority.driver                 = 100\n\
                #priority.session                = 100\n\
                node.pause-on-idle               = false\n\
                #resample.quality                = 4\n\
                #channelmix.normalize            = false\n\
                #channelmix.mix-lfe              = false\n\
                #audio.channels                  = 2\n\
                #audio.format                    = \"S16LE\"\n\
                #audio.rate                      = 44100\n\
                #audio.position                  = \"FL,FR\"\n\
                session.suspend-timeout-seconds = 0            # 0 disables suspend\n\
                #monitor.channel-volumes         = false\n\
\n\
                #latency.internal.rate = 0            # internal latency in samples\n\
                #latency.internal.ns   = 0            # internal latency in nanoseconds\n\
\n\
                #api.alsa.period-size   = 1024\n\
                #api.alsa.headroom      = 0\n\
                #api.alsa.start-delay   = 0\n\
                #api.alsa.disable-mmap  = false\n\
                #api.alsa.disable-batch = false\n\
                #api.alsa.use-chmap     = false\n\
                #iec958.codecs          = [ PCM DTS AC3 MPEG MPEG2-AAC EAC3 TrueHD DTS-HD ]\n\
            }\n\
        }\n\
    }\n\
]\n\
";
            alsa.close();
        } else {
            std::ofstream wp;
            command = "mkdir -p " + homedir + "/.config/wireplumber && cp -r /usr/share/wireplumber/* " + homedir + "/.config/wireplumber";
            if (system(command.c_str())!=0) {
                tp::err();
            }
            command = "touch " + homedir + "/.config/wireplumber/wireplumber.conf.d/51-disable-suspension.conf";
            if (system(command.c_str())!=0) {
                tp::err();
            }
            wp.open(homedir + "/.config/wireplumber/wireplumber.conf.d/51-disable-suspension.conf");
            wp << "monitor.alsa.rules = [\n\
  {\n\
      matches = [\n\
        {\n\
          # Matches all sources\n\
          node.name = \"~alsa_input.*\"\n\
        },\n\
        {\n\
          # Matches all sinks\n\
          node.name = \"~alsa_output.*\"\n\
        }\n\
      ]\n\
      actions = {\n\
          update-props = {\n\
              session.suspend-timeout-seconds = 0\n\
            }\n\
      }\n\
  }\n\
            ]";
            wp.close();
        }

        std::ofstream pipewire;
        pipewire.open(homedir + "/.config/pipewire/pipewire.conf");
        pipewire << "# Daemon config file for PipeWire version \"1.0.7\" #\n\
#\n\
# Copy and edit this file in /etc/pipewire for system-wide changes\n\
# or in ~/.config/pipewire for local changes.\n\
#\n\
# It is also possible to place a file with an updated section in\n\
# /etc/pipewire/pipewire.conf.d/ for system-wide changes or in\n\
# ~/.config/pipewire/pipewire.conf.d/ for local changes.\n\
#\n\
\n\
context.properties = {\n\
    ## Configure properties in the system.\n\
    #library.name.system                   = support/libspa-support\n\
    #context.data-loop.library.name.system = support/libspa-support\n\
    #support.dbus                          = true\n\
    #link.max-buffers                      = 64\n\
    link.max-buffers                       = 16                       # version < 3 clients can't handle more\n\
    #mem.warn-mlock                        = false\n\
    #mem.allow-mlock                       = true\n\
    #mem.mlock-all                         = false\n\
    #clock.power-of-two-quantum            = true\n\
    #log.level                             = 2\n\
    #cpu.zero.denormals                    = false\n\
\n\
    core.daemon = true              # listening for socket connections\n\
    core.name   = pipewire-0        # core name and socket name\n\
\n\
    ## Properties for the DSP configuration.\n\
    default.clock.rate          = 48000\n\
    #default.clock.allowed-rates = [ 48000 ]\n\
    default.clock.quantum       = " + std::to_string(quantum) + "\n\
    default.clock.min-quantum   = " + std::to_string(quantum) + "\n\
    #default.clock.max-quantum   = 2048\n\
    #default.clock.quantum-limit = 8192\n\
    #default.clock.quantum-floor = 4\n\
    #default.video.width         = 640\n\
    #default.video.height        = 480\n\
    #default.video.rate.num      = 25\n\
    #default.video.rate.denom    = 1\n\
    #\n\
    #settings.check-quantum      = false\n\
    #settings.check-rate         = false\n\
    #\n\
    # These overrides are only applied when running in a vm.\n\
    vm.overrides = {\n\
        default.clock.min-quantum = 1024\n\
    }\n\
\n\
    # keys checked below to disable module loading\n\
    module.x11.bell = true\n\
    # enables autoloading of access module, when disabled an alternative\n\
    # access module needs to be loaded.\n\
    module.access = true\n\
    # enables autoloading of module-jackdbus-detect\n\
    module.jackdbus-detect = true\n\
}\n\
\n\
context.spa-libs = {\n\
    #<factory-name regex> = <library-name>\n\
    #\n\
    # Used to find spa factory names. It maps an spa factory name\n\
    # regular expression to a library name that should contain\n\
    # that factory.\n\
    #\n\
    audio.convert.* = audioconvert/libspa-audioconvert\n\
    avb.*           = avb/libspa-avb\n\
    api.alsa.*      = alsa/libspa-alsa\n\
    api.v4l2.*      = v4l2/libspa-v4l2\n\
    api.libcamera.* = libcamera/libspa-libcamera\n\
    api.bluez5.*    = bluez5/libspa-bluez5\n\
    api.vulkan.*    = vulkan/libspa-vulkan\n\
    api.jack.*      = jack/libspa-jack\n\
    support.*       = support/libspa-support\n\
    #videotestsrc   = videotestsrc/libspa-videotestsrc\n\
    #audiotestsrc   = audiotestsrc/libspa-audiotestsrc\n\
}\n\
\n\
context.modules = [\n\
    #{ name = <module-name>\n\
    #    ( args  = { <key> = <value> ... } )\n\
    #    ( flags = [ ( ifexists ) ( nofail ) ] )\n\
    #    ( condition = [ { <key> = <value> ... } ... ] )\n\
    #}\n\
    #\n\
    # Loads a module with the given parameters.\n\
    # If ifexists is given, the module is ignored when it is not found.\n\
    # If nofail is given, module initialization failures are ignored.\n\
    # If condition is given, the module is loaded only when the context\n\
    # properties all match the match rules.\n\
    #\n\
\n\
    # Uses realtime scheduling to boost the audio thread priorities. This uses\n\
    # RTKit if the user doesn't have permission to use regular realtime\n\
    # scheduling. You can also clamp utilisation values to improve scheduling\n\
    # on embedded and heterogeneous systems, e.g. Arm big.LITTLE devices.\n\
    { name = libpipewire-module-rt\n\
        args = {\n\
            nice.level    = -11\n\
            rt.prio       = 88\n\
            #rt.time.soft = -1\n\
            #rt.time.hard = -1\n\
            #uclamp.min = 0\n\
            #uclamp.max = 1024\n\
        }\n\
        flags = [ ifexists nofail ]\n\
    }\n\
\n\
    # The native communication protocol.\n\
    { name = libpipewire-module-protocol-native\n\
        args = {\n\
            # List of server Unix sockets, and optionally permissions\n\
            #sockets = [ { name = \"pipewire-0\" }, { name = \"pipewire-0-manager\" } ]\n\
        }\n\
    }\n\
\n\
    # The profile module. Allows application to access profiler\n\
    # and performance data. It provides an interface that is used\n\
    # by pw-top and pw-profiler.\n\
    { name = libpipewire-module-profiler }\n\
\n\
    # Allows applications to create metadata objects. It creates\n\
    # a factory for Metadata objects.\n\
    { name = libpipewire-module-metadata }\n\
\n\
    # Creates a factory for making devices that run in the\n\
    # context of the PipeWire server.\n\
    { name = libpipewire-module-spa-device-factory }\n\
\n\
    # Creates a factory for making nodes that run in the\n\
    # context of the PipeWire server.\n\
    { name = libpipewire-module-spa-node-factory }\n\
\n\
    # Allows creating nodes that run in the context of the\n\
    # client. Is used by all clients that want to provide\n\
    # data to PipeWire.\n\
    { name = libpipewire-module-client-node }\n\
\n\
    # Allows creating devices that run in the context of the\n\
    # client. Is used by the session manager.\n\
    { name = libpipewire-module-client-device }\n\
\n\
    # The portal module monitors the PID of the portal process\n\
    # and tags connections with the same PID as portal\n\
    # connections.\n\
    { name = libpipewire-module-portal\n\
        flags = [ ifexists nofail ]\n\
    }\n\
\n\
    # The access module can perform access checks and block\n\
    # new clients.\n\
    { name = libpipewire-module-access\n\
        args = {\n\
            # Socket-specific access permissions\n\
            #access.socket = { pipewire-0 = \"default\", pipewire-0-manager = \"unrestricted\" }\n\
\n\
            # Deprecated legacy mode (not socket-based),\n\
            # for now enabled by default if access.socket is not specified\n\
            #access.legacy = true\n\
        }\n\
        condition = [ { module.access = true } ]\n\
    }\n\
\n\
    # Makes a factory for wrapping nodes in an adapter with a\n\
    # converter and resampler.\n\
    { name = libpipewire-module-adapter }\n\
\n\
    # Makes a factory for creating links between ports.\n\
    { name = libpipewire-module-link-factory }\n\
\n\
    # Provides factories to make session manager objects.\n\
    { name = libpipewire-module-session-manager }\n\
\n\
    # Use libcanberra to play X11 Bell\n\
    { name = libpipewire-module-x11-bell\n\
        args = {\n\
            #sink.name = \"@DEFAULT_SINK@\"\n\
            #sample.name = \"bell-window-system\"\n\
            #x11.display = null\n\
            #x11.xauthority = null\n\
        }\n\
        flags = [ ifexists nofail ]\n\
        condition = [ { module.x11.bell = true } ]\n\
    }\n\
    { name = libpipewire-module-jackdbus-detect\n\
        args = {\n\
            #jack.library     = libjack.so.0\n\
            #jack.server      = null\n\
            #jack.client-name = PipeWire\n\
            #jack.connect     = true\n\
            #tunnel.mode      = duplex  # source|sink|duplex\n\
            source.props = {\n\
                #audio.channels = 2\n\
		#midi.ports = 1\n\
                #audio.position = [ FL FR ]\n\
                # extra sink properties\n\
            }\n\
            sink.props = {\n\
                #audio.channels = 2\n\
		#midi.ports = 1\n\
                #audio.position = [ FL FR ]\n\
                # extra sink properties\n\
            }\n\
        }\n\
        flags = [ ifexists nofail ]\n\
        condition = [ { module.jackdbus-detect = true } ]\n\
    }\n\
]\n\
\n\
context.objects = [\n\
    #{ factory = <factory-name>\n\
    #    ( args  = { <key> = <value> ... } )\n\
    #    ( flags = [ ( nofail ) ] )\n\
    #    ( condition = [ { <key> = <value> ... } ... ] )\n\
    #}\n\
    #\n\
    # Creates an object from a PipeWire factory with the given parameters.\n\
    # If nofail is given, errors are ignored (and no object is created).\n\
    # If condition is given, the object is created only when the context properties\n\
    # all match the match rules.\n\
    #\n\
    #{ factory = spa-node-factory   args = { factory.name = videotestsrc node.name = videotestsrc node.description = videotestsrc \"Spa:Pod:Object:Param:Props:patternType\" = 1 } }\n\
    #{ factory = spa-device-factory args = { factory.name = api.jack.device foo=bar } flags = [ nofail ] }\n\
    #{ factory = spa-device-factory args = { factory.name = api.alsa.enum.udev } }\n\
    #{ factory = spa-node-factory   args = { factory.name = api.alsa.seq.bridge node.name = Internal-MIDI-Bridge } }\n\
    #{ factory = adapter            args = { factory.name = audiotestsrc node.name = my-test node.description = audiotestsrc } }\n\
    #{ factory = spa-node-factory   args = { factory.name = api.vulkan.compute.source node.name = my-compute-source } }\n\
\n\
    # A default dummy driver. This handles nodes marked with the \"node.always-process\"\n\
    # property when no other driver is currently active. JACK clients need this.\n\
    { factory = spa-node-factory\n\
        args = {\n\
            factory.name    = support.node.driver\n\
            node.name       = Dummy-Driver\n\
            node.group      = pipewire.dummy\n\
            priority.driver = 20000\n\
            #clock.id       = monotonic # realtime | tai | monotonic-raw | boottime\n\
            #clock.name     = \"clock.system.monotonic\"\n\
        }\n\
    }\n\
    { factory = spa-node-factory\n\
        args = {\n\
            factory.name    = support.node.driver\n\
            node.name       = Freewheel-Driver\n\
            priority.driver = 19000\n\
            node.group      = pipewire.freewheel\n\
            node.freewheel  = true\n\
        }\n\
    }\n\
\n\
    # This creates a new Source node. It will have input ports\n\
    # that you can link, to provide audio for this source.\n\
    #{ factory = adapter\n\
    #    args = {\n\
    #        factory.name     = support.null-audio-sink\n\
    #        node.name        = \"my-mic\"\n\
    #        node.description = \"Microphone\"\n\
    #        media.class      = \"Audio/Source/Virtual\"\n\
    #        audio.position   = \"FL,FR\"\n\
    #        monitor.passthrough = true\n\
    #    }\n\
    #}\n\
\n\
    # This creates a single PCM source device for the given\n\
    # alsa device path hw:0. You can change source to sink\n\
    # to make a sink in the same way.\n\
    #{ factory = adapter\n\
    #    args = {\n\
    #        factory.name           = api.alsa.pcm.source\n\
    #        node.name              = \"alsa-source\"\n\
    #        node.description       = \"PCM Source\"\n\
    #        media.class            = \"Audio/Source\"\n\
    #        api.alsa.path          = \"hw:0\"\n\
    #        api.alsa.period-size   = 1024\n\
    #        api.alsa.headroom      = 0\n\
    #        api.alsa.disable-mmap  = false\n\
    #        api.alsa.disable-batch = false\n\
    #        audio.format           = \"S16LE\"\n\
    #        audio.rate             = 48000\n\
    #        audio.channels         = 2\n\
    #        audio.position         = \"FL,FR\"\n\
    #    }\n\
    #}\n\
\n\
    # Use the metadata factory to create metadata and some default values.\n\
    #{ factory = metadata\n\
    #    args = {\n\
    #        metadata.name = my-metadata\n\
    #        metadata.values = [\n\
    #            { key = default.audio.sink   value = { name = somesink } }\n\
    #            { key = default.audio.source value = { name = somesource } }\n\
    #        ]\n\
    #    }\n\
    #}\n\
]\n\
\n\
context.exec = [\n\
    #{   path = <program-name>\n\
    #    ( args = \"<arguments>\" )\n\
    #    ( condition = [ { <key> = <value> ... } ... ] )\n\
    #}\n\
    #\n\
    # Execute the given program with arguments.\n\
    # If condition is given, the program is executed only when the context\n\
    # properties all match the match rules.\n\
    #\n\
    # You can optionally start the session manager here,\n\
    # but it is better to start it as a systemd service.\n\
    # Run the session manager with -h for options.\n\
    #\n\
    #{ path = \"/usr/bin/pipewire-media-session\" args = \"\"\n\
    #  condition = [ { exec.session-manager = null } { exec.session-manager = true } ] }\n\
    #\n\
    # You can optionally start the pulseaudio-server here as well\n\
    # but it is better to start it as a systemd service.\n\
    # It can be interesting to start another daemon here that listens\n\
    # on another address with the -a option (eg. -a tcp:4713).\n\
    #\n\
    #{ path = \"/usr/bin/pipewire\" args = \"-c pipewire-pulse.conf\"\n\
    #  condition = [ { exec.pipewire-pulse = null } { exec.pipewire-pulse = true } ] }\n\
]";
        pipewire.close();

        std::ofstream pipulse;
        pipulse.open(homedir + "/.config/pipewire/pipewire-pulse.conf");
        pipulse << "# PulseAudio config file for PipeWire version \"1.0.7\" #\n\
#\n\
# Copy and edit this file in /etc/pipewire for system-wide changes\n\
# or in ~/.config/pipewire for local changes.\n\
#\n\
# It is also possible to place a file with an updated section in\n\
# /etc/pipewire/pipewire-pulse.conf.d/ for system-wide changes or in\n\
# ~/.config/pipewire/pipewire-pulse.conf.d/ for local changes.\n\
#\n\
\n\
context.properties = {\n\
    ## Configure properties in the system.\n\
    #mem.warn-mlock  = false\n\
    #mem.allow-mlock = true\n\
    #mem.mlock-all   = false\n\
    #log.level       = 2\n\
\n\
    #default.clock.quantum-limit = 8192\n\
}\n\
\n\
context.spa-libs = {\n\
    audio.convert.* = audioconvert/libspa-audioconvert\n\
    support.*       = support/libspa-support\n\
}\n\
\n\
context.modules = [\n\
    { name = libpipewire-module-rt\n\
        args = {\n\
            nice.level   = -11\n\
            #rt.prio      = 83\n\
            #rt.time.soft = -1\n\
            #rt.time.hard = -1\n\
            #uclamp.min = 0\n\
            #uclamp.max = 1024\n\
        }\n\
        flags = [ ifexists nofail ]\n\
    }\n\
    { name = libpipewire-module-protocol-native }\n\
    { name = libpipewire-module-client-node }\n\
    { name = libpipewire-module-adapter }\n\
    { name = libpipewire-module-metadata }\n\
\n\
    { name = libpipewire-module-protocol-pulse\n\
        args = {\n\
	    # contents of pulse.properties can also be placed here\n\
	    # to have config per server.\n\
        }\n\
    }\n\
]\n\
\n\
# Extra scripts can be started here. Setup in default.pa can be moved in\n\
# a script or in pulse.cmd below\n\
context.exec = [\n\
    #{ path = \"pactl\"        args = \"load-module module-always-sink\" }\n\
    #{ path = \"pactl\"        args = \"upload-sample my-sample.wav my-sample\" }\n\
    #{ path = \"/usr/bin/sh\"  args = \"~/.config/pipewire/default.pw\" }\n\
]\n\
\n\
# Extra commands can be executed here.\n\
#   load-module : loads a module with args and flags\n\
#      args = \"<module-name> <module-args>\"\n\
#      ( flags = [ nofail ] )\n\
pulse.cmd = [\n\
    { cmd = \"load-module\" args = \"module-always-sink\" flags = [ ] }\n\
    #{ cmd = \"load-module\" args = \"module-switch-on-connect\" }\n\
    #{ cmd = \"load-module\" args = \"module-gsettings\" flags = [ nofail ] }\n\
]\n\
\n\
stream.properties = {\n\
    node.latency          = " + std::to_string(quantum) + "/48000\n\
    #node.autoconnect      = true\n\
    #resample.quality      = 4\n\
    #channelmix.normalize  = false\n\
    #channelmix.mix-lfe    = true\n\
    #channelmix.upmix      = true\n\
    #channelmix.upmix-method = psd  # none, simple\n\
    #channelmix.lfe-cutoff = 150\n\
    #channelmix.fc-cutoff  = 12000\n\
    #channelmix.rear-delay = 12.0\n\
    #channelmix.stereo-widen = 0.0\n\
    #channelmix.hilbert-taps = 0\n\
    #dither.noise = 0\n\
}\n\
\n\
pulse.properties = {\n\
    # the addresses this server listens on\n\
    server.address = [\n\
        \"unix:native\"\n\
        #\"unix:/tmp/something\"              # absolute paths may be used\n\
        #\"tcp:4713\"                         # IPv4 and IPv6 on all addresses\n\
        #\"tcp:[::]:9999\"                    # IPv6 on all addresses\n\
        #\"tcp:127.0.0.1:8888\"               # IPv4 on a single address\n\
        #\n\
        #{ address = \"tcp:4713\"             # address\n\
        #  max-clients = 64                 # maximum number of clients\n\
        #  listen-backlog = 32              # backlog in the server listen queue\n\
        #  client.access = \"restricted\"     # permissions for clients\n\
        #}\n\
    ]\n\
    #server.dbus-name       = \"org.pulseaudio.Server\"\n\
    pulse.min.req          = " + std::to_string(quantum) + "/48000     # 2.7ms\n\
    pulse.default.req      = " + std::to_string(quantum) + "/48000     # 20 milliseconds\n\
    pulse.min.frag         = " + std::to_string(quantum) + "/48000     # 2.7ms\n\
    #pulse.default.frag     = 96000/48000   # 2 seconds\n\
    #pulse.default.tlength  = 96000/48000   # 2 seconds\n\
    pulse.min.quantum      = " + std::to_string(quantum) + "/48000     # 2.7ms\n\
    #pulse.idle.timeout     = 0             # don't pause after underruns\n\
    #pulse.default.format   = F32\n\
    #pulse.default.position = [ FL FR ]\n\
    # These overrides are only applied when running in a vm.\n\
    vm.overrides = {\n\
        pulse.min.quantum = 1024/48000      # 22ms\n\
    }\n\
}\n\
\n\
# client/stream specific properties\n\
pulse.rules = [\n\
    {\n\
        matches = [\n\
            {\n\
                # all keys must match the value. ! negates. ~ starts regex.\n\
                #client.name                = \"Firefox\"\n\
                #application.process.binary = \"teams\"\n\
                #application.name           = \"~speech-dispatcher.*\"\n\
            }\n\
        ]\n\
        actions = {\n\
            update-props = {\n\
                #node.latency = 512/48000\n\
            }\n\
            # Possible quirks:\"\n\
            #    force-s16-info                 forces sink and source info as S16 format\n\
            #    remove-capture-dont-move       removes the capture DONT_MOVE flag\n\
            #    block-source-volume            blocks updates to source volume\n\
            #    block-sink-volume              blocks updates to sink volume\n\
            #quirks = [ ]\n\
        }\n\
    }\n\
    {\n\
        # skype does not want to use devices that don't have an S16 sample format.\n\
        matches = [\n\
             { application.process.binary = \"teams\" }\n\
             { application.process.binary = \"teams-insiders\" }\n\
             { application.process.binary = \"skypeforlinux\" }\n\
        ]\n\
        actions = { quirks = [ force-s16-info ] }\n\
    }\n\
    {\n\
        # firefox marks the capture streams as don't move and then they\n\
        # can't be moved with pavucontrol or other tools.\n\
        matches = [ { application.process.binary = \"firefox\" } ]\n\
        actions = { quirks = [ remove-capture-dont-move ] }\n\
    }\n\
    {\n\
        # speech dispatcher asks for too small latency and then underruns.\n\
        matches = [ { application.name = \"~speech-dispatcher.*\" } ]\n\
        actions = {\n\
            update-props = {\n\
                pulse.min.req          = 512/48000      # 10.6ms\n\
                pulse.min.quantum      = 512/48000      # 10.6ms\n\
                pulse.idle.timeout     = 5              # pause after 5 seconds of underrun\n\
            }\n\
        }\n\
    }\n\
    #{\n\
    #    matches = [ { application.process.binary = \"Discord\" } ]\n\
    #    actions = { quirks = [ block-source-volume ] }\n\
    #}\n\
]";
        if (system("systemctl --user restart pipewire.service pipewire.socket pipewire-pulse.service pipewire-pulse.socket")!=0) {
            tp::err();
        }

        if(pipms) {
            if (system("systemctl --user restart pipewire-media-session.service")!=0) {
                tp::err();
            }
        }else {
            if (system("systemctl --user restart wireplumber.service")!=0) {
                tp::err();
            }
        }

        tp::div();

        fmt::println("Audio configs are all written.");

        if(tp::yn("Install osu!")) {
            command = "mkdir -p " + homedir + "/osu/";
            if (system(command.c_str())!=0) {
                tp::err();
            }

            command = "wget --output-document " + homedir + "/osu/osu\\!.exe https://m1.ppy.sh/r/osu\\!install.exe";
            if (system(command.c_str())!=0) {
                tp::err();
            }

            if(tp::yn("You need to press" + fmt::format(fmt::fg(fmt::color::red),"NO") + "on \"install mono?\" dialog, otherwise osu! " + fmt::format(fmt::fg(fmt::color::red),"WON'T WORK PROPERLY")),'N') {
                command = "rm -rf " + homedir + "/.wineosu";
                if (system(command.c_str())!=0) {
                    tp::err();
                }

                command = "WINEARCH=win32 WINEPREFIX=" + homedir + "/.wineosu winetricks dotnet45 cjkfonts gdiplus";
                if (system(command.c_str())!=0) {
                    tp::err();
                }
            }
        }

    }
}
