#include "tampilan.h"
#include <iostream>
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void setWarna(int warna) {
    SetConsoleTextAttribute(h, warna);
}

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(h, pos);
}

void clearScreen() {
    system("cls");
}

void box(int x, int y, int lebar, int tinggi) {
    for (int i = 0; i <= lebar; i++) {
        gotoxy(x + i, y); cout << "=";
        gotoxy(x + i, y + tinggi); cout << "=";
    }
    for (int i = 0; i <= tinggi; i++) {
        gotoxy(x, y + i); cout << "|";
        gotoxy(x + lebar, y + i); cout << "|";
    }
}


void loading() {
    clearScreen();

    setWarna(11);
    gotoxy(30, 10); cout << "Memuat Sistem";

    for (int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(400);
    }

    setWarna(14);
    gotoxy(30, 12); cout << "Loading: ";

    for (int i = 0; i <= 20; i++) {
        cout << char(219);
        Sleep(100);
    }

    setWarna(10);
    gotoxy(30, 14); cout << "Berhasil!";
    Sleep(700);

    setWarna(7);
}

void tampilkan_menu_login() {
    clearScreen();

    setWarna(11);
    box(20, 5, 40, 10);

    gotoxy(30, 6); cout << "GO-SIMPY V2";

    setWarna(14);
    gotoxy(25, 8);  cout << "1. Login";
    gotoxy(25, 9);  cout << "2. Daftar Customer";
    gotoxy(25,10);  cout << "3. Daftar Driver";
    gotoxy(25,11);  cout << "4. Exit";

    setWarna(7);
    gotoxy(25,13); cout << "Pilih menu: ";
}


void tampilkan_menu_utama(string role) {
    clearScreen();

    setWarna(10);
    box(20, 5, 40, 12);

    gotoxy(28, 6); cout << "MENU " << role;

    setWarna(14);

    if (role == "ADMIN") {
        gotoxy(25, 8); cout << "1. Manajemen Akun";
        gotoxy(25, 9); cout << "2. Lihat Data";
        gotoxy(25,10); cout << "3. Logout";
    }
    else if (role == "CUSTOMER") {
        gotoxy(25, 8); cout << "1. Pesan Layanan";
        gotoxy(25, 9); cout << "2. Riwayat Pesanan";
        gotoxy(25,10); cout << "3. Logout";
    }
    else if (role == "DRIVER") {
        gotoxy(25, 8); cout << "1. Lihat Order";
        gotoxy(25, 9); cout << "2. Update Status";
        gotoxy(25,10); cout << "3. Logout";
    }

    setWarna(7);
    gotoxy(25,13); cout << "Pilih menu: ";
}