#include "functions.h"

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
    if (strlen(email) == 0) return false;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].alamatEmail, email) == 0) {
            return true;
        }
    }
    return false;
}

bool validasiUsername(const char* username) {
    int len = strlen(username);
    if (len < 3 || len > 15) return false;
    if (!((username[0] >= 'a' && username[0] <= 'z') || (username[0] >= 'A' && username[0] <= 'Z'))) return false;
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
    if (len < 10) return false;
    for (int i = 0; i < len; i++) {
        if (nomor[i] < '0' || nomor[i] > '9') return false;
    }
    return true;
}

bool validasiEmail(const char* email) {
    if (strlen(email) == 0) return true; // email opsional
    bool at = false, dot = false;
    int len = strlen(email);
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') at = true;
        if (at && email[i] == '.') dot = true;
    }
    if (!at || !dot) return false;

    // local part tidak boleh mengandung titik
    for (int i = 0; i < len && email[i] != '@'; i++) {
        if (email[i] == '.') return false;
    }
    return true;
}

bool validasiNama(const char* nama) {
    if (strlen(nama) == 0) return false;
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
    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        if (usernameTerdaftar(baru.username)) std::cout << "Username sudah ada." << std::endl;
        else std::cout << "Username tidak valid." << std::endl;
        std::cout << "Masukkan username lagi: ";
        std::cin >> baru.username;
    }

    std::cout << "Password: ";
    std::cin >> baru.password;

    std::cin.ignore();
    std::cout << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama hanya boleh huruf dan spasi. Masukkan lagi: ";
        std::cin.getline(baru.namaLengkap, 50);
    }

    std::cout << "Nomor telepon (min 10 digit angka): ";
    std::cin >> baru.nomorTelepon;
    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        if (nomorTerdaftar(baru.nomorTelepon)) std::cout << "Nomor sudah terdaftar." << std::endl;
        else std::cout << "Nomor tidak valid." << std::endl;
        std::cout << "Masukkan nomor telepon lagi: ";
        std::cin >> baru.nomorTelepon;
    }

    std::cin.ignore();
    std::cout << "Alamat email (opsional, tekan Enter jika tidak ada): ";
    std::cin.getline(baru.alamatEmail, 50);
    if (strlen(baru.alamatEmail) > 0) {
        while (!validasiEmail(baru.alamatEmail)) {
            std::cout << "Email tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(baru.alamatEmail, 50);
            if (strlen(baru.alamatEmail) == 0) break;
        }
        if (strlen(baru.alamatEmail) > 0 && emailTerdaftar(baru.alamatEmail)) {
            std::cout << "Email sudah terdaftar. Registrasi dibatalkan." << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    std::cout << "Alamat: ";
    std::cin.getline(baru.alamat, 100);
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

    std::cout << "Role (admin/customer/driver): ";
    std::cin >> baru.role;
    while (strcmp(baru.role, "admin") != 0 && strcmp(baru.role, "customer") != 0 && strcmp(baru.role, "driver") != 0) {
        std::cout << "Role harus admin, customer, atau driver. Masukkan lagi: ";
        std::cin >> baru.role;
    }

    std::cout << "Username: ";
    std::cin >> baru.username;
    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        if (usernameTerdaftar(baru.username)) std::cout << "Username sudah ada." << std::endl;
        else std::cout << "Username tidak valid." << std::endl;
        std::cout << "Masukkan username lagi: ";
        std::cin >> baru.username;
    }

    std::cout << "Password: ";
    std::cin >> baru.password;

    std::cin.ignore();
    std::cout << "Nama lengkap: ";
    std::cin.getline(baru.namaLengkap, 50);
    while (!validasiNama(baru.namaLengkap)) {
        std::cout << "Nama hanya boleh huruf dan spasi. Masukkan lagi: ";
        std::cin.getline(baru.namaLengkap, 50);
    }

    std::cout << "Nomor telepon: ";
    std::cin >> baru.nomorTelepon;
    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        if (nomorTerdaftar(baru.nomorTelepon)) std::cout << "Nomor sudah terdaftar." << std::endl;
        else std::cout << "Nomor tidak valid." << std::endl;
        std::cout << "Masukkan nomor telepon lagi: ";
        std::cin >> baru.nomorTelepon;
    }

    std::cin.ignore();
    std::cout << "Email (opsional): ";
    std::cin.getline(baru.alamatEmail, 50);
    if (strlen(baru.alamatEmail) > 0) {
        while (!validasiEmail(baru.alamatEmail)) {
            std::cout << "Email tidak valid. Masukkan lagi (atau kosongkan): ";
            std::cin.getline(baru.alamatEmail, 50);
            if (strlen(baru.alamatEmail) == 0) break;
        }
        if (strlen(baru.alamatEmail) > 0 && emailTerdaftar(baru.alamatEmail)) {
            std::cout << "Email sudah terdaftar. Pembatalan." << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    // Masih bingung untuk alamatnya wajib atau dijadikan opsional aja??
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

    std::cout << "Nama lengkap (" << u->namaLengkap << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNama(input)) strcpy(u->namaLengkap, input);
    else if (strlen(input) > 0) std::cout << "Nama tidak valid." << std::endl;

    std::cout << "Username baru (" << u->username << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiUsername(input) && !usernameTerdaftar(input)) {
        strcpy(u->username, input);
        setCurrentUser(input); // update current user
    } else if (strlen(input) > 0) std::cout << "Username tidak valid/terdaftar." << std::endl;

    std::cout << "Nomor telepon (" << u->nomorTelepon << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNomorTelepon(input) && !nomorTerdaftar(input)) {
        strcpy(u->nomorTelepon, input);
    } else if (strlen(input) > 0) std::cout << "Nomor tidak valid/terdaftar." << std::endl;

    std::cout << "Email (" << u->alamatEmail << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiEmail(input) && !emailTerdaftar(input)) {
        strcpy(u->alamatEmail, input);
    } else if (strlen(input) > 0) std::cout << "Email tidak valid/terdaftar." << std::endl;

    std::cout << "Alamat (" << u->alamat << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) strcpy(u->alamat, input);

    std::cout << "Password baru (kosongkan jika tidak ganti): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) strcpy(u->password, input);

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

    std::cout << "Nama lengkap (" << u->namaLengkap << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNama(input)) strcpy(u->namaLengkap, input);
    else if (strlen(input) > 0) std::cout << "Nama tidak valid." << std::endl;

    std::cout << "Username baru (" << u->username << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiUsername(input) && !usernameTerdaftar(input)) {
        strcpy(u->username, input);
    } else if (strlen(input) > 0) std::cout << "Username tidak valid/terdaftar." << std::endl;

    std::cout << "Nomor telepon (" << u->nomorTelepon << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiNomorTelepon(input) && !nomorTerdaftar(input)) {
        strcpy(u->nomorTelepon, input);
    } else if (strlen(input) > 0) std::cout << "Nomor tidak valid/terdaftar." << std::endl;

    std::cout << "Email (" << u->alamatEmail << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && validasiEmail(input) && !emailTerdaftar(input)) {
        strcpy(u->alamatEmail, input);
    } else if (strlen(input) > 0) std::cout << "Email tidak valid/terdaftar." << std::endl;

    std::cout << "Alamat (" << u->alamat << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) strcpy(u->alamat, input);

    std::cout << "Role baru (" << u->role << "): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0 && (strcmp(input,"admin")==0 || strcmp(input,"customer")==0 || strcmp(input,"driver")==0)) {
        strcpy(u->role, input);
    }

    std::cout << "Password baru (kosongkan jika tidak ganti): ";
    std::cin.getline(input, 100);
    if (strlen(input) > 0) strcpy(u->password, input);

    std::cout << "Akun berhasil diupdate." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void hapusAkunOlehAdmin() {
    if (!isLogin()) return;
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
    }

    else {
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
    }

    else {
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
        }

        else {
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
