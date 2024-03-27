#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
using namespace std;

void pausecmd() {
    struct termios oldt, newt;
    int ch;
    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Set the terminal to raw mode to capture key presses without Enter key
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("Press any key to continue");
    ch = getchar();
    // Restore the terminal to its original settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Too few arguments! Usage: pacman <action> <package_name(s)>\n";
        return 1;
    }

    string action = argv[1];
    string packages;

    for (int i = 2; i < argc; ++i) {
        packages += argv[i];
        if (i < argc - 1) {
            packages += " ";
        }
    }


    if (action == "install") {
        if (packages.empty()) {
        cerr << "Error: No package names specified. Please provide at least one package name.\n";
        return 1;
        }
        system(("sudo pacman -S " + packages).c_str());
    } else if (action == "remove") {
        if (packages.empty()) {
        cerr << "Error: No package names specified. Please provide at least one package name.\n";
        return 1;
        }
        system(("sudo pacman -Rs " + packages).c_str());
    } else if (action == "update") {
        if (argc >= 3) {
            std::cout << "Too many arguments\n";
            return 1;
        } else {
            system("sudo pacman -Syy");
        }
    } else if (action == "upgrade") {
        if (argc >= 3) {
            std::cout << "Too many arguments\n";
            return 1;
        } else {
            system("sudo pacman -Su");
        }
    } else if (action == "upd") {
        if (argc >= 3) {
            std::cout << "Too many arguments\n";
            return 1;
        } else {
            system("sudo pacman -Syu");
        }
    }
    else if (action == "show") {
        if (packages.empty()) {
        cerr << "Error: No package names specified. Please provide at least one package name.\n";
        return 1;
        }
        system(("sudo pacman -Q " + packages).c_str());
    } else if (action == "localinstall") {
        if (packages.empty()) {
        cerr << "Error: No package path specified. Please provide a package path.\n";
        return 1;
        }
        if (argc > 3) {
        std::cout << "Too many arguments!" << std::endl;
        }
        system(("sudo pacman -U " + packages).c_str());
    } else if (action == "list") {
        if (packages.empty()) {
        cerr << "Error: No package names specified. Please provide at least one package name.\n";
        return 1;
        }
        system("sudo pacman -Q");
    } else if (action == "search") {
        if (packages.empty()) {
        cerr << "Error: No package names specified. Please provide at least one package name.\n";
        return 1;
        }
        system(("sudo pacman -Si " + packages).c_str());
    } else if (action == "mremove") {
        if (packages.empty()) {
        cerr << "Error: No package names specified. Please provide at least one package name.\n";
        return 1;
        }
        system(("sudo pacman -R $(pacman -Qq | grep " + packages + ")").c_str());
    } else if (action == "edit-sources") {
        if (argc >= 3) {
            std::cout << "Too many arguments\n";
            return 1;
        } else {
        std::cout << "What text editior do you want to use?\n";
        std::cout << "(nano,vim,vi)";
        std::string input;
        std::cin >> input;
        if (input == "nano" || input == "Nano") {
            system("sudo nano /etc/pacman.conf");
        }
        else if (input == "vim" || input == "Vim") {
            system("sudo vim /etc/pacman.conf");
        }
        else if (input == "vi" || input == "Vim") {
            system("sudo vi /etc/pacman.conf");
        }
        else {
            std::cout << "Not natively supported text editior! Do you want to continue?";
            std::string input;
            std::cin >> input;
            if (input == "y" || input == "Y" || input == "yes" || input == "Yes") {
                system(("sudo" + input + "/etc/pacman.conf").c_str());
            }
            else {
                return 1;
            }
            
        }
        pausecmd();
        }
    }
     else {
        cerr << "Invalid argument!\n";
        return 1;
    }
    
}
