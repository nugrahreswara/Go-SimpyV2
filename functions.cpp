#define _HAS_STD_BYTE 0 
#include "functions.h"
#include <windows.h>
#include <iostream>
#include "sortingsearch.h" 
#include <limits>
using namespace std;


// Definisi variabel global (karena di akun.h hanya extern)
User daftarUser[MAX_USER];
int jumlahUser = 0;

// Variabel static untuk autentikasi (hanya terlihat di file ini)
static bool sudahLogin = false;
static char currentUser[20] = "";

// === UTILITAS ===
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// === VALIDASI ===
bool usernameTerdaftar(const char* username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

bool nomorTerdaftar(const char* nomor) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].nomorTelepon, nomor) == 0) {
            return true;
        }
    }
    return false;
}

bool emailTerdaftar(const char* email) {
    if (strlen(email) == 0) {
        return false;
    }

    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].alamatEmail, email) == 0) {
            return true;
        }
    }
    return false;
}

bool validasiUsername(const char* username) {
    int len = strlen(username);
    if (len < 3 || len > 15) {
        return false;
    }

    if (!((username[0] >= 'a' && username[0] <= 'z') || (username[0] >= 'A' && username[0] <= 'Z'))) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-')) {
            return false;
        }
    }

    return true;
}

bool validasiNomorTelepon(const char* nomor) {
    int len = strlen(nomor);
    if (len < 10) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (nomor[i] < '0' || nomor[i] > '9') {
            return false;
        }
    }

    return true;
}

bool validasiEmail(const char* email) {
    // Alamat E-Mail opsional
    if (strlen(email) == 0) {
        return true;
    }

    bool at = false, dot = false;
    int len = strlen(email);

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            at = true;
        }

        if (at && email[i] == '.') {
            dot = true;
        }
    }

    if (!at || !dot) {
        return false;
    }

    // local part tidak boleh mengandung titik
    for (int i = 0; i < len && email[i] != '@'; i++) {
        if (email[i] == '.') {
            return false;
        }
    }

    return true;
}

bool validasiNama(const char* nama) {
    if (strlen(nama) == 0) {
        return false;
    }

    for (int i = 0; nama[i]; i++) {
        char c = nama[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }

    return true;
}

// === MANAJEMEN AKUN ===
void buatAkunRegistrasi(const char* role) {
    clearScreen();
    std::cout << "=== REGISTRASI " << role << " ===" << std::endl;
    if (jumlahUser >= MAX_USER) {
        std::cout << "Kapasitas user penuh." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    User baru;
    baru.aktif = true;
    strcpy(baru.role, role);

    std::cout << "Ketentuan Username: " <<
    std::endl << "1. Panjang 3-15 karakter" <<
    std::endl << "2. Dapat mengandung huruf, angka, _ dan -" <<
    std:: endl << "3. Wajib diawali dengan huruf" <<
    std::endl << "Masukkan username: ";
    std::cin >> baru.username;

    // Validasi inputan username
    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        if (usernameTerdaftar(baru.username)) {
            std::cout << "Username sudah ada." << std::endl;
        } else {
            std::cout << "Username tidak valid." << std::endl;
        }

        std::cout << "Masukkan username lagi: ";
        std::cin >> baru.username;
    }

    // Password
    std::cout << "Password: ";
    std::cin >> baru.password;

    // Nama Lengkap
    std::cin.ignore();
    std::cout << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);

    // Validasi inputan Nama Lengkap
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama hanya boleh huruf dan spasi. Masukkan lagi: ";
        std::cin.getline(baru.namaLengkap, 50);
    }

    // Nomor Telepon
    std::cout << "Nomor telepon (min 10 digit angka): ";
    std::cin >> baru.nomorTelepon;

    // Validasi inputan Nomor Telepon
    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        if (nomorTerdaftar(baru.nomorTelepon)) {
            std::cout << "Nomor sudah terdaftar." << std::endl;
        } else {
            std::cout << "Nomor tidak valid." << std::endl;
            std::cout << "Masukkan nomor telepon lagi: ";
            std::cin >> baru.nomorTelepon;
        }
    }

    // Alamat E-Mail
    std::cin.ignore();
    std::cout << "Alamat email (opsional, tekan Enter jika tidak ada): ";
    std::cin.getline(baru.alamatEmail, 50);

    // Alamat E-Mail opsional
    if (strlen(baru.alamatEmail) > 0) {
        // Validasi inputan Alamat E-Mail
        while (!validasiEmail(baru.alamatEmail)) {
            std::cout << "Email tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(baru.alamatEmail, 50);
            if (strlen(baru.alamatEmail) == 0) {
                break;
            }
        }

        if (strlen(baru.alamatEmail) > 0 && emailTerdaftar(baru.alamatEmail)) {
            std::cout << "Email sudah terdaftar. Registrasi dibatalkan." << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    // Alamat
    std::cout << "Alamat: ";
    std::cin.getline(baru.alamat, 100);

    // Alamat wajib diisi
    while (strlen(baru.alamat) == 0) {
        std::cout << "Alamat tidak boleh kosong. Masukkan alamat: ";
        std::cin.getline(baru.alamat, 100);
    }

    daftarUser[jumlahUser++] = baru;
    std::cout << "Registrasi berhasil! Silakan login." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void buatAkunOlehAdmin() {
    clearScreen();
    std::cout << "=== TAMBAH AKUN (ADMIN) ===" << std::endl;
    if (jumlahUser >= MAX_USER) {
        std::cout << "Kapasitas penuh." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    User baru;
    baru.aktif = true;

    // Role
    std::cout << "Role (admin/customer/driver): ";
    std::cin >> baru.role;

    // Validasi inputan Role
    while (strcmp(baru.role, "admin") != 0 && strcmp(baru.role, "customer") != 0 && strcmp(baru.role, "driver") != 0) {
        std::cout << "Role harus admin, customer, atau driver. Masukkan lagi: ";
        std::cin >> baru.role;
    }

    // Username
    std::cout << "Username: ";
    std::cin >> baru.username;
    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        if (usernameTerdaftar(baru.username)) {
            std::cout << "Username sudah ada." << std::endl;
        } else {
            std::cout << "Username tidak valid." << std::endl;
            std::cout << "Masukkan username lagi: ";
            std::cin >> baru.username;
        }
    }

    // Password
    std::cout << "Password: ";
    std::cin >> baru.password;

    // Nama Lengkap
    std::cin.ignore();
    std::cout << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);

    // Validasi inputan Nama Lengkap
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama hanya boleh huruf dan spasi. Masukkan lagi: ";
        std::cin.getline(baru.namaLengkap, 50);
    }

    // Nomor Telepon
    std::cout << "Nomor telepon: ";
    std::cin >> baru.nomorTelepon;

    // Validasi inputan Nomor Telepon dan tidak boleh duplikat
    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        if (nomorTerdaftar(baru.nomorTelepon)) {
            std::cout << "Nomor sudah terdaftar." << std::endl;
        } else {
            std::cout << "Nomor tidak valid." << std::endl;
            std::cout << "Masukkan nomor telepon lagi: ";
            std::cin >> baru.nomorTelepon;
        }
    }

    // Alamat E-Mail
    std::cin.ignore();
    std::cout << "Email (opsional): ";
    std::cin.getline(baru.alamatEmail, 50);

    // Alamat E-Mail opsional
    if (strlen(baru.alamatEmail) > 0) {
        // Validasi inputan Alamat E-Mail
        while (!validasiEmail(baru.alamatEmail)) {
            std::cout << "Alamat E-Mail tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(baru.alamatEmail, 50);
            if (strlen(baru.alamatEmail) == 0) {
                break;
            }
        }

        if (strlen(baru.alamatEmail) > 0 && emailTerdaftar(baru.alamatEmail)) {
            std::cout << "Alamat E-Mail sudah terdaftar. Pembatalan." << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    // Alamat
    std::cout << "Alamat: ";
    std::cin.getline(baru.alamat, 100);

    daftarUser[jumlahUser++] = baru;
    std::cout << "Akun berhasil dibuat." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void editProfilSendiri() {
    if (!isLogin()) {
        std::cout << "Anda belum login." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    clearScreen();
    std::cout << "=== EDIT PROFIL SENDIRI ===" << std::endl;
    const char* username = getCurrentUser();
    User* u = cariUserByUsername(username);

    if (u == nullptr) {
        std::cout << "Akun tidak ditemukan." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "Kosongkan jika tidak ingin mengubah." << std::endl;
    char input[100];
    std::cin.ignore();

    // Nama Lengkap
    std::cout << "Nama lengkap (" << u->namaLengkap << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNama(input)) {
        strcpy(u->namaLengkap, input);
    } else if (strlen(input) > 0) {
        std::cout << "Nama tidak valid." << std::endl;
    }

    // Username
    std::cout << "Username baru (" << u->username << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {

        // Cek apakah username baru sama dengan yang lama
        if (strcmp(input, u->username) == 0) {
        } 

        else if (validasiUsername(input) && !usernameTerdaftar(input)) {
            strcpy(u->username, input);
            setCurrentUser(input); // update current user
        }

        else {
            std::cout << "Username tidak valid/terdaftar." << std::endl;
        }
    }

    // Nomor Telepon
    std::cout << "Nomor telepon (" << u->nomorTelepon << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        if (strcmp(input, u->nomorTelepon) == 0) {
        }

        else if (validasiNomorTelepon(input) && !nomorTerdaftar(input)) {
            strcpy(u->nomorTelepon, input);
        }

        else {
            std::cout << "Nomor tidak valid/terdaftar." << std::endl;
        }
    }

    // Alamat E-Mail
    std::cout << "Alamat E-Mail (" << u->alamatEmail << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        if (strcmp(input, u->alamatEmail) == 0) {
        }

        else if (validasiEmail(input) && !emailTerdaftar(input)) {
            strcpy(u->alamatEmail, input);
        }

        else {
            std::cout << "Alamat E-Mail tidak valid atau sudah terdaftar." << std::endl;
        }
    }

    // Alamat
    std::cout << "Alamat (" << u->alamat << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        strcpy(u->alamat, input);
    }

    // Password
    std::cout << "Password baru (kosongkan jika tidak ganti): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        strcpy(u->password, input);
    }

    std::cout << "Profil berhasil diupdate." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void editProfilOlehAdmin() {
    clearScreen();
    if (jumlahUser == 0) {
        std::cout << "Belum ada akun." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Tampilkan semua user dulu
    tampilkanSemuaUser();
    char username[20];
    std::cout << "Masukkan username akun yang akan diedit: ";
    std::cin >> username;
    int idx = -1;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0 && daftarUser[i].aktif) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        std::cout << "Akun tidak ditemukan." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }
    User *u = &daftarUser[idx];
    std::cout << "Edit akun " << username << " (kosongkan jika tidak ingin mengubah)" << std::endl;
    std::cin.ignore();
    char input[100];

    // Nama Lengkap
    std::cout << "Nama lengkap (" << u->namaLengkap << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNama(input)) {
        strcpy(u->namaLengkap, input);
    } else if (strlen(input) > 0) {
        std::cout << "Nama tidak valid." << std::endl;
    }

    // Username
    std::cout << "Username baru (" << u->username << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiUsername(input) && !usernameTerdaftar(input)) {
        strcpy(u->username, input);
    } else if (strlen(input) > 0) {
        std::cout << "Username tidak valid/terdaftar." << std::endl;
    }

    // Nomor Telepon
    std::cout << "Nomor telepon (" << u->nomorTelepon << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNomorTelepon(input) && !nomorTerdaftar(input)) {
        strcpy(u->nomorTelepon, input);
    } else if (strlen(input) > 0) {
        std::cout << "Nomor tidak valid/terdaftar." << std::endl;
    }

    // Alamat E-Mail
    std::cout << "Alamat E-Mail (" << u->alamatEmail << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiEmail(input) && !emailTerdaftar(input)) {
        strcpy(u->alamatEmail, input);
    } else if (strlen(input) > 0) {
        std::cout << "Email tidak valid/terdaftar." << std::endl;
    }

    // Alamat
    std::cout << "Alamat (" << u->alamat << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        strcpy(u->alamat, input);
    }

    // Role
    std::cout << "Role baru (" << u->role << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && (strcmp(input,"admin")==0 || strcmp(input,"customer")==0 || strcmp(input,"driver")==0)) {
        strcpy(u->role, input);
    }

    // Password
    std::cout << "Password baru (kosongkan jika tidak ganti): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        strcpy(u->password, input);
    }

    std::cout << "Akun berhasil diupdate." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void hapusAkunOlehAdmin() {
    if (!isLogin()) {
        return;
    }
    clearScreen();
    if (jumlahUser == 0) {
        std::cout << "Belum ada akun." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }
    tampilkanSemuaUser();
    char username[20];
    std::cout << "Masukkan username akun yang akan dihapus: ";
    std::cin >> username;

    // Cek apakah yang dihapus adalah admin yang sedang login
    if (strcmp(username, getCurrentUser()) == 0) {
        std::cout << "Anda tidak dapat menghapus akun Anda sendiri di sini. Gunakan 'Hapus Akun Saya' jika ingin menghapus diri." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    int idx = -1;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0 && daftarUser[i].aktif) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        std::cout << "Akun tidak ditemukan." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Hapus
    for (int i = idx; i < jumlahUser - 1; i++) {
        daftarUser[i] = daftarUser[i+1];
    }
    jumlahUser--;
    std::cout << "Akun berhasil dihapus." << std::endl;
    std::cin.ignore();
    std::cin.get();
}


void hapusAkunSendiri() {
    if (!isLogin()) {
        std::cout << "Anda belum login." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    clearScreen();
    std::cout << "=== HAPUS AKUN SENDIRI ===" << std::endl;
    std::cout << "Akun Anda akan dihapus secara permanen. Data transaksi tetap tersimpan dengan username asli." << std::endl;
    std::cout << "Yakin? (y/t): ";
    char confirm;
    std::cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        const char* username = getCurrentUser();
        int idx = -1;
        for (int i = 0; i < jumlahUser; i++) {
            if (strcmp(daftarUser[i].username, username) == 0 && daftarUser[i].aktif) {
                idx = i;
                break;
            }
        }

        if (idx != -1) {
            for (int i = idx; i < jumlahUser - 1; i++) {
                daftarUser[i] = daftarUser[i+1];
            }
            jumlahUser--;
        }

        logout(); // set sudahLogin false dan currentUser kosong
        std::cout << "Akun Anda telah dihapus. Anda akan kembali ke menu login." << std::endl;
        std::cin.ignore();
        std::cin.get();
    } else {
        std::cout << "Penghapusan dibatalkan." << std::endl;
        std::cin.ignore();
        std::cin.get();
    }
}


void tampilkanSemuaUser() {
    clearScreen();
    std::cout << "=== DAFTAR SEMUA AKUN ===" << std::endl;
    if (jumlahUser == 0) {
        std::cout << "Tidak ada akun terdaftar." << std::endl;
    } else {
        for (int i = 0; i < jumlahUser; i++) {
            User u = daftarUser[i];
            std::cout << "Username   : " << u.username << std::endl;
            std::cout << "Nama       : " << u.namaLengkap << std::endl;
            std::cout << "Telepon    : " << u.nomorTelepon << std::endl;
            std::cout << "Email      : " << (strlen(u.alamatEmail) ? u.alamatEmail : "-") << std::endl;
            std::cout << "Alamat     : " << u.alamat << std::endl;
            std::cout << "Role       : " << u.role << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    std::cin.ignore();
    std::cin.get();
}

User* cariUserByUsername(const char* username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0 && daftarUser[i].aktif) {
            return &daftarUser[i];
        }
    }
    return nullptr;
}

// === AUTENTIKASI ===
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
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        // Cari user
        User* user = cariUserByUsername(username);
        if (user != nullptr && strcmp(user->password, password) == 0 && user->aktif) {
            sudahLogin = true;
            strcpy(currentUser, username);
            std::cout << "Login berhasil!" << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        } else {
            percobaan++;
            if (percobaan < maxPercobaan) {
                std::cout << "Username atau password salah. Percobaan " << percobaan << " dari " << maxPercobaan << std::endl;
                std::cin.ignore();
                std::cin.get();
                clearScreen();
            } else {
                std::cout << "Anda telah gagal login 5 kali. Program akan berhenti." << std::endl;
                exit(0);
            }
        }
    }
}

void logout() {
    sudahLogin = false;
    currentUser[0] = '\0';
    std::cout << "Anda telah logout." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

// === PEMESANAN (TRANSAKSI) ===
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
        std::cout << "Tidak ada driver tersedia saat ini." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    float jarak;
    std::cout << "Masukkan jarak (km): ";
    std::cin >> jarak;
    if (jarak <= 0) {
        std::cout << "Jarak harus lebih dari 0." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
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

    std::ofstream out("transaksi.csv", std::ios::app);
    if (!out.is_open()) {
        std::cout << "Gagal membuka file transaksi.csv" << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }
    out << waktu << "," << getCurrentUser() << "," << driverDipilih << "," << jarak << "," << harga << std::endl;
    out.close();

    std::cout << "Pesanan berhasil!" << std::endl;
    std::cout << "Jarak: " << jarak << " km" << std::endl;
    std::cout << "Harga: Rp" << harga << std::endl;
    std::cout << "Driver: " << driverDipilih << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void lihatHistoriCustomer() {
    if (!isLogin()) {
        return;
    }
    clearScreen();
    std::ifstream in("transaksi.csv");
    if (!in.is_open()) {
        std::cout << "Belum ada transaksi." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }
    char line[256];
    bool found = false;
    int lineNum = 0;
    std::cout << "=== HISTORI PEMESANAN ===" << std::endl;
    while (in.getline(line, 256)) {
        if (lineNum == 0) {
            lineNum++;
            continue;
        }
        char waktu[50], customer[20], driver[20];
        float jarak, harga;
        char *token = strtok(line, ",");
        if (token) {
            strcpy(waktu, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(customer, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(driver, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            jarak = atof(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            harga = atof(token);
        }
        if (strcmp(customer, getCurrentUser()) == 0) {
            found = true;
            std::cout << "Waktu: " << waktu << std::endl;
            std::cout << "Driver: " << driver << std::endl;
            std::cout << "Jarak: " << jarak << " km" << std::endl;
            std::cout << "Harga: Rp" << harga << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    in.close();
    if (!found) {
        std::cout << "Belum ada histori pemesanan." << std::endl;
    }
    std::cin.ignore();
    std::cin.get();
}

void lihatPendapatanDriver() {
    if (!isLogin()) {
        return;
    }
    clearScreen();
    std::ifstream in("transaksi.csv");
    if (!in.is_open()) {
        std::cout << "Belum ada transaksi." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }
    char line[256];
    bool found = false;
    int lineNum = 0;
    float total = 0;
    std::cout << "=== PENDAPATAN DRIVER ===" << std::endl;
    while (in.getline(line, 256)) {
        if (lineNum == 0) {
            lineNum++;
            continue;
        }
        char waktu[50], customer[20], driver[20];
        float jarak, harga;
        char *token = strtok(line, ",");
        if (token) {
            strcpy(waktu, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(customer, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(driver, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            jarak = atof(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            harga = atof(token);
        }
        if (strcmp(driver, getCurrentUser()) == 0) {
            found = true;
            std::cout << "Waktu: " << waktu << std::endl;
            std::cout << "Customer: " << customer << std::endl;
            std::cout << "Jarak: " << jarak << " km" << std::endl;
            std::cout << "Pendapatan: Rp" << harga << std::endl;
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
    std::cin.ignore();
    std::cin.get();
}

void lihatSemuaTransaksiAdmin() {
    if (!isLogin()) {
        return;
    }

    clearScreen();
    std::ifstream in("transaksi.csv");

    if (!in.is_open()) {
        std::cout << "Belum ada transaksi." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    char line[256];
    std::cout << "=== SEMUA TRANSAKSI ===" << std::endl;

    while (in.getline(line, 256)) {
        std::cout << line << std::endl;
    }

    in.close();
    std::cin.ignore();
    std::cin.get();
}

#include "functions.h"
#include <iostream>
#include <windows.h>
#include <limits>

using namespace std;


void garis() {
    cout << "=========================================\n";
}


void tampilHeader(const char* judul) {
    system("cls");
    garis();
    cout << "          GO-SIMPY \n";
    garis();
    cout << "          " << judul << endl;
    garis();
    cout << endl;
}

void loading(const char* text, int delay) {
    cout << text;
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(delay);
    }
    cout << endl;
}

void loadingBar(const char* text, int total, int delay) {
    cout << text << "\n[";
    for (int i = 0; i < total; i++) {
        cout << "#";
        Sleep(delay);
    }
    cout << "]\n";
}

int inputMenu(int min, int max) {
    int pilihan;

    while (true) {
        cout << "Pilih: ";
        cin >> pilihan;

        if (cin.fail()) {
            cout << "Input harus angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (pilihan < min || pilihan > max) {
            cout << "Pilihan harus antara " << min << " - " << max << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return pilihan;
    }
}

void pause() {
    cout << "\nTekan Enter...";
    cin.ignore();
    cin.get();
}

