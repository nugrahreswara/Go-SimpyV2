#define _HAS_STD_BYTE 0
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "functions.h"
#include "utils.h"

using namespace std;

void inisialisasiFileCSV() {
    ifstream file("transaksi.csv");
    if (!file.is_open()) {
        ofstream out("transaksi.csv");
        out << "Waktu,Customer,Driver,Jarak,Harga" << endl;
        out.close();
    } else {
        file.close();
        ifstream cek("transaksi.csv");
        if (cek.peek() == ifstream::traits_type::eof()) {
            cek.close();
            ofstream out("transaksi.csv");
            out << "Waktu,Customer,Driver,Jarak,Harga" << endl;
            out.close();
        } else {
            cek.close();
        }
    }
}

void pesanOjek() {
    if (!isLogin()) {
        return;
    }

    clearScreen();

    // Cek ketersediaan driver
    int countDriver = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].role, "driver") == 0 && daftarUser[i].aktif) {
            countDriver++;
        }
    }

    if (countDriver == 0) {
        warna(12); cout << "  [!] Tidak ada driver tersedia saat ini." << endl; resetWarna();
        waitEnter();
        return;
    }

    // Pilih mode pemesanan
    int mode;
    cout << "=== PESAN OJEK ===" << endl;
    cout << "Pilih mode:" << endl;
    cout << "1. Masukkan jarak langsung (km)" << endl;
    cout << "2. Pilih lokasi (asal dan tujuan)" << endl;
    cout << "Pilih (1/2): ";
    cin >> mode;
    cin.ignore(); // buang newline

    if (mode != 1 && mode != 2) {
        warna(12); cout << "  [!] Mode tidak valid." << endl; resetWarna();
        waitEnter();
        return;
    }

    float jarak = 0.0f;

    if (mode == 1) {
        cout << "Masukkan jarak (km): ";
        cin >> jarak;
        cin.ignore();

        if (jarak <= 0) {
            warna(12); cout << "  [!] Jarak harus lebih dari 0." << endl; resetWarna();
            waitEnter();
            return;
        }
    }

    else {
        if (jumlahLokasi == 0) {
            warna(12); cout << "  [!] Data lokasi belum tersedia. Silakan cek file lokasi.csv." << endl; resetWarna();
            waitEnter();
            return;
        }

        tampilkanDaftarLokasi();
        char asal[100], tujuan[100];
        cout << "Masukkan lokasi jemputan: ";
        cin.getline(asal, 100);
        cout << "Masukkan lokasi tujuan: ";
        cin.getline(tujuan, 100);

        if (strlen(asal) == 0 || strlen(tujuan) == 0) {
            warna(12); cout << "  [!] Lokasi tidak boleh kosong." << endl; resetWarna();
            waitEnter();
            return;
        }

        jarak = cariJarak(asal, tujuan);
        if (jarak < 0) {
            warna(12); cout << "  [!] Pasangan lokasi tidak ditemukan dalam database." << endl; resetWarna();
            waitEnter();
            return;
        }
        cout << "Jarak dari \"" << asal << "\" ke \"" << tujuan << "\" adalah " << jarak << " km." << endl;
    }

    // Kumpulkan driver aktif
    char driverList[MAX_USER][20];
    int dIdx = 0;

    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].role, "driver") == 0 && daftarUser[i].aktif) {
            strcpy(driverList[dIdx++], daftarUser[i].username);
        }
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

    ofstream out("transaksi.csv", ios::app);

    if (!out.is_open()) {
        warna(12); cout << "  [!] Gagal membuka file transaksi.csv" << endl; resetWarna();
        waitEnter();
        return;
    }

    out << waktu << "," << getCurrentUser() << "," << driverDipilih << "," << jarak << "," << harga << endl;
    out.close();

    loading("Memproses pesanan", 150);
    warna(10); cout << "  [+] Pesanan berhasil!" << endl; resetWarna();
    cout << "  Jarak  : " << jarak << " km" << endl;
    cout << "  Harga  : Rp" << harga << endl;
    cout << "  Driver : " << driverDipilih << endl;
    waitEnter();
}

void lihatHistoriCustomer() {
    if (!isLogin()) return;

    clearScreen();
    loading("Memuat histori", 100);  // efek loading sebentar

    ifstream in("transaksi.csv");
    if (!in.is_open()) {
        warna(12); cout << "  [!] Belum ada transaksi." << endl; resetWarna();
        waitEnter();
        return;
    }

    char line[256];
    bool found = false;
    int lineNum = 0;
    cout << "=== HISTORI PEMESANAN ===" << endl;

    while (in.getline(line, 256)) {
        if (lineNum == 0) {
            lineNum++;
            continue;
        }

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
            cout << "Waktu  : " << waktu << endl;
            cout << "Driver : " << driver << endl;
            cout << "Jarak  : " << jarak << " km" << endl;
            cout << "Harga  : Rp" << harga << endl;
            cout << "------------------------" << endl;
        }
    }
    in.close();

    if (!found) {
        warna(12); cout << "  [!] Belum ada histori pemesanan." << endl; resetWarna();
    }

    waitEnter();
}

void lihatPendapatanDriver() {
    if (!isLogin()) return;

    clearScreen();
    loading("Memuat pendapatan", 100);

    ifstream in("transaksi.csv");
    if (!in.is_open()) {
        warna(12); cout << "  [!] Belum ada transaksi." << endl; resetWarna();
        waitEnter();
        return;
    }

    char line[256];
    bool found = false;
    int lineNum = 0;
    float total = 0;
    cout << "=== PENDAPATAN DRIVER ===" << endl;

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
            cout << "Waktu      : " << waktu << endl;
            cout << "Customer   : " << customer << endl;
            cout << "Jarak      : " << jarak << " km" << endl;
            cout << "Pendapatan : Rp" << harga << endl;
            cout << "------------------------" << endl;
            total += harga;
        }
    }
    in.close();

    if (!found) {
        warna(12); cout << "  [!] Belum ada pendapatan." << endl; resetWarna();
    } else {
        warna(10); cout << "  TOTAL PENDAPATAN: Rp" << total << endl; resetWarna();
    }

    waitEnter();
}

void lihatSemuaTransaksiAdmin() {
    if (!isLogin()) return;

    clearScreen();
    loading("Memuat transaksi", 100);
    cout << endl;

    ifstream in("transaksi.csv");
    if (!in.is_open()) {
        warna(12); cout << "  [!] Belum ada transaksi." << endl; resetWarna();
        waitEnter();
        return;
    }

    char line[256];
    cout << "=== SEMUA TRANSAKSI ===" << endl;

    while (in.getline(line, 256)) {
        cout << line << endl;
    }

    in.close();
    waitEnter();
}

void normalisasiString(char* output, const char* input) {
    int i = 0, j = 0;
    while (input[i] == ' ') i++;
    bool prevSpasi = false;
    for (; input[i]; i++) {
        if (input[i] == ' ') {
            if (!prevSpasi && input[i+1] != '\0') {
                output[j++] = ' ';
                prevSpasi = true;
            }
        } else {
            output[j++] = tolower(input[i]);
            prevSpasi = false;
        }
    }
    if (j > 0 && output[j-1] == ' ') j--;
    output[j] = '\0';
}

void inisialisasiFileLokasi() {
    ifstream file("lokasi.csv");
    if (!file.is_open()) {
        ofstream out("lokasi.csv");
        out << "lokasi_asal,lokasi_tujuan,jarak_km\n";
        out.close();
        file.open("lokasi.csv");
    }
    char line[256];
    bool first = true;
    jumlahLokasi = 0;
    while (file.getline(line, 256)) {
        if (first) { first = false; continue; }
        if (strlen(line) == 0) continue;
        char asal[100], tujuan[100];
        float jarak;
        char *token = strtok(line, ",");
        if (token) strcpy(asal, token);
        token = strtok(NULL, ",");
        if (token) strcpy(tujuan, token);
        token = strtok(NULL, ",");
        if (token) jarak = atof(token);
        strcpy(daftarLokasi[jumlahLokasi].asal, asal);
        strcpy(daftarLokasi[jumlahLokasi].tujuan, tujuan);
        daftarLokasi[jumlahLokasi].jarak = jarak;
        jumlahLokasi++;
        if (jumlahLokasi >= MAX_LOKASI) break;
    }
    file.close();
}

float cariJarak(const char* asal, const char* tujuan) {
    char normAsal[100], normTujuan[100];
    normalisasiString(normAsal, asal);
    normalisasiString(normTujuan, tujuan);
    for (int i = 0; i < jumlahLokasi; i++) {
        char a[100], t[100];
        normalisasiString(a, daftarLokasi[i].asal);
        normalisasiString(t, daftarLokasi[i].tujuan);
        if (strcmp(a, normAsal) == 0 && strcmp(t, normTujuan) == 0)
            return daftarLokasi[i].jarak;
    }
    return -1.0f;
}

void tampilkanDaftarLokasi() {
    cout << "  Daftar lokasi yang tersedia (contoh):\n";
    for (int i = 0; i < jumlahLokasi && i < 20; i++) {
        cout << "    - " << daftarLokasi[i].asal << " -> " << daftarLokasi[i].tujuan << endl;
    }
}
