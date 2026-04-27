#include "manajemen_akun.h"
#include "akun.h"
#include "validasi.h"
#include <iostream>
#include <iomanip>

void tampilkan_daftar_akun() {
    cout << "\n=== DAFTAR AKUN ===\n";
    for (auto &a : akunDB) {
        cout << a.first << " | " << a.second.role << endl;
    }
}

void buat_akun(string pilihan) {
    Akun a;
    cout << "Username: ";
    cin >> a.username;

    if (username_terdaftar(a.username)) {
        cout << "Username sudah ada\n"; return;
    }

    cout << "Password: ";
    cin >> a.password;

    cout << "Nama: ";
    cin.ignore();
    getline(cin, a.nama_lengkap);

    string umurStr;
    cout << "Umur: ";
    cin >> umurStr;
    a.umur = validasi_input_umur(umurStr);

    cout << "Telepon: ";
    cin >> a.nomor_telepon;

    cout << "Email: ";
    cin >> a.alamat_email;

    if (pilihan == "2") a.role = "customer";
    else a.role = "driver";

    akunDB[a.username] = a;

    cout << "Akun berhasil dibuat\n";
}

void hapus_akun() {
    string user;
    cout << "Username: ";
    cin >> user;

    if (akunDB.count(user)) {
        akunDB.erase(user);
        cout << "Akun dihapus\n";
    }
}

void edit_profil(string user) {
    if (!akunDB.count(user)) return;

    cout << "Edit profil (dummy)\n";
}