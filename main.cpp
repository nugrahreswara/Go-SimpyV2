#include <iostream>
#include "autentikasi.h"
#include "manajemen_akun.h"
#include "tampilan.h"
#include "sistem_pemesanan.h"
#include "akun.h"

using namespace std;

int main() {

    // akun default admin
    akunDB["admin"] = {"admin","admin","Admin",20,"0812","admin@mail.com","admin"};

    while (true) {

        // ================= BELUM LOGIN =================
        if (!apakah_sudah_login()) {
            tampilkan_menu_login();

            string p;
            cin >> p;

            if (p == "1") {
                login();
                if (apakah_sudah_login()) {
                    loading(); // 
                }
            }
            else if (p == "2" || p == "3") {
                buat_akun(p);
            }
            else if (p == "4") {
                exit(0);
            }
        }

        else {
            string role = get_role();
            int pilih;

            tampilkan_menu_utama(role);
            cin >> pilih;

        
            if (role == "admin") {
                switch (pilih) {
                    case 1:
                        tampilkan_daftar_akun();
                        break;
                    case 2:
                        cout << "Fitur belum dibuat\n";
                        break;
                    case 3:
                        logout();
                        break;
                    default:
                        cout << "Pilihan salah!\n";
                }
            }

    
            else if (role == "customer") {
                switch (pilih) {
                    case 1:
                        pesan_layanan();
                        break;
                    case 2:
                        cout << "Riwayat belum dibuat\n";
                        break;
                    case 3:
                        logout();
                        break;
                }
            }

    
            else if (role == "driver") {
                switch (pilih) {
                    case 1:
                        cout << "Lihat order\n";
                        break;
                    case 2:
                        cout << "Update status\n";
                        break;
                    case 3:
                        logout();
                        break;
                }
            }

            system("pause");
        }
    }

    return 0;
}