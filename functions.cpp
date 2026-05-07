#define _HAS_STD_BYTE 0 
#include "functions.h"
#ifdef _WIN32
    #include <windows.h>
#endif
#include <iostream>
#include "sortingsearch.h" 
#include <limits>
#include "tampilan.h"

Lokasi daftarLokasi[MAX_LOKASI];
int jumlahLokasi = 0;

using namespace std;


// Definisi variabel global (karena di akun.h hanya extern)
User daftarUser[MAX_USER];
int jumlahUser = 0;

// === UTILITAS ===
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

    // Username
    std::cout << "Ketentuan Username: "
    << std::endl << "1. Panjang 3-15 karakter"
    << std::endl << "2. Dapat mengandung huruf, angka, _ dan -"
    << std::endl << "3. Wajib diawali dengan huruf"
    << std::endl << "Masukkan username: ";
    inputAman(baru.username, 20);

    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        if (usernameTerdaftar(baru.username)) {
            std::cout << "Username sudah ada." << std::endl;
        } else {
            std::cout << "Username tidak valid." << std::endl;
        }
        std::cout << "Masukkan username lagi: ";
        inputAman(baru.username, 20);
    }

    // Password
    std::cout << "Ketentuan Password:" << std::endl
    << "1. Panjang 8-20 karakter" << std::endl
    << "2. Mengandung huruf besar (A-Z)" << std::endl
    << "3. Mengandung huruf kecil (a-z)" << std::endl
    << "4. Mengandung angka (0-9)" << std::endl
    << "5. Mengandung simbol (! @ # $ % _ - .)" << std::endl
    << "Password: ";
    inputAman(baru.password, 20);
    while (!validasiPassword(baru.password)) {
        std::cout << "Password tidak memenuhi ketentuan. Masukkan lagi: ";
        inputAman(baru.password, 20);
    }

    // Nama Lengkap
    std::cout << "Ketentuan Nama Lengkap:" << std::endl
    << "1. Minimal 3 karakter, maksimal 50 karakter" << std::endl
    << "2. Harus terdiri dari minimal 2 kata" << std::endl
    << "3. Hanya boleh huruf dan spasi" << std::endl
    << "4. Tidak boleh diawali/diakhiri spasi atau spasi ganda" << std::endl
    << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama tidak valid. Masukkan lagi: ";
        std::cin.getline(baru.namaLengkap, 50);
    }

    // Nomor Telepon
    std::cout << "Nomor telepon (min 10 digit, maks 15 digit): ";
    inputAman(baru.nomorTelepon, 20);

    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        if (nomorTerdaftar(baru.nomorTelepon)) {
            std::cout << "Nomor sudah terdaftar oleh akun lain." << std::endl;
        } else {
            std::cout << "Nomor tidak valid." << std::endl;
        }
        std::cout << "Masukkan nomor telepon lagi: ";
        inputAman(baru.nomorTelepon, 20);
}

    // Email
    std::cout << "Alamat email (opsional, tekan Enter jika tidak ada): ";
    std::cin.getline(baru.alamatEmail, 50);

    if (strlen(baru.alamatEmail) > 0) {
        while (true) {
            if (!validasiEmail(baru.alamatEmail)) {
                std::cout << "Email tidak valid. Masukkan lagi (atau kosongkan): ";
                std::cin.getline(baru.alamatEmail, 50);
            } else if (emailTerdaftar(baru.alamatEmail)) {
                std::cout << "Email sudah dipakai akun lain. Masukkan lagi (atau kosongkan): ";
                std::cin.getline(baru.alamatEmail, 50);
            } else {
                break;
            }

            if (strlen(baru.alamatEmail) == 0) {
                break;
            }
        }
    }

    // Alamat
    std::cout << "Ketentuan Alamat:" << std::endl
    << "1. Minimal 5 karakter" << std::endl
    << "2. Harus mengandung minimal 1 huruf" << std::endl
    << "3. Karakter yang diizinkan: huruf, angka, spasi, . , - / ( )" << std::endl
    << "Alamat: ";
    std::cin.getline(baru.alamat, 100);

    while (!validasiAlamat(baru.alamat)) {
        std::cout << "Alamat tidak valid. Masukkan lagi: ";
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
    while (strcmp(baru.role, "admin") != 0 && strcmp(baru.role, "customer") != 0 && strcmp(baru.role, "driver") != 0) {
        std::cout << "Role harus admin, customer, atau driver. Masukkan lagi: ";
        std::cin >> baru.role;
    }
 
    // Password
    std::cout << "Ketentuan Password:" << std::endl;
    std::cout << "1. Panjang 8-20 karakter" << std::endl;
    std::cout << "2. Mengandung huruf besar (A-Z)" << std::endl;
    std::cout << "3. Mengandung huruf kecil (a-z)" << std::endl;
    std::cout << "4. Mengandung angka (0-9)" << std::endl;
    std::cout << "5. Mengandung simbol (! @ # $ % _ - .)" << std::endl;
    std::cout << "6. Tidak boleh mengandung spasi" << std::endl;
    std::cout << "Password: ";
    std::cin >> baru.password;
    while (!validasiPassword(baru.password)) {
        std::cout << "Password tidak memenuhi ketentuan. Masukkan lagi: ";
        std::cin >> baru.password;
    }
 
    // Nama Lengkap
    std::cin.ignore();
    std::cout << "Ketentuan Nama Lengkap:" << std::endl
    << "1. Minimal 3 karakter, maksimal 50 karakter" << std::endl
    << "2. Harus terdiri dari minimal 2 kata" << std::endl
    << "3. Hanya boleh huruf dan spasi" << std::endl
    << "4. Tidak boleh diawali/diakhiri spasi atau spasi ganda" << std::endl
    << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama tidak valid. Masukkan lagi: ";
        std::cin.getline(baru.namaLengkap, 50);
    }
 
    // Nomor Telepon
    std::cout << "Nomor telepon (min 10 digit, maks 15 digit): ";
    inputAman(baru.nomorTelepon, 20);
    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        if (nomorTerdaftar(baru.nomorTelepon)) {
            std::cout << "Nomor sudah terdaftar oleh akun lain." << std::endl;
        } else {
            std::cout << "Nomor tidak valid." << std::endl;
        }
        std::cout << "Masukkan nomor telepon lagi: ";
        inputAman(baru.nomorTelepon, 20);
    }
 
    // Alamat E-Mail
    std::cout << "Email (opsional, tekan Enter jika tidak ada): ";
    std::cin.getline(baru.alamatEmail, 50);
    if (strlen(baru.alamatEmail) > 0) {
        while (true) {
            if (!validasiEmail(baru.alamatEmail)) {
                std::cout << "Email tidak valid. Masukkan lagi (atau kosongkan): ";
                std::cin.getline(baru.alamatEmail, 50);
            } else if (emailTerdaftar(baru.alamatEmail)) {
                std::cout << "Email sudah dipakai akun lain. Masukkan lagi (atau kosongkan): ";
                std::cin.getline(baru.alamatEmail, 50);
            } else {
                break;
            }
            if (strlen(baru.alamatEmail) == 0) break;
        }
    }
 
    // Alamat
    std::cout << "Alamat: ";
    std::cin.getline(baru.alamat, 100);
    while (!validasiAlamat(baru.alamat)) {
        std::cout << "Alamat tidak valid. Masukkan lagi: ";
        std::cin.getline(baru.alamat, 100);
    }
 
    daftarUser[jumlahUser++] = baru;
    std::cout << "Akun berhasil dibuat." << std::endl;
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

    tampilkanSemuaUser();
    char username[20];
    std::cout << "Masukkan username akun yang akan diedit: ";
    inputAman(username, 20);
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
    char input[100];

    // Nama Lengkap
    std::cout << "Nama lengkap (" << u->namaLengkap << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiNama(input)) {
            std::cout << "Nama tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) {
            strcpy(u->namaLengkap, input);
        }
    }

    // Username
    std::cout << "Username baru (" << u->username << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->username) != 0 &&
              (!validasiUsername(input) || usernameTerdaftar(input))) {
            if (usernameTerdaftar(input)) {
                std::cout << "Username sudah dipakai akun lain." << std::endl;
            } else {
                std::cout << "Username tidak valid." << std::endl;
            }
            std::cout << "Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->username) != 0) {
            strcpy(u->username, input);
        }
    }

    // Nomor Telepon
    std::cout << "Nomor telepon (" << u->nomorTelepon << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->nomorTelepon) != 0 &&
              (!validasiNomorTelepon(input) || nomorTerdaftar(input))) {
            if (nomorTerdaftar(input)) {
                std::cout << "Nomor sudah dipakai akun lain." << std::endl;
            } else {
                std::cout << "Nomor tidak valid." << std::endl;
            }
            std::cout << "Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->nomorTelepon) != 0) {
            strcpy(u->nomorTelepon, input);
        }
    }

    // Alamat E-Mail
    std::cout << "Alamat E-Mail (" << u->alamatEmail << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->alamatEmail) != 0 &&
              (!validasiEmail(input) || emailTerdaftar(input))) {
            if (emailTerdaftar(input)) {
                std::cout << "Email sudah dipakai akun lain." << std::endl;
            } else {
                std::cout << "Email tidak valid." << std::endl;
            }
            std::cout << "Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->alamatEmail) != 0) {
            strcpy(u->alamatEmail, input);
        }
    }

    // Alamat
    std::cout << "Alamat (" << u->alamat << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiAlamat(input)) {
            std::cout << "Alamat tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) {
            strcpy(u->alamat, input);
        }
    }

    // Role
    std::cout << "Role baru (" << u->role << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input,"admin") != 0 &&
               strcmp(input,"customer") != 0 &&
               strcmp(input,"driver") != 0) {
            std::cout << "Role tidak valid. Masukkan lagi (admin/customer/driver): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) {
            strcpy(u->role, input);
        }
    }

    // Password
    std::cout << "Password baru (kosongkan jika tidak ganti): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiPassword(input)) {
            std::cout << "Password tidak memenuhi ketentuan. Masukkan lagi: ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) {
            strcpy(u->password, input);
        }
    }

    std::cout << "Akun berhasil diupdate." << std::endl; 
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
    User* u = cariUserByUsername(getCurrentUser());
    if (u == nullptr) {
        std::cout << "Akun tidak ditemukan." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "Kosongkan jika tidak ingin mengubah." << std::endl;
    char input[100];
    std::cin.ignore();

    std::cout << "Nama lengkap (" << u->namaLengkap << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiNama(input)) {
            std::cout << "Nama tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) strcpy(u->namaLengkap, input);
    }

    std::cout << "Username baru (" << u->username << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->username) != 0 && (!validasiUsername(input) || usernameTerdaftar(input))) {
            std::cout << (usernameTerdaftar(input) ? "Username sudah dipakai." : "Username tidak valid.") << std::endl;
            std::cout << "Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->username) != 0) {
            strcpy(u->username, input);
            setCurrentUser(input);
        }
    }

    std::cout << "Nomor telepon (" << u->nomorTelepon << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->nomorTelepon) != 0 && (!validasiNomorTelepon(input) || nomorTerdaftar(input))) {
            std::cout << (nomorTerdaftar(input) ? "Nomor sudah dipakai." : "Nomor tidak valid.") << std::endl;
            std::cout << "Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->nomorTelepon) != 0) strcpy(u->nomorTelepon, input);
    }

    std::cout << "Alamat E-Mail (" << u->alamatEmail << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->alamatEmail) != 0 && (!validasiEmail(input) || emailTerdaftar(input))) {
            std::cout << (emailTerdaftar(input) ? "Email sudah dipakai." : "Email tidak valid.") << std::endl;
            std::cout << "Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->alamatEmail) != 0) strcpy(u->alamatEmail, input);
    }

    std::cout << "Alamat (" << u->alamat << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiAlamat(input)) {
            std::cout << "Alamat tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) strcpy(u->alamat, input);
    }

    std::cout << "Password baru (kosongkan jika tidak ganti): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiPassword(input)) {
            std::cout << "Password tidak memenuhi ketentuan. Masukkan lagi: ";
            std::cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) strcpy(u->password, input);
    }

    std::cout << "Profil berhasil diupdate." << std::endl;
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
    inputAman(username, 20);

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
    char confirmBuf[5];
    inputAman(confirmBuf, 5);
    char confirm = confirmBuf[0];
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


<<<<<<< HEAD
=======
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
        inputAman(username, 20);
        std::cout << "Password: ";
        inputAman(password, 20);

        // Cari user
        User* user = cariUserByUsername(username);
        if (user != nullptr && strcmp(user->password, password) == 0 && user->aktif) {
            sudahLogin = true;
            strcpy(currentUser, username);
            std::cout << "Login berhasil!" << std::endl;
            waitEnter();
            return;
        }

        else {
            percobaan++;
            if (percobaan < maxPercobaan) {
                std::cout << "Username atau password salah. Percobaan " << percobaan << " dari " << maxPercobaan << std::endl;
                waitEnter();
                clearScreen();
            } else {
                std::cout << "Anda telah gagal login 5 kali. Program akan berhenti." << std::endl;
                waitEnter();
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
>>>>>>> e3cdd407bade6f4b029d684b434ec3b419a02a6d

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
    if (!isLogin()) return;
    clearScreen();

    // Cek ketersediaan driver
    int countDriver = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].role, "driver") == 0 && daftarUser[i].aktif) countDriver++;
    }
    if (countDriver == 0) {
        std::cout << "Tidak ada driver tersedia saat ini." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    // Pilih mode pemesanan
    int mode;
    std::cout << "=== PESAN OJEK ===" << std::endl;
    std::cout << "Pilih mode:" << std::endl;
    std::cout << "1. Masukkan jarak langsung (km)" << std::endl;
    std::cout << "2. Pilih lokasi (asal dan tujuan)" << std::endl;
    std::cout << "Pilih (1/2): ";
    std::cin >> mode;
    if (mode != 1 && mode != 2) {
        std::cout << "Mode tidak valid." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    float jarak = 0.0f;

    if (mode == 1) {
        std::cout << "Masukkan jarak (km): ";
        std::cin >> jarak;
        if (jarak <= 0) {
            std::cout << "Jarak harus lebih dari 0." << std::endl;
            std::cin.ignore(); std::cin.get();
            return;
        }
    } else { // mode == 2
        // Pastikan data lokasi sudah dimuat
        if (jumlahLokasi == 0) {
            std::cout << "Data lokasi belum tersedia. Silakan cek file lokasi.csv." << std::endl;
            std::cin.ignore(); std::cin.get();
            return;
        }
        tampilkanDaftarLokasi();
        std::cin.ignore(); // membersihkan newline
        char asal[100], tujuan[100];
        std::cout << "Masukkan lokasi jemputan: ";
        std::cin.getline(asal, 100);
        std::cout << "Masukkan lokasi tujuan: ";
        std::cin.getline(tujuan, 100);
        if (strlen(asal) == 0 || strlen(tujuan) == 0) {
            std::cout << "Lokasi tidak boleh kosong." << std::endl;
            std::cin.ignore(); std::cin.get();
            return;
        }
        jarak = cariJarak(asal, tujuan);
        if (jarak < 0) {
            std::cout << "Pasangan lokasi tidak ditemukan dalam database." << std::endl;
            std::cin.ignore(); std::cin.get();
            return;
        }
        std::cout << "Jarak dari \"" << asal << "\" ke \"" << tujuan << "\" adalah " << jarak << " km." << std::endl;
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
        std::cin.ignore(); std::cin.get();
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

<<<<<<< HEAD
=======
bool validasiPassword(const char* password) {
    int len = strlen(password);
    if (len < 8 || len > 20) return false;
    bool hurufBesar=false, hurufKecil=false, angka=false, simbol=false;
    for (int i = 0; i < len; i++) {
        char c = password[i];
        if (c>='A'&&c<='Z') hurufBesar=true;
        else if (c>='a'&&c<='z') hurufKecil=true;
        else if (c>='0'&&c<='9') angka=true;
        else if (c=='!'||c=='@'||c=='#'||c=='$'||c=='%'||c=='_'||c=='-'||c=='.') simbol=true;
        else return false;
    }
    return hurufBesar && hurufKecil && angka && simbol;
}

bool validasiAlamat(const char* alamat) {
    int len = strlen(alamat);
    if (len < 5) return false;
    bool adaHuruf = false;
    for (int i = 0; i < len; i++) {
        char c = alamat[i];
        if ((c>='a'&&c<='z')||(c>='A'&&c<='Z')) adaHuruf = true;
        else if (!((c>='0'&&c<='9')||c==' '||c=='.'||c==','||c=='-'||c=='/'||c=='('||c==')')) return false;
    }
    return adaHuruf;
}


void normalisasiString(char* output, const char* input) {
    int i = 0, j = 0;
    bool prevSpasi = false;

    // Hilangkan spasi di awal
    while (input[i] == ' ') i++;
    while (input[i] != '\0') {
        if (input[i] == ' ') {
            if (!prevSpasi && input[i+1] != '\0') {
                output[j++] = ' ';
                prevSpasi = true;
            }
        }

        else {
            output[j++] = tolower(input[i]);
            prevSpasi = false;
        }

        i++;
    }

    // Hilangkan spasi di akhir
    if (j > 0 && output[j-1] == ' ') j--;
    output[j] = '\0';
}

void inisialisasiFileLokasi() {
    std::ifstream file("lokasi.csv");
    if (!file.is_open()) {
        // buat file contoh jika belum ada
        std::ofstream out("lokasi.csv");
        out << "lokasi_asal,lokasi_tujuan,jarak_km" << std::endl;
        out << "Universitas Mulawarman,Big Mall Samarinda,12.5" << std::endl;
        out << "Universitas Mulawarman,Bandara APT Pranoto,25.3" << std::endl;
        out << "Big Mall Samarinda,Universitas Mulawarman,12.5" << std::endl;
        out.close();
        file.open("lokasi.csv");
    }

    // Baca semua baris
    char line[256];
    bool firstLine = true;
    jumlahLokasi = 0;
    while (file.getline(line, 256)) {
        if (firstLine) { firstLine = false; continue; } // skip header
        if (strlen(line) == 0) continue;
        char asal[100], tujuan[100];
        float jarak;
        char *token = strtok(line, ",");
        if (token) strcpy(asal, token);
        token = strtok(NULL, ",");
        if (token) strcpy(tujuan, token);
        token = strtok(NULL, ",");
        if (token) jarak = atof(token);
        // simpan
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
        char normAsalFile[100], normTujuanFile[100];
        normalisasiString(normAsalFile, daftarLokasi[i].asal);
        normalisasiString(normTujuanFile, daftarLokasi[i].tujuan);
        if (strcmp(normAsalFile, normAsal) == 0 && strcmp(normTujuanFile, normTujuan) == 0) {
            return daftarLokasi[i].jarak;
        }
    }
    return -1.0f; // tidak ditemukan
}

void tampilkanDaftarLokasi() {
    std::cout << "Daftar lokasi yang tersedia (asal dan tujuan):" << std::endl;
    // sederhana: tampilkan semua asal dan tujuan unik (pakai array sementara)
    char lokasiUnik[MAX_LOKASI*2][100];
    int jumlahUnik = 0;
    for (int i = 0; i < jumlahLokasi; i++) {
        // cek asal
        bool adaAsal = false;
        for (int j = 0; j < jumlahUnik; j++) {
            if (strcmp(lokasiUnik[j], daftarLokasi[i].asal) == 0) { adaAsal = true; break; }
        }
        if (!adaAsal) strcpy(lokasiUnik[jumlahUnik++], daftarLokasi[i].asal);
        // cek tujuan
        bool adaTujuan = false;
        for (int j = 0; j < jumlahUnik; j++) {
            if (strcmp(lokasiUnik[j], daftarLokasi[i].tujuan) == 0) { adaTujuan = true; break; }
        }
        if (!adaTujuan) strcpy(lokasiUnik[jumlahUnik++], daftarLokasi[i].tujuan);
    }
    for (int i = 0; i < jumlahUnik; i++) {
        std::cout << "- " << lokasiUnik[i] << std::endl;
    }
}
>>>>>>> e3cdd407bade6f4b029d684b434ec3b419a02a6d
