#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#define clear std::cout << "\033[2J\033[1;1H";
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




void dw() {
    std::string input;
    std::cout << "What distro are you using?" << std::endl;
    std::cout << "(arch,debian,fedora,opensuse or void)" << std::endl;
    std::cout << "(Derivatives included)" << std::endl;
    //derivatives like ubuntu,mint...
    std::cin >> input;
    if (input == "arch" || input == "Arch") {
        system("sudo pacman -S git wget gcc");
    }
    else if (input == "debian" || input == "Debian") {
        system("sudo apt-get install git wget build-essential");
    }
    else if (input == "fedora" || input == "Fedora") {
        system("sudo dnf install git wget gcc-c++");
    }
    else if (input == "opensuse" || input == "Opensuse") {
        system("sudo zypper install git wget gcc-c++");
    }
    else if (input == "void" || input == "Void") {
        system("sudo xbps-install git wget gcc");
    }
    else {
        std::cout << "Invalid input\n";
        dw();
    }
    
}


int main() {
    system("sudo rm -r /usr/easypacman/");
    system("sudo mkdir /usr/easypacman/");
    clear;
    std::cout << "EasyPacman Installer" << std::endl;
    std::cout << "By VPeti" << std::endl;
    sleep(2);
    dw();
    //std::cout << "The next few operations can cause damage to your system! Proceed at your own risk!\n";
    pausecmd();
    //system("sudo mv /bin/pacman /bin/pacmanold");
    system("sudo wget https://raw.githubusercontent.com/VPeti1/EasyPacman/main/main.cpp -O /usr/easypacman/pm.cpp");
    //system("sudo g++ /usr/easypacman/pm.cpp -o /bin/pacman");
    system("sudo g++ /usr/easypacman/pm.cpp -o /bin/easypacman");
    system("sudo chmod +x /bin/pacman");
    std::cout << "EasyPacman Installer Completed!" << std::endl;
    system("exit");
}