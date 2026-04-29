#include "sistem_pemesanan.h"
#include "autentikasi.h"
#include <iostream>
#include <windows.h>
using namespace std;

void pesan_ojek() {
    cout << "\n=== PESAN OJEK ===\n";
    cout << "Pesanan sedang diproses...\n";
}

void lihat_histori() {
    cout << "\n=== HISTORI CUSTOMER ===\n";
    cout << "Belum ada histori\n";
}

void lihat_pendapatan() {
    cout << "\n=== PENDAPATAN DRIVER ===\n";
    cout << "Rp 0\n";
}

void lihat_semua_pendapatan() {
    cout << "\n=== SEMUA PENDAPATAN ===\n";
    cout << "Total: Rp 0\n";
}


void loadingPesanan() {
    cout << "\nMencari driver";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(500);
    }
    cout << endl;
}

void pesan_layanan() {
    system("cls");

    string lokasiAwal, tujuan;
    int pilihan;

    cout << "===== PESAN LAYANAN =====\n";
    cout << "Lokasi Penjemputan : ";
    cin.ignore();
    getline(cin, lokasiAwal);

    cout << "Tujuan             : ";
    getline(cin, tujuan);

    cout << "\nPilih Layanan:\n";
    cout << "1. GoRide\n";
    cout << "2. GoCar\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    loadingPesanan(); 

    cout << "\n===== DRIVER DITEMUKAN =====\n";
    cout << "Nama Driver : Budi\n";
    cout << "Kendaraan   : ";
    
    if (pilihan == 1)
        cout << "Motor\n";
    else
        cout << "Mobil\n";

    cout << "Plat Nomor  : KT 1234 XX\n";
    cout << "Estimasi    : 5 menit\n";

    cout << "\nPesanan berhasil dibuat!\n";
}