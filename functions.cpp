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

void inputAman(char* buffer, int maxLen) {
    std::cin.getline(buffer, maxLen);

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        buffer[maxLen - 1] = '\0';
    }
}

// === VALIDASI ===
bool inputFloat(float& hasil) {
    char buffer[20];
    inputAman(buffer, 20);

    if (strlen(buffer) == 0) {
        return false;
    }

    bool adaTitik = false;
    int digitCount = 0;
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '.') {
            if (adaTitik) return false;
            adaTitik = true;
        } else if (buffer[i] >= '0' && buffer[i] <= '9') {
            digitCount++;
        } else {
            return false;
        }
    }

    if (digitCount == 0) {
        return false;
    }

    hasil = atof(buffer);
    return true;
}

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
    int panjangNomor = strlen(nomor);

    if (panjangNomor < 10 || panjangNomor > 15) {
        return false;
    }

    if (nomor[0] != '0' && nomor[0] != '8') {
        return false;
    }

    bool angkaMuncul[10] = {false, false, false, false, false, false, false, false, false, false};
    int jumlahAngkaUnik = 0;

    for (int i = 0; i < panjangNomor; i++) {
        if (nomor[i] < '0' || nomor[i] > '9') {
            return false;
        }
        
        int nilaiAngka = nomor[i] - '0'; 
        
        if (angkaMuncul[nilaiAngka] == false) {
            angkaMuncul[nilaiAngka] = true;
            jumlahAngkaUnik++;
        }
    }

    if (jumlahAngkaUnik < 4) {
        return false;
    }

    return true;
}

bool validasiEmail(const char* email) {
    // Alamat E-Mail opsional
    if (strlen(email) == 0) {
        return true;
    }

    int panjangEmail = strlen(email);
    int posisiAt = -1; 
    int jumlahAt = 0;

    for (int i = 0; i < panjangEmail; i++) {
        if (email[i] == '@') {
            posisiAt = i;
            jumlahAt++;
        }
    }

    if (jumlahAt != 1 || posisiAt == 0 || posisiAt == panjangEmail - 1) {
        return false;
    }

    if (email[0] == '.' || email[posisiAt - 1] == '.') {
        return false;
    }
    
    for (int i = 0; i < posisiAt; i++) {
        if (email[i] == '.' && email[i + 1] == '.') {
            return false;
        }
    }

    bool adaTitikDiDomain = false;
    for (int i = posisiAt + 1; i < panjangEmail; i++) {
        if (email[i] == '.') {
            if (i == posisiAt + 1 || i == panjangEmail - 1) {
                return false;
            }
            if (email[i - 1] == '.') {
                return false;
            }
            adaTitikDiDomain = true;
        }
    }

    return adaTitikDiDomain;
}

bool validasiNama(const char* nama) {
    int len = strlen(nama);

    if (len < 3 || len > 50) {
        return false;
    }

    if (nama[0] == ' ' || nama[len - 1] == ' ') {
        return false;
    }

    for (int i = 0; i < len - 1; i++) {
        if (nama[i] == ' ' && nama[i + 1] == ' ') {
            return false;
        }
    }

    for (int i = 0; i < len; i++) {
        char c = nama[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }

    bool adaSpasi = false;
    for (int i = 1; i < len - 1; i++) {
        if (nama[i] == ' ') {
            adaSpasi = true;
            break;
        }
    }
    if (!adaSpasi) {
        return false;
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

    // Validasi inputan Role
    while (strcmp(baru.role, "admin") != 0 && strcmp(baru.role, "customer") != 0 && strcmp(baru.role, "driver") != 0) {
        std::cout << "Role harus admin, customer, atau driver. Masukkan lagi: ";
        std::cin >> baru.role;
    }

    // Nama lengkap
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
    std::cout << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);

    // Validasi inputan Nama Lengkap
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama hanya boleh huruf dan spasi. Masukkan lagi: ";
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

            if (strlen(baru.alamatEmail) == 0) {
                break;
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
            setCurrentUser(input);
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
        inputAman(username, 20);
        std::cout << "Password: ";
        inputAman(password, 20);

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

