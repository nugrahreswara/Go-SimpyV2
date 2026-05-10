#define _HAS_STD_BYTE 0 
#include <iostream>
#include <limits>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
#include "functions.h"
#include "sortingsearch.h" 
#include "utils.h"

using namespace std;

// === MANAJEMEN AKUN ===
void buatAkunRegistrasi(const char* role) {
    char judul[40];
    snprintf(judul, sizeof(judul), "REGISTRASI %s", role);
    tampilHeader(judul);

    if (jumlahUser >= MAX_USER) {
        warna(12); cout << "  [!] Kapasitas user penuh." << endl; resetWarna();
        waitEnter(); return;
    }

    User baru;
    baru.aktif = true;
    strcpy(baru.role, role);

    // Username
    warna(11); cout << endl << "  -- KETENTUAN USERNAME --" << endl; resetWarna();
    cout << "  1. Panjang 3-15 karakter" << endl;
    cout << "  2. Huruf, angka, _ dan -" << endl;
    cout << "  3. Wajib diawali huruf" << endl;
    warna(14); cout << "  Username : "; resetWarna();
    inputAman(baru.username, 20);

    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        warna(12);
        cout << "  [!] " << (usernameTerdaftar(baru.username) ? "Username sudah ada." : "Username tidak valid.") << endl;
        resetWarna();
        warna(14); cout << "  Username : "; resetWarna();
        inputAman(baru.username, 20);
    }

    // Password
    warna(11); cout << endl << "  -- KETENTUAN PASSWORD --" << endl; resetWarna();
    cout << "  1. Panjang 8-20 karakter" << endl;
    cout << "  2. Huruf besar (A-Z)" << endl;
    cout << "  3. Huruf kecil (a-z)" << endl;
    cout << "  4. Angka (0-9)" << endl;
    cout << "  5. Simbol (! @ # $ % _ - .)" << endl;
    warna(14); cout << "  Password : "; resetWarna();
    inputAman(baru.password, 20);

    while (!validasiPassword(baru.password)) {
        warna(12); cout << "  [!] Password tidak memenuhi ketentuan." << endl; resetWarna();
        warna(14); cout << "  Password : "; resetWarna();
        inputAman(baru.password, 20);
    }

    // Nama Lengkap
    warna(11); cout << endl << "  -- KETENTUAN NAMA LENGKAP --" << endl; resetWarna();
    cout << "  1. Minimal 3, maksimal 50 karakter" << endl;
    cout << "  2. Minimal 2 kata" << endl;
    cout << "  3. Hanya huruf dan spasi" << endl;
    cout << "  4. Tidak boleh diawali/diakhiri spasi ganda" << endl;
    warna(14); cout << "  Nama Lengkap : "; resetWarna();
    cin.getline(baru.namaLengkap, 50);

    while (!validasiNama(baru.namaLengkap)) {
        warna(12); cout << "  [!] Nama tidak valid." << endl; resetWarna();
        warna(14); cout << "  Nama Lengkap : "; resetWarna();
        cin.getline(baru.namaLengkap, 50);
    }

    // Nomor Telepon
    warna(14); cout << endl << "  Nomor Telepon (10-15 digit) : "; resetWarna();
    inputAman(baru.nomorTelepon, 20);
    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        warna(12); cout << "  [!] " << (nomorTerdaftar(baru.nomorTelepon) ? "Nomor sudah terdaftar." : "Nomor tidak valid.") << endl; resetWarna();
        warna(14); cout << "  Nomor Telepon : "; resetWarna();
        inputAman(baru.nomorTelepon, 20);
    }

    // Email
    warna(14); cout << "  Email (opsional, Enter jika tidak ada) : "; resetWarna();
    cin.getline(baru.alamatEmail, 50);

    if (strlen(baru.alamatEmail) > 0) {
        while (true) {
            if (!validasiEmail(baru.alamatEmail)) {
                warna(12); cout << "  [!] Email tidak valid." << endl; resetWarna();
            }

            else if (emailTerdaftar(baru.alamatEmail)) {
                warna(12); cout << "  [!] Email sudah dipakai akun lain." << endl; resetWarna();
            }

            else {
                break;
            }

            warna(14); cout << "  Email : "; resetWarna();
            cin.getline(baru.alamatEmail, 50);

            if (strlen(baru.alamatEmail) == 0) {
                break;
            }
        }
    }

    // Alamat
    warna(11); cout << endl << "  -- KETENTUAN ALAMAT --" << endl; resetWarna();
    cout << "  1. Minimal 5 karakter" << endl;
    cout << "  2. Minimal 1 huruf" << endl;
    cout << "  3. Karakter: huruf, angka, spasi, . , - / ( )" << endl;
    warna(14); cout << "  Alamat : "; resetWarna();
    cin.getline(baru.alamat, 100);

    while (!validasiAlamat(baru.alamat)) {
        warna(13); cout << "  [!] Alamat tidak valid." << endl;
        resetWarna();
        warna(14); cout << "  Alamat : ";
        resetWarna();
        cin.getline(baru.alamat, 100);
    }

    daftarUser[jumlahUser++] = baru;
    loading("Menyimpan akun", 150);
    warna(10); cout << "  [+] Registrasi berhasil! Silakan login." << endl;
    resetWarna();
    waitEnter();
}

void buatAkunOlehAdmin() {
    tampilHeader("TAMBAH AKUN");

    if (jumlahUser >= MAX_USER) {
        warna(12); cout << "  [!] Kapasitas penuh." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    User baru;
    baru.aktif = true;

    // Role
    warna(14); cout << "  Role (admin/customer/driver) : "; resetWarna();
    cin >> baru.role;
    while (strcmp(baru.role, "admin") != 0 && strcmp(baru.role, "customer") != 0 && strcmp(baru.role, "driver") != 0) {
        warna(12); cout << "  [!] Role tidak valid." << endl;
        resetWarna();
        warna(14); cout << "  Role : ";
        resetWarna();
        cin >> baru.role;
        cin.ignore();
    }

    // Username 
    warna(14); cout << "  Username : "; resetWarna();
    cin >> baru.username;
    while (!validasiUsername(baru.username) || usernameTerdaftar(baru.username)) {
        warna(12);
        cout << "  [!] " << (usernameTerdaftar(baru.username) ? "Username sudah ada." : "Username tidak valid.") << endl;
        resetWarna();
        warna(14); cout << "  Username : ";
        resetWarna();
        cin >> baru.username;
    }

    // Password
    warna(14); cout << "  Password : "; resetWarna();
    cin >> baru.password;
    while (!validasiPassword(baru.password)) {
        warna(12); cout << "  [!] Password tidak memenuhi ketentuan.";
        resetWarna();
        warna(14); cout << "  Password : ";
        resetWarna();
        cin >> baru.password;
        cin.ignore();
    }

    // Nama Lengkap
    cin.ignore();
    warna(14); cout << "  Nama Lengkap : "; resetWarna();
    cin.getline(baru.namaLengkap, 50);

    while (!validasiNama(baru.namaLengkap)) {
        warna(12); cout << "  [!] Nama tidak valid." << endl;
        resetWarna();
        warna(14); cout << "  Nama Lengkap : ";
        resetWarna();
        cin.getline(baru.namaLengkap, 50);
    }

    // Nomor Telepon
    warna(14); cout << "  Nomor Telepon : "; resetWarna();
    inputAman(baru.nomorTelepon, 20);

    while (!validasiNomorTelepon(baru.nomorTelepon) || nomorTerdaftar(baru.nomorTelepon)) {
        warna(12); cout << "  [!] " << (nomorTerdaftar(baru.nomorTelepon) ? "Nomor sudah terdaftar." : "Nomor tidak valid.") << endl; resetWarna();
        warna(14); cout << "  Nomor Telepon : "; resetWarna();
        inputAman(baru.nomorTelepon, 20);
    }

    // Alamat E-Mail
    warna(14); cout << "  Email (opsional) : "; resetWarna();
    cin.getline(baru.alamatEmail, 50);

    if (strlen(baru.alamatEmail) > 0) {
        while (true) {
            if (!validasiEmail(baru.alamatEmail)) {
                warna(12); cout << "  [!] Email tidak valid." << endl; resetWarna();
            }

            else if (emailTerdaftar(baru.alamatEmail)) {
                warna(12); cout << "  [!] Email sudah dipakai." << endl; resetWarna();
            }

            else {
                break;
            }

            warna(14); cout << "  Email : "; resetWarna();
            cin.getline(baru.alamatEmail, 50);

            if (strlen(baru.alamatEmail) == 0) {
                break;
            }
        }
    }

    // Alamat
    warna(14); cout << "  Alamat : "; resetWarna();
    cin.getline(baru.alamat, 100);

    while (!validasiAlamat(baru.alamat)) {
        warna(12); cout << "  [!] Alamat tidak valid." << endl;
        resetWarna();
        warna(14); cout << "  Alamat : ";
        resetWarna();
        cin.getline(baru.alamat, 100);
    }

    // Menyimpan akun
    daftarUser[jumlahUser++] = baru;
    loading("Menyimpan akun", 150);
    warna(10); cout << "  [+] Akun berhasil dibuat." << endl; resetWarna();
    waitEnter();
}

void editProfilOlehAdmin() {
    tampilHeader("EDIT AKUN");

    if (jumlahUser == 0) {
        warna(12); cout << "  [!] Belum ada akun." << endl; resetWarna();
        waitEnter();
        return;
    }

    tampilSemuaUserDetail();
    char username[20];
    warna(14); cout << endl << "  Username akun yang diedit : "; resetWarna();
    inputAman(username, 20);
    int idx = -1;

    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0 && daftarUser[i].aktif) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        warna(12); cout << "  [!] Akun tidak ditemukan." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    User *u = &daftarUser[idx];
    warna(11); cout << endl << "  Kosongkan jika tidak ingin mengubah." << endl;
    resetWarna();
    char input[100];
    bool isSelf = (strcmp(username, getCurrentUser()) == 0 );
    char oldUsername[20];
    strcpy(oldUsername, u->username);

    // Edit Admin Nama Lengkap
    warna(14); cout << "  Nama Lengkap (" << u->namaLengkap << ") : ";
    resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (!validasiNama(input)) {
            warna(12); cout << "  [!] Nama tidak valid." << endl;
            resetWarna();
            warna(14); cout << "  Nama : "; resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0) {
            strcpy(u->namaLengkap, input);
        }
    }

    // Edit Admin Username
    warna(14); cout << "  Username baru (" << u->username << ") : "; resetWarna();
    cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->username) != 0 && (!validasiUsername(input) || usernameTerdaftar(input))) {
            warna(12); cout << "  [!] " << (usernameTerdaftar(input) ? "Username sudah dipakai." : "Username tidak valid.") << endl; resetWarna();
            warna(14); cout << "  Username : "; resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0 && strcmp(input, u->username) != 0) {
            strcpy(u->username, input);
            if (isSelf) setCurrentUser(input);
        }
    }

    warna(14); cout << "  Nomor telepon (" << u->nomorTelepon << ") : "; resetWarna();
    cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->nomorTelepon) != 0 && (!validasiNomorTelepon(input) || nomorTerdaftar(input))) {
            warna(12);
            cout << "  [!] " << (nomorTerdaftar(input) ? "Nomor sudah dipakai." : "Nomor tidak valid.") << "\n";
            resetWarna();
            warna(14); cout << "  Nomor : "; resetWarna();
            cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }

        if (strlen(input) > 0 && strcmp(input, u->nomorTelepon) != 0) strcpy(u->nomorTelepon, input);
    }

    warna(14); cout << "  Email (" << u->alamatEmail << ") : "; resetWarna();
    cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input, u->alamatEmail) != 0 && (!validasiEmail(input) || emailTerdaftar(input))) {
            warna(12);
            cout << "  [!] " << (emailTerdaftar(input) ? "Email sudah dipakai." : "Email tidak valid.") << endl;
            resetWarna();
            warna(14); cout << "  Email : "; resetWarna();
            cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0 && strcmp(input, u->alamatEmail) != 0) strcpy(u->alamatEmail, input);
    }

    warna(14); cout << "  Alamat (" << u->alamat << ") : "; resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (!validasiAlamat(input)) {
            warna(12); cout << "  [!] Alamat tidak valid." << endl; resetWarna();
            warna(14); cout << "  Alamat : "; resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0) strcpy(u->alamat, input);
    }

    warna(14); cout << "  Role baru (" << u->role << ") : "; resetWarna();
    cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (strcmp(input,"admin")!=0 && strcmp(input,"customer")!=0 && strcmp(input,"driver")!=0) {
            warna(12); cout << "  [!] Role tidak valid (admin/customer/driver).\n"; resetWarna();
            warna(14); cout << "  Role : "; resetWarna();
            cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) strcpy(u->role, input);
    }

    warna(14); cout << "  Password baru (kosongkan jika tidak ganti) : "; resetWarna();
    cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiPassword(input)) {
            warna(12); cout << "  [!] Password tidak memenuhi ketentuan.\n"; resetWarna();
            warna(14); cout << "  Password : "; resetWarna();
            cin.getline(input, 100);
            if (strlen(input) == 0) break;
        }
        if (strlen(input) > 0) strcpy(u->password, input);
    }

    loading("Menyimpan perubahan", 150);
    warna(10); cout << "  [+] Akun berhasil diupdate.\n"; resetWarna();
    waitEnter();
}

void editProfilSendiri() {
    if (!isLogin()) {
        warna(12); cout << "  [!] Anda belum login." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    tampilHeader("EDIT PROFIL");
    User* u = cariUserByUsername(getCurrentUser());

    if (u == nullptr) {
        warna(12); cout << "  [!] Akun tidak ditemukan." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    warna(11); cout << "  Kosongkan jika tidak ingin mengubah." << endl << endl;
    resetWarna();
    char input[100];

    // Edit Nama Lengkap
    warna(14); cout << "  Nama Lengkap (" << u->namaLengkap << ") : ";
    resetWarna();
    cin.getline(input, 100);
    if (strlen(input) > 0) {
        while (!validasiNama(input)) {
            warna(12); cout << "  [!] Nama tidak valid." << endl;
            resetWarna();
            warna(14); cout << "  Nama : ";
            resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0) {
            strcpy(u->namaLengkap, input);
        }
    }

    // Edit Username
    warna(14); cout << "  Username baru (" << u->username << ") : ";
    resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (strcmp(input, u->username) != 0 && (!validasiUsername(input) || usernameTerdaftar(input))) {
            warna(12);
            cout << "  [!] " << (usernameTerdaftar(input) ? "Username sudah dipakai." : "Username tidak valid.") << endl;
            resetWarna();
            warna(14); cout << "  Username : "; resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0 && strcmp(input, u->username) != 0) {
            strcpy(u->username, input);
            setCurrentUser(input);
        }
    }

    // Edit Nomor Telepon
    warna(14); cout << "  Nomor telepon (" << u->nomorTelepon << ") : ";
    resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (strcmp(input, u->nomorTelepon) != 0 && (!validasiNomorTelepon(input) || nomorTerdaftar(input))) {
            warna(12);
            cout << "  [!] " << (nomorTerdaftar(input) ? "Nomor sudah dipakai." : "Nomor tidak valid.") << endl;
            resetWarna();
            warna(14); cout << "  Nomor : ";
            resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0 && strcmp(input, u->nomorTelepon) != 0) {
            strcpy(u->nomorTelepon, input);
        }
    }

    // Edit E-Mail / Email
    warna(14); cout << "  Email (" << u->alamatEmail << ") : ";
    resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (strcmp(input, u->alamatEmail) != 0 && (!validasiEmail(input) || emailTerdaftar(input))) {
            warna(12);
            cout << "  [!] " << (emailTerdaftar(input) ? "Email sudah dipakai." : "Email tidak valid.") << endl;
            resetWarna();
            warna(14); cout << "  Email : ";
            resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0 && strcmp(input, u->alamatEmail) != 0) {
            strcpy(u->alamatEmail, input);
        }
    }

    // Edit Alamat
    warna(14); cout << "  Alamat (" << u->alamat << ") : ";
    resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (!validasiAlamat(input)) {
            warna(12); cout << "  [!] Alamat tidak valid." << endl;
            resetWarna();
            warna(14); cout << "  Alamat : ";
            resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0) {
            strcpy(u->alamat, input);
        }
    }

    // Edit Password
    warna(14); cout << "  Password baru (kosongkan jika tidak ganti) : ";
    resetWarna();
    cin.getline(input, 100);

    if (strlen(input) > 0) {
        while (!validasiPassword(input)) {
            warna(12); cout << "  [!] Password tidak memenuhi ketentuan." << endl;
            resetWarna();
            warna(14); cout << "  Password : ";
            resetWarna();
            cin.getline(input, 100);

            if (strlen(input) == 0) {
                break;
            }
        }

        if (strlen(input) > 0) {
            strcpy(u->password, input);
        }
    }

    // Menyimpan Perubahan
    loading("Menyimpan Perubahan", 150);
    warna(10); cout << "  [+] Profil berhasil diupdate." << endl;
    resetWarna();
    waitEnter();
}

void hapusAkunOlehAdmin() {
    if (!isLogin()) {
        return;
    }

    tampilHeader("HAPUS AKUN");

    if (jumlahUser == 0) {
        warna(12); cout << "  [!] Belum ada akun." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    tampilSemuaUserDetail();
    char username[20];
    warna(14); cout << endl << "  Username akun yang dihapus : ";
    resetWarna();
    inputAman(username, 20);

    if (strcmp(username, getCurrentUser()) == 0) {
        warna(12); cout << "  [!] Tidak bisa hapus akun sendiri di sini." << endl;
        resetWarna();
        waitEnter();
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
        warna(12); cout << "  [!] Akun tidak ditemukan." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    for (int i = idx; i < jumlahUser - 1; i++) {
        daftarUser[i] = daftarUser[i+1];
    }

    jumlahUser--;
    loading("Menghapus akun", 150);
    warna(10); cout << "  [+] Akun berhasil dihapus." << endl;
    resetWarna();
    waitEnter();
}

void hapusAkunSendiri() {
    if (!isLogin()) {
        warna(12); cout << "  [!] Anda belum login." << endl;
        resetWarna();
        waitEnter();
        return;
    }

    tampilHeader("HAPUS AKUN SAYA");
    warna(12);
    cout << "  [!] Akun akan dihapus permanen." << endl;
    cout << "  [!] Data transaksi tetap tersimpan." << endl;
    resetWarna();
    warna(14); cout << endl << "  Yakin? (y/t) : ";
    resetWarna();

    char confirmBuf[5];
    inputAman(confirmBuf, 5);

    if (confirmBuf[0] == 'y' || confirmBuf[0] == 'Y') {
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

        loading("Menghapus akun", 150);
        warna(10); cout << "  [+] Akun berhasil dihapus." << endl;
        resetWarna();
        logout();
    }

    else {
        warna(11); cout << "  Penghapusan dibatalkan." << endl;
        resetWarna();
        waitEnter();
    }
}

void tampilkanSemuaUser() {
    tampilHeader("DAFTAR SEMUA AKUN");
    if (jumlahUser == 0) {
        warna(12); cout << "  Tidak ada akun terdaftar." << endl;
        resetWarna();
    }

    else {
        tampilSemuaUserDetail();
    }

    waitEnter();
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
static bool sudahLogin = false;
static char currentUser[20] = "";

bool isLogin() { return sudahLogin; }
const char* getCurrentUser() { return currentUser; }
void setCurrentUser(const char* username) {
    if (username && strlen(username) > 0) strcpy(currentUser, username);
    else currentUser[0] = '\0';
}
void setLoginStatus(bool status) { sudahLogin = status; }

void login() {
    tampilHeader("LOGIN");
    char username[20], password[20];
    int percobaan = 0;
    const int maxPercobaan = 5;
    while (percobaan < maxPercobaan) {
        warna(14); cout << "  Username : "; resetWarna();
        inputAman(username, 20);
        warna(14); cout << "  Password : "; resetWarna();
        inputAman(password, 20);
        User* user = cariUserByUsername(username);
        if (user && strcmp(user->password, password) == 0 && user->aktif) {
            sudahLogin = true;
            strcpy(currentUser, username);
            loading("Login", 150);
            warna(10); cout << "  [+] Login berhasil!" << endl;
            resetWarna();
            waitEnter();
            return;
        }

        percobaan++;

        if (percobaan < maxPercobaan) {
            warna(12); cout << "  [!] Username atau password salah. Percobaan " << percobaan << " dari " << maxPercobaan << endl; resetWarna();
            waitEnter();
            clearScreen();
        }

        else {
            warna(12); cout << "  [!] Terlalu banyak percobaan. Program berhenti." << endl; resetWarna();
            exit(0);
        }
    }
}

void logout() {
    sudahLogin = false;
    currentUser[0] = '\0';
    warna(11); cout << "  Anda telah logout." << endl;
    resetWarna();
    waitEnter();
}
