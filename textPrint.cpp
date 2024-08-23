#include "textPrint.h"

void tp::printHello() {
    auto greeting = fmt::format(fmt::fg(fmt::color::red),
                           "\n--     ,---,        ,-.----.      ,----..         ,--.\'|    /   /   \\     .--.--.                        ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::red),
                           "\n--    \'  .\' \\       \\    /  \\    /   /   \\     ,--,  | :   /   .     :   /  /    \'.           ,--,  ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::orange),
                           "\n--   /  ;    \'.     ;   :    \\  |   :     : ,---.\'|  : \'  .   /   ;.  \\ |  :  /`. /         ,\'_ /|   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::orange),
                           "\n--  :  :       \\    |   | .\\ :  .   |  ;. / |   | : _\' | .   ;   /  ` ; ;  |  |--`     .--. |  | :      ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::yellow),
                           "\n--  :  |   /\\   \\   .   : |: |  .   ; /--`  :   : |.\'  | ;   |  ; \\ ; | |  :  ;_     ,\'_ /| :  . |    ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::yellow),
                           "\n--  |  :  \' ;.   :  |   |  \\ :  ;   | ;     |   \' \'  ; : |   :  | ; | \'  \\  \\    `.  |  \' | |  . . ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::green),
                           "\n--  |  |  ;/  \\   \\ |   : .  /  |   : |     \'   |  .\'. | .   |  \' \' \' :   `----.   \\ |  | \' |  | | ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::green),
                           "\n--  \'  :  | \\  \\ ,\' ;   | |  \\  .   | \'___  |   | :  | \' \'   ;  \\; /  |   __ \\  \\  | :  | | :  \' ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::cyan),
                           "\n--  |  |  \'  \'--\'   |   | ;\\  \\ \'   ; : .\'| \'   : |  : ;  \\   \\  \',  /   /  /`--\'  / |  ; \' |  | \'  ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::cyan),
                           "\n--  |  :  :         :   \' | \\.\' \'   | \'/  : |   | \'  ,/    ;   :    /   \'--\'.     /  :  | : ;  ; |   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::blue),
                           "\n--  |  | ,\'         :   : :-\'   |   :    /  ;   : ;--\'      \\   \\ .\'      `--\'---\'   \'  :  `--\'   \\ ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::blue),
                           "\n--  `--\'           |   |.\'      \\   \\ .\'   |   ,/           `---`                   :  ,      .-./        ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::purple),
                           "\n--                  `---\'         `---`     \'---\'                                     `--`----\'              ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::purple),
                           "\n--                                                                                                                                                                                                                                      ");
    fmt::print("{}", greeting);

    greeting = fmt::format(fmt::fg(fmt::color::deep_pink),"\nby Vudek and Yudek");
    fmt::println("{}",greeting);
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void tp::printHelloBig() {
    //big greeting
    auto greeting = fmt::format(fmt::fg(fmt::color::red),
                                "\n--     ,---,        ,-.----.      ,----..         ,--.\'|    /   /   \\     .--.--.                              ,---,          .--.--.      .--.--.       ,---,   .--.--.        ,`   .\'  :    ,---,               ,--.\'|     ,`   .\'  : ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::red),
                           "\n--    \'  .\' \\       \\    /  \\    /   /   \\     ,--,  | :   /   .     :   /  /    \'.           ,--,            \'  .\' \\        /  /    \'.   /  /    \'.  ,`--.\' |  /  /    \'.    ;    ;     /   \'  .\' \\          ,--,:  : |   ;    ;     / ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::orange),
                           "\n--   /  ;    \'.     ;   :    \\  |   :     : ,---.\'|  : \'  .   /   ;.  \\ |  :  /`. /         ,\'_ /|           /  ;    \'.     |  :  /`. /  |  :  /`. /  |   :  : |  :  /`. /  .\'___,/    ,\'   /  ;    \'.     ,`--.\'`|  \' : .\'___,/    ,\'  ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::orange),
                           "\n--  :  :       \\    |   | .\\ :  .   |  ;. / |   | : _\' | .   ;   /  ` ; ;  |  |--`     .--. |  | :          :  :       \\    ;  |  |--`   ;  |  |--`   :   |  \' ;  |  |--`   |    :     |   :  :       \\    |   :  :  | | |    :     |   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::yellow),
                           "\n--  :  |   /\\   \\   .   : |: |  .   ; /--`  :   : |.\'  | ;   |  ; \\ ; | |  :  ;_     ,\'_ /| :  . |          :  |   /\\   \\   |  :  ;_     |  :  ;_     |   :  | |  :  ;_     ;    |.\';  ;   :  |   /\\   \\   :   |   \\ | : ;    |.\';  ;   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::yellow),
                           "\n--  |  :  \' ;.   :  |   |  \\ :  ;   | ;     |   \' \'  ; : |   :  | ; | \'  \\  \\    `.  |  \' | |  . .          |  :  \' ;.   :   \\  \\    `.   \\  \\    `.  \'   \'  ;  \\  \\    `.  `----\'  |  |   |  :  \' ;.   :  |   : \'  \'; | `----\'  |  |   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::green),
                           "\n--  |  |  ;/  \\   \\ |   : .  /  |   : |     \'   |  .\'. | .   |  \' \' \' :   `----.   \\ |  | \' |  | |          |  |  ;/  \\   \\   `----.   \\   `----.   \\ |   |  |   `----.   \\     \'   :  ;   |  |  ;/  \\   \\ \'   \' ;.    ;     \'   :  ;   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::green),
                           "\n--  \'  :  | \\  \\ ,\' ;   | |  \\  .   | \'___  |   | :  | \' \'   ;  \\; /  |   __ \\  \\  | :  | | :  \' ;          \'  :  | \\  \\ ,\'   __ \\  \\  |   __ \\  \\  | \'   :  ;   __ \\  \\  |     |   |  \'   \'  :  | \\  \\ ,\' |   | | \\   |     |   |  \'   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::cyan),
                           "\n--  |  |  \'  \'--\'   |   | ;\\  \\ \'   ; : .\'| \'   : |  : ;  \\   \\  \',  /   /  /`--\'  / |  ; \' |  | \'          |  |  \'  \'--\'    /  /`--\'  /  /  /`--\'  / |   |  \'  /  /`--\'  /     \'   :  |   |  |  \'  \'--\'   \'   : |  ; .\'     \'   :  |   ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::cyan),
                           "\n--  |  :  :         :   \' | \\.\' \'   | \'/  : |   | \'  ,/    ;   :    /   \'--\'.     /  :  | : ;  ; |          |  :  :         \'--\'.     /  \'--\'.     /  \'   :  | \'--\'.     /      ;   |.\'    |  :  :         |   | \'`--\'       ;   |.\'    ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::blue),
                           "\n--  |  | ,\'         :   : :-\'   |   :    /  ;   : ;--\'      \\   \\ .\'      `--\'---\'   \'  :  `--\'   \\         |  | ,\'           `--\'---\'     `--\'---\'   ;   |.\'    `--\'---\'       \'---\'      |  | ,\'         \'   : |           \'---\'  ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::blue),
                           "\n--  `--\'           |   |.\'      \\   \\ .\'   |   ,/           `---`                   :  ,      .-./         `--\'                                     \'---\'                                `--\'           ;   |.\'                      ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::purple),
                           "\n--                  `---\'         `---`     \'---\'                                     `--`----\'                                                                                                            \'---\'                        ");
    fmt::print("{}", greeting);
    greeting = fmt::format(fmt::fg(fmt::color::purple),
                           "\n--                                                                                                                                                                                                                                      ");
    fmt::print("{}", greeting);
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void tp::div() {
    fmt::println("\n\n\n");
}

bool tp::yn(std::string const &question, char const& preffered) {
    std::string ib;
    if (preffered == 'Y' || preffered == 'y') {
        fmt::print("\n{} [Y/n]\n",question);
    }else {
        fmt::print("\n{} [y/N]\n",question);
    }
    std::getline(std::cin,ib);
    if (ib.empty()) {
        ib = std::to_string(preffered);
    }
    return (ib == "y" || ib == "Y");
}

bool tp::yn(std::string const &question) {
    std::string ib;
    fmt::print("\n\n{} [Y/n]\n",question);
    std::getline(std::cin,ib);
    if (ib.empty()) {
        ib = "Y";
    }
    return (ib == "y" || ib == "Y");
}

bool tp::exec(std::string const &command) {
    fmt::println("{}",command);
    if (system(command.c_str())!=0) {
        return false;
    }
    return true;
}


