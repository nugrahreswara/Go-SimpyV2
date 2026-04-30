#include "functions.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// ================= MENU ADMIN =================
void menuAdmin() {
    while (true) {
        tampilHeader("MENU ADMIN");

        cout << " [1] Edit Profil Saya\n";
        cout << " [2] Tambah Akun\n";
        cout << " [3] Edit Akun Lain\n";
        cout << " [4] Hapus Akun Lain\n";
        cout << " [5] Lihat Semua Akun\n";
        cout << " [6] Lihat Semua Transaksi\n";
        cout << " [7] Logout\n";
        cout << " [8] Keluar\n";

        cout << "----------------------------------\n";

        int p = inputMenu(1, 8);

        switch (p) {
            case 1: loading("Memproses..."); editProfilSendiri(); break;
            case 2: loading("Memproses..."); buatAkunOlehAdmin(); break;
            case 3: loading("Memproses..."); editProfilOlehAdmin(); break;
            case 4: loading("Memproses..."); hapusAkunOlehAdmin(); break;
            case 5: loading("Memproses..."); tampilkanSemuaUser(); break;
            case 6: loading("Memproses..."); lihatSemuaTransaksiAdmin(); break;
            case 7: loading("Logout"); logout(); return;
            case 8: exit(0);
            default: cout << "Input tidak valid\n"; pause();
        }
    }
}

// ================= MENU CUSTOMER =================
void menuCustomer() {
    while (true) {
        tampilHeader("MENU CUSTOMER");

        cout << " [1] Edit Profil\n";
        cout << " [2] Pesan Ojek\n";
        cout << " [3] Lihat Histori\n";
        cout << " [4] Hapus Akun\n";
        cout << " [5] Logout\n";
        cout << " [6] Keluar\n";

        cout << "----------------------------------\n";

        int p = inputMenu(1, 6);

        switch (p) {
            case 1: loading("Memproses..."); editProfilSendiri(); break;
            case 2: loading("Mencari driver"); pesanOjek(); break;
            case 3: loading("Memproses..."); lihatHistoriCustomer(); break;
            case 4: loading("Memproses..."); hapusAkunSendiri(); return;
            case 5: loading("Logout"); logout(); return;
            case 6: exit(0);
            default: cout << "Input tidak valid\n"; pause();
        }
    }
}

// ================= MENU DRIVER =================
void menuDriver() {
    while (true) {
        tampilHeader("MENU DRIVER");

        cout << " [1] Edit Profil\n";
        cout << " [2] Lihat Pendapatan\n";
        cout << " [3] Hapus Akun\n";
        cout << " [4] Logout\n";
        cout << " [5] Keluar\n";

        cout << "----------------------------------\n";

        int p = inputMenu(1, 5);

        switch (p) {
            case 1: loading("Memproses..."); editProfilSendiri(); break;
            case 2: loading("Memproses..."); lihatPendapatanDriver(); break;
            case 3: loading("Memproses..."); hapusAkunSendiri(); return;
            case 4: loading("Logout"); logout(); return;
            case 5: exit(0);
            default: cout << "Input tidak valid\n"; pause();
        }
    }
}

// ================= MAIN =================
int main() {

    // Inisialisasi user default
    if (jumlahUser == 0) {
        User admin;
        strcpy(admin.username, "admin");
        strcpy(admin.password, "admin");
        strcpy(admin.namaLengkap, "Administrator");
        strcpy(admin.role, "admin");
        admin.aktif = true;
        daftarUser[jumlahUser++] = admin;
    }

    inisialisasiFileCSV();
    srand(time(0));

    while (true) {

        // ===== BELUM LOGIN =====
        if (!isLogin()) {
            tampilHeader("MENU LOGIN");

            cout << " [1] Login\n";
            cout << " [2] Registrasi Customer\n";
            cout << " [3] Registrasi Driver\n";
            cout << " [4] Keluar\n";

            cout << "----------------------------------\n";

            int p = inputMenu(1, 4);

            switch (p) {
                case 1:
                    loading("Memproses login");
                    login();
                    break;
                case 2:
                    loading("Membuat akun");
                    buatAkunRegistrasi("customer");
                    break;
                case 3:
                    loading("Membuat akun");
                    buatAkunRegistrasi("driver");
                    break;
                case 4:
                    loadingBar();
                    return 0;
                default:
                    cout << "Input tidak valid\n";
                    pause();
            }
        }

        // ===== SUDAH LOGIN =====
        else {
            const char* username = getCurrentUser();
            User* user = cariUserByUsername(username);

            if (user == nullptr) {
                logout();
                continue;
            }

            loadingBar(); // animasi masuk menu

            if (strcmp(user->role, "admin") == 0) {
                menuAdmin();
            }
            else if (strcmp(user->role, "customer") == 0) {
                menuCustomer();
            }
            else if (strcmp(user->role, "driver") == 0) {
                menuDriver();
            }
            else {
                logout();
            }
        }
    }

    return 0;
}