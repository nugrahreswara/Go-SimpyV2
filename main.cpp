#define _HAS_STD_BYTE 0 
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "sortingsearch.h"
using namespace std;

// === MENU ADMIN ===
void menuAdmin() {
    while (true) {
        tampilHeader("MENU ADMIN");

        cout << "1. Edit Profil Saya" << endl;
        cout << "2. Tambah Akun" << endl;
        cout << "3. Edit Akun Lain" << endl;
        cout << "4. Hapus Akun Lain" << endl;
        cout << "5. Lihat Semua Akun" << endl;
        cout << "6. Lihat Semua Transaksi" << endl;
        cout << "7. Cari User" << endl;
        cout << "8. Sort User A-Z" << endl;
        cout << "9. Logout" << endl;
        cout << "10. Keluar" << endl << endl;

        int p = inputMenu(1, 10);

        switch (p) {
            case 1: editProfilSendiri(); break;
            case 2: buatAkunOlehAdmin(); break;
            case 3: editProfilOlehAdmin(); break;
            case 4: hapusAkunOlehAdmin(); break;
            case 5: tampilkanSemuaUser(); break;
            case 6: lihatSemuaTransaksiAdmin(); break;
            case 7: {
                char cari[50];
                cout << "Masukkan username: ";
                cin >> cari;
                cin.ignore();
            
                loading("Mencari user", 150);
            
                int idx = cariUserIndexByUsername(cari);
            
                if (idx != -1) {
                    tampilDetailUser(idx);
                } else {
                    warna(12); cout << "  [!] User Tidak Ditemukan." << endl; resetWarna();
                }
            
                waitEnter();
                break;
            }

            case 8: {
                loading("Sorting A-Z", 150);
                sortUserByUsernameAsc();
                tampilSemuaUserDetail();
                waitEnter();
                break;
            }

            case 9: logout(); return;
            case 10: exit(0);
            default: cout << "Input tidak valid" << endl;
            waitEnter();
        }
    }
}

// === MENU CUSTOMER ===
void menuCustomer() {
    while (true) {
        tampilHeader("MENU CUSTOMER");

        cout << "1. Edit Profil" << endl;
        cout << "2. Pesan Ojek" << endl;
        cout << "3. Lihat Histori" << endl;
        cout << "4. Hapus Akun" << endl;
        cout << "5. Logout" << endl;
        cout << "6. Keluar" << endl << endl;

        int p = inputMenu(1, 6);

        switch (p) {
            case 1: editProfilSendiri(); break;
            case 2: pesanOjek(); break;
            case 3: lihatHistoriCustomer(); break;
            case 4: hapusAkunSendiri(); return;
            case 5: logout(); return;
            case 6: exit(0);
            default: cout << "Input tidak valid" << endl; waitEnter();
        }
    }
}

// === MENU DRIVER ===
void menuDriver() {
    while (true) {
        tampilHeader("MENU DRIVER");

        cout << "1. Edit Profil" << endl;
        cout << "2. Lihat Pendapatan" << endl;
        cout << "3. Hapus Akun" << endl;
        cout << "4. Logout" << endl;
        cout << "5. Keluar" << endl << endl;

        int p = inputMenu(1, 5);

        switch (p) {
            case 1: editProfilSendiri(); break;
            case 2: lihatPendapatanDriver(); break;
            case 3: hapusAkunSendiri(); return;
            case 4: logout(); return;
            case 5: exit(0);
            default: cout << "Input tidak valid" << endl; waitEnter();
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

    // Inisialisasi user customer default
        User customer;
        strcpy(customer.username, "customer");
        strcpy(customer.password, "customer");
        strcpy(customer.namaLengkap, "Customer");
        strcpy(customer.role, "customer");
        customer.aktif = true;
        daftarUser[jumlahUser++] = customer;

    // Inisialisasi user driver default
        User driver;
        strcpy(driver.username, "driver");
        strcpy(driver.password, "driver");
        strcpy(driver.namaLengkap, "driver");
        strcpy(driver.role, "driver");
        driver.aktif = true;
        daftarUser[jumlahUser++] = driver;
    }

    inisialisasiFileCSV();
    inisialisasiFileLokasi();
    srand(time(0));

    while (true) {

        // === BELUM LOGIN ===
        if (!isLogin()) {
            tampilHeader("MENU LOGIN");

            cout << "1. Login" << endl;
            cout << "2. Registrasi Customer" << endl;
            cout << "3. Registrasi Driver" << endl;
            cout << "4. Keluar" << endl << endl;

            int p = inputMenu(1, 4);

            switch (p) {
                case 1: login(); break;
                case 2: buatAkunRegistrasi("customer"); break;
                case 3: buatAkunRegistrasi("driver"); break;
                case 4: return 0;
                default:
                    cout << "Input tidak valid" << endl;
                    waitEnter();
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
