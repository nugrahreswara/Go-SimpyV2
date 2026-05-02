#ifndef AKUN_H
#define AKUN_H

#include <iostream>
#include <cstring> // untuk strcpy, strcmp, dll
#include <fstream> // untuk transaksi
#include <ctime> // untuk waktu
#include <cstdlib> // untuk system, rand, srand
#define _HAS_STD_BYTE 0

const int MAX_USER = 100;

struct User {
    char username[20];
    char password[20];
    char namaLengkap[50];
    char nomorTelepon[15];
    char alamatEmail[50];
    char alamat[100];
    char role[10]; // ada 3 role: "admin", "customer" dan "driver"
    bool aktif; // true jika akun masih ada dan false jika akun sudah dihapus
};

// Deklarasi variabel global 
extern User daftarUser[MAX_USER];
extern int jumlahUser;

#endif
