#include "tampilan.h"
#include <iostream>

void tampilkan_menu_login() {
    cout << "\n1. Login\n2. Daftar Customer\n3. Daftar Driver\n4. Exit\n";
}

void tampilkan_menu_utama(string role) {
    cout << "\n=== MENU " << role << " ===\n";
}