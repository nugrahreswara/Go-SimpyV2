#define _HAS_STD_BYTE 0
#include <windows.h>
#include "functions.h"
#include <iostream>

using namespace std;

User daftarUser[MAX_USER];
int jumlahUser = 0;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void inputAman(char* buffer, int maxLen) {
    std::cin.getline(buffer, maxLen);
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        buffer[maxLen - 1] = '\0';
    }
}