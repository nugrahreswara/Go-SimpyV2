#define _HAS_STD_BYTE 0
#include "functions.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

static bool sudahLogin = false;
static char currentUser[20] = "";

bool isLogin() {
    return sudahLogin;
}

const char* getCurrentUser() {
    return currentUser;
}

void setCurrentUser(const char* username) {
    if (username != nullptr && strlen(username) > 0) {
        strcpy(currentUser, username);
    } else {
        currentUser[0] = '\0';
    }
}

void setLoginStatus(bool status) {
    sudahLogin = status;
}

void login() {
    clearScreen();
    std::cout << "=== LOGIN ===" << std::endl;
    char username[20], password[20];
    int percobaan = 0;
    const int maxPercobaan = 5;

    while (percobaan < maxPercobaan) {
        std::cout << "Username : ";
        inputAman(username, 20);
        std::cout << "Password : ";
        inputAman(password, 20);

        User* user = cariUserByUsername(username);
        if (user != nullptr && strcmp(user->password, password) == 0 && user->aktif) {
            sudahLogin = true;
            strcpy(currentUser, username);
            std::cout << "\n[+] Login berhasil! Selamat datang, " << user->namaLengkap << "!" << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        } else {
            percobaan++;
            if (percobaan < maxPercobaan) {
                std::cout << "[!] Username atau password salah. Percobaan " << percobaan << " dari " << maxPercobaan << std::endl;
                std::cin.ignore();
                std::cin.get();
                clearScreen();
            } else {
                std::cout << "[!] Anda telah gagal login 5 kali. Program akan berhenti." << std::endl;
                exit(0);
            }
        }
    }
}

void logout() {
    sudahLogin = false;
    currentUser[0] = '\0';
    std::cout << "[+] Anda telah logout. Sampai jumpa!" << std::endl;
    std::cin.ignore();
    std::cin.get();
}