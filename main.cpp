#define _HAS_STD_BYTE 0 
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "sortingsearch.h"
using namespace std;

// ================= MENU ADMIN =================
void menuAdmin() {
    while (true) {
        tampilHeader("MENU ADMIN");

        cout << "1. Edit Profil Saya\n";
        cout << "2. Tambah Akun\n";
        cout << "3. Edit Akun Lain\n";
        cout << "4. Hapus Akun Lain\n";
        cout << "5. Lihat Semua Akun\n";
        cout << "6. Lihat Semua Transaksi\n";
        cout << "7. Cari User\n";
        cout << "8. Sort User A-Z\n";
        cout << "9. Logout\n";
        cout << "10. Keluar\n\n";

        int p = inputMenu(1, 10);

        switch (p) {
            case 1: editProfilSendiri(); break;
            case 2: buatAkunOlehAdmin(); break;
            case 3: editProfilOlehAdmin(); break;
            case 4: hapusAkunOlehAdmin(); break;
            case 5: tampilkanSemuaUser(); break;
            case 6: lihatSemuaTransaksiAdmin(); break;
            case 7:
{
    char cari[50];
    cout << "Masukkan username: ";
    cin >> cari;

    loading("Mencari user", 150);

    int idx = cariUserIndexByUsername(cari);

    if (idx != -1) {
        tampilDetailUser(idx);
    } else {
        cout << "Tidak ditemukan\n";
    }

    pause();
    break;  // ← pastikan break ada di DALAM kurung kurawal
}
        case 8:
        loading("Sorting A-Z", 150);
        sortUserByUsernameAsc();
        tampilSemuaUserDetail();
        pause();
        break;
            case 9: logout(); return;
            case 10: exit(0);
            default: cout << "Input tidak valid\n"; pause();
        }
    }
}

// ================= MENU CUSTOMER =================
void menuCustomer() {
    while (true) {
        tampilHeader("MENU CUSTOMER");

        cout << "1. Edit Profil\n";
        cout << "2. Pesan Ojek\n";
        cout << "3. Lihat Histori\n";
        cout << "4. Hapus Akun\n";
        cout << "5. Logout\n";
        cout << "6. Keluar\n\n";

        int p = inputMenu(1, 6);

        switch (p) {
            case 1: editProfilSendiri(); break;
            case 2: pesanOjek(); break;
            case 3: lihatHistoriCustomer(); break;
            case 4: hapusAkunSendiri(); return;
            case 5: logout(); return;
            case 6: exit(0);
            default: cout << "Input tidak valid\n"; pause();
        }
    }
}

// ================= MENU DRIVER =================
void menuDriver() {
    while (true) {
        tampilHeader("MENU DRIVER");

        cout << "1. Edit Profil\n";
        cout << "2. Lihat Pendapatan\n";
        cout << "3. Hapus Akun\n";
        cout << "4. Logout\n";
        cout << "5. Keluar\n\n";

        int p = inputMenu(1, 5);

        switch (p) {
            case 1: editProfilSendiri(); break;
            case 2: lihatPendapatanDriver(); break;
            case 3: hapusAkunSendiri(); return;
            case 4: logout(); return;
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

            cout << "1. Login\n";
            cout << "2. Registrasi Customer\n";
            cout << "3. Registrasi Driver\n";
            cout << "4. Keluar\n\n";

            int p = inputMenu(1, 4);

            switch (p) {
                case 1: login(); break;
                case 2: buatAkunRegistrasi("customer"); break;
                case 3: buatAkunRegistrasi("driver"); break;
                case 4: return 0;
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
