#define _HAS_STD_BYTE 0
#include "functions.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

void inisialisasiFileCSV() {
    std::ifstream file("transaksi.csv");
    if (!file.is_open()) {
        std::ofstream out("transaksi.csv");
        out << "Waktu,Customer,Driver,Jarak,Harga" << std::endl;
        out.close();
    } else {
        file.close();
        std::ifstream cek("transaksi.csv");
        if (cek.peek() == std::ifstream::traits_type::eof()) {
            cek.close();
            std::ofstream out("transaksi.csv");
            out << "Waktu,Customer,Driver,Jarak,Harga" << std::endl;
            out.close();
        } else {
            cek.close();
        }
    }
}

void pesanOjek() {
    if (!isLogin()) return;
    clearScreen();

    int countDriver = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].role, "driver") == 0 && daftarUser[i].aktif)
            countDriver++;
    }
    if (countDriver == 0) {
        std::cout << "Tidak ada driver tersedia saat ini." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    float jarak;
    bool inputValid = false;

    std::cout << "Ketentuan Jarak:" << std::endl
    << "1. Harus berupa angka" << std::endl
    << "2. Minimal 0.1 km, maksimal 500 km" << std::endl
    << "3. Tidak boleh mengandung huruf atau simbol" << std::endl
    << "Masukkan jarak (km): ";

    while (!inputValid) {
        if (!inputFloat(jarak)) {
            std::cout << "Input tidak valid. Masukkan angka saja: ";
            continue;
        }
        if (jarak < 0.1f) {
            std::cout << "Jarak terlalu kecil. Minimal 0.1 km: ";
            continue;
        }
        if (jarak > 500.0f) {
            std::cout << "Jarak terlalu besar. Maksimal 500 km: ";
            continue;
        }
        inputValid = true;
    }

    char driverList[MAX_USER][20];
    int dIdx = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].role, "driver") == 0 && daftarUser[i].aktif)
            strcpy(driverList[dIdx++], daftarUser[i].username);
    }
    int randomIndex = rand() % dIdx;
    char driverDipilih[20];
    strcpy(driverDipilih, driverList[randomIndex]);

    float harga = jarak * 7000.0f;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char waktu[50];
    sprintf(waktu, "Tanggal: %02d-%02d-%04d Jam: %02d:%02d:%02d",
            ltm->tm_mday, ltm->tm_mon+1, ltm->tm_year+1900,
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    std::ofstream out("transaksi.csv", std::ios::app);
    if (!out.is_open()) {
        std::cout << "Gagal membuka file transaksi.csv" << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }
    out << waktu << "," << getCurrentUser() << "," << driverDipilih << "," << jarak << "," << harga << std::endl;
    out.close();

    std::cout << "Pesanan berhasil!" << std::endl;
    std::cout << "Jarak  : " << jarak << " km" << std::endl;
    std::cout << "Harga  : Rp" << harga << std::endl;
    std::cout << "Driver : " << driverDipilih << std::endl;
    std::cin.ignore(); std::cin.get();
}

void lihatHistoriCustomer() {
    if (!isLogin()) return;
    clearScreen();

    std::ifstream in("transaksi.csv");
    if (!in.is_open()) {
        std::cout << "Belum ada transaksi." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    char line[256];
    bool found = false;
    int lineNum = 0;
    std::cout << "=== HISTORI PEMESANAN ===" << std::endl;

    while (in.getline(line, 256)) {
        if (lineNum == 0) { lineNum++; continue; }
        char waktu[50], customer[20], driver[20];
        float jarak, harga;
        char *token = strtok(line, ",");
        if (token) strcpy(waktu, token);
        token = strtok(NULL, ",");
        if (token) strcpy(customer, token);
        token = strtok(NULL, ",");
        if (token) strcpy(driver, token);
        token = strtok(NULL, ",");
        if (token) jarak = atof(token);
        token = strtok(NULL, ",");
        if (token) harga = atof(token);

        if (strcmp(customer, getCurrentUser()) == 0) {
            found = true;
            std::cout << "Waktu  : " << waktu << std::endl;
            std::cout << "Driver : " << driver << std::endl;
            std::cout << "Jarak  : " << jarak << " km" << std::endl;
            std::cout << "Harga  : Rp" << harga << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    in.close();
    if (!found) std::cout << "Belum ada histori pemesanan." << std::endl;
    std::cin.ignore(); std::cin.get();
}

void lihatPendapatanDriver() {
    if (!isLogin()) return;
    clearScreen();

    std::ifstream in("transaksi.csv");
    if (!in.is_open()) {
        std::cout << "Belum ada transaksi." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    char line[256];
    bool found = false;
    int lineNum = 0;
    float total = 0;
    std::cout << "=== PENDAPATAN DRIVER ===" << std::endl;

    while (in.getline(line, 256)) {
        if (lineNum == 0) { lineNum++; continue; }
        char waktu[50], customer[20], driver[20];
        float jarak, harga;
        char *token = strtok(line, ",");
        if (token) strcpy(waktu, token);
        token = strtok(NULL, ",");
        if (token) strcpy(customer, token);
        token = strtok(NULL, ",");
        if (token) strcpy(driver, token);
        token = strtok(NULL, ",");
        if (token) jarak = atof(token);
        token = strtok(NULL, ",");
        if (token) harga = atof(token);

        if (strcmp(driver, getCurrentUser()) == 0) {
            found = true;
            std::cout << "Waktu      : " << waktu << std::endl;
            std::cout << "Customer   : " << customer << std::endl;
            std::cout << "Jarak      : " << jarak << " km" << std::endl;
            std::cout << "Pendapatan : Rp" << harga << std::endl;
            std::cout << "------------------------" << std::endl;
            total += harga;
        }
    }
    in.close();
    if (!found) {
        std::cout << "Belum ada pendapatan." << std::endl;
    } else {
        std::cout << "TOTAL PENDAPATAN: Rp" << total << std::endl;
    }
    std::cin.ignore(); std::cin.get();
}

void lihatSemuaTransaksiAdmin() {
    if (!isLogin()) return;
    clearScreen();

    std::ifstream in("transaksi.csv");
    if (!in.is_open()) {
        std::cout << "Belum ada transaksi." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    char line[256];
    std::cout << "=== SEMUA TRANSAKSI ===" << std::endl;
    while (in.getline(line, 256)) {
        std::cout << line << std::endl;
    }
    in.close();
    std::cin.ignore(); std::cin.get();
}