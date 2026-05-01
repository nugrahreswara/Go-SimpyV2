#include "functions.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// === MENU ADMIN ===
void menuAdmin() {
    while (true) {
        tampilHeader("MENU ADMIN");

        cout << " [1] Edit Profil Saya" << endl;
        cout << " [2] Tambah Akun" << endl;
        cout << " [3] Edit Akun Lain" << endl;
        cout << " [4] Hapus Akun Lain" << endl;
        cout << " [5] Lihat Semua Akun" << endl;
        cout << " [6] Lihat Semua Transaksi" << endl;
        cout << " [7] Logout" << endl;
        cout << " [8] Keluar" << endl;

        cout << "----------------------------------" << endl;

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
            default: cout << "Input tidak valid" << endl;
            pause();
        }
    }
}

// === MENU CUSTOMER ===
void menuCustomer() {
    while (true) {
        tampilHeader("MENU CUSTOMER");

        cout << " [1] Edit Profil" << endl;
        cout << " [2] Pesan Ojek" << endl;
        cout << " [3] Lihat Histori" << endl;
        cout << " [4] Hapus Akun" << endl;
        cout << " [5] Logout" << endl;
        cout << " [6] Keluar" << endl;

        cout << "----------------------------------" << endl;

        int p = inputMenu(1, 6);

        switch (p) {
            case 1: loading("Memproses..."); editProfilSendiri(); break;
            case 2: loading("Mencari driver"); pesanOjek(); break;
            case 3: loading("Memproses..."); lihatHistoriCustomer(); break;
            case 4: loading("Memproses..."); hapusAkunSendiri(); return;
            case 5: loading("Logout"); logout(); return;
            case 6: exit(0);
            default: cout << "Input tidak valid" << endl;
            pause();
        }
    }
}

// === MENU DRIVER ===
void menuDriver() {
    while (true) {
        tampilHeader("MENU DRIVER");

        cout << " [1] Edit Profil" << endl;
        cout << " [2] Lihat Pendapatan" << endl;
        cout << " [3] Hapus Akun" << endl;
        cout << " [4] Logout" << endl;
        cout << " [5] Keluar" << endl;

        cout << "----------------------------------" << endl;

        int p = inputMenu(1, 5);

        switch (p) {
            case 1: loading("Memproses..."); editProfilSendiri(); break;
            case 2: loading("Memproses..."); lihatPendapatanDriver(); break;
            case 3: loading("Memproses..."); hapusAkunSendiri(); return;
            case 4: loading("Logout"); logout(); return;
            case 5: exit(0);
            default: cout << "Input tidak valid" << endl;
            pause();
        }
    }
}

// === MAIN ===
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

        // === BELUM LOGIN ===
        if (!isLogin()) {
            tampilHeader("MENU LOGIN");

            cout << " [1] Login" << endl;
            cout << " [2] Registrasi Customer" << endl;
            cout << " [3] Registrasi Driver" << endl;
            cout << " [4] Keluar" << endl;

            cout << "----------------------------------" << endl;

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
                    cout << "Input tidak valid" << endl;
                    pause();
            }
        }

        // === SUDAH LOGIN ===
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
