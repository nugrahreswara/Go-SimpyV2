#define _HAS_STD_BYTE 0
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
#include "utils.h"
#include "functions.h"

using namespace std;

User daftarUser[MAX_USER];
int jumlahUser = 0;

Lokasi daftarLokasi[MAX_LOKASI];
int jumlahLokasi = 0;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void inputAman(char* buffer, int maxLen) {
    cin.getline(buffer, maxLen);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        buffer[maxLen - 1] = '\0';
    }
}
