#include <iostream>
#include "autentikasi.h"
#include "manajemen_akun.h"
#include "tampilan.h"
#include "sistem_pemesanan.h"
#include "akun.h"

using namespace std;

int main() {

    akunDB["admin"] = {"admin","admin","Admin",20,"0812","admin@mail.com","admin"};

    while (true) {
        if (!apakah_sudah_login()) {
            tampilkan_menu_login();
            string p;
            cin >> p;

            if (p == "1") login();
            else if (p == "2" || p == "3") buat_akun(p);
            else if (p == "4") exit(0);
        } 
        else {
            string role = get_role();

            if (role == "admin") {
                tampilkan_daftar_akun();
                logout();
            }
        }
    }
}