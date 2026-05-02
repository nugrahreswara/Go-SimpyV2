#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "akun.h"
#include <string>
using namespace std;


// === UTILITAS ===
void clearScreen();

// === VALIDASI ===
bool usernameTerdaftar(const char* username);
bool nomorTerdaftar(const char* nomor);
bool emailTerdaftar(const char* email);
bool validasiUsername(const char* username);
bool validasiNomorTelepon(const char* nomor);
bool validasiEmail(const char* email);
bool validasiNama(const char* nama);

// === MANAJEMEN AKUN ===
// Registrasi dari menu login (tanpa pemilihan role)
void buatAkunRegistrasi(const char* role); // role: "customer" atau "driver"

// Admin: tambah akun baru (bisa pilih role)
void buatAkunOlehAdmin();

// Edit profil milik sendiri (customer/driver/admin)
void editProfilSendiri();

// Admin: edit profil user lain (berdasarkan username)
void editProfilOlehAdmin();

// Admin: hapus user lain (tidak bisa hapus dirinya sendiri)
void hapusAkunOlehAdmin();

// Customer/Driver: hapus akun sendiri (langsung logout, data transaksi tetap di CSV)
void hapusAkunSendiri();

// Tampilkan semua akun (detail lengkap)
void tampilkanSemuaUser();

// Fungsi tambahan untuk mendapatkan data user berdasarkan username (opsional)
User* cariUserByUsername(const char* username);

// === AUTENTIKASI ===
void login();
void logout();
bool isLogin();
const char* getCurrentUser(); // mengembalikan username yang sedang login
void setCurrentUser(const char* username);
void setLoginStatus(bool status);

// === PEMESANAN (TRANSAKSI) ===
void inisialisasiFileCSV();         // buat file transaksi.csv jika belum ada
void pesanOjek();                   // customer memesan ojek
void lihatHistoriCustomer();        // customer melihat histori pemesanan
void lihatPendapatanDriver();       // driver melihat pendapatan
void lihatSemuaTransaksiAdmin();    // admin melihat semua transaksi
// UI
void garis();
void tampilHeader(const char* judul);
void loading(const char* text = "Loading", int delay = 300);
void loadingBar(const char* text = "Loading", int total = 20, int delay = 50);
void pause();
int inputMenu(int min, int max);

#endif
