#include "functions.h"

void menuAdmin() {
    int pilihan;
    do {
        clearScreen();
        std::cout << "=== MENU ADMIN ===" << std::endl;
        std::cout << "1. Edit Profil Saya" << std::endl;
        std::cout << "2. Tambah Akun (Customer/Driver/Admin)" << std::endl;
        std::cout << "3. Edit Akun Lain" << std::endl;
        std::cout << "4. Hapus Akun Lain" << std::endl;
        std::cout << "5. Lihat Semua Akun" << std::endl;
        std::cout << "6. Lihat Semua Transaksi" << std::endl;
        std::cout << "7. Logout" << std::endl;
        std::cout << "8. Keluar" << std::endl;
        std::cout << "Pilih: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1: editProfilSendiri(); break;
            case 2: buatAkunOlehAdmin(); break;
            case 3: editProfilOlehAdmin(); break;
            case 4: hapusAkunOlehAdmin(); break;
            case 5: tampilkanSemuaUser(); break;
            case 6: lihatSemuaTransaksiAdmin(); break;
            case 7: logout(); return;
            case 8: std::cout << "Terima kasih." << std::endl; exit(0);
            default: std::cout << "Pilihan salah." << std::endl; std::cin.ignore(); std::cin.get();
        }
    }

    while (true);
}

void menuCustomer() {
    int pilihan;
    do {
        clearScreen();
        std::cout << "=== MENU CUSTOMER ===" << std::endl;
        std::cout << "1. Edit Profil" << std::endl;
        std::cout << "2. Pesan Ojek" << std::endl;
        std::cout << "3. Lihat Histori Pemesanan" << std::endl;
        std::cout << "4. Hapus Akun Saya" << std::endl;
        std::cout << "5. Logout" << std::endl;
        std::cout << "6. Keluar" << std::endl;
        std::cout << "Pilih: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1: editProfilSendiri(); break;
            case 2: pesanOjek(); break;
            case 3: lihatHistoriCustomer(); break;
            case 4: hapusAkunSendiri(); return;
            case 5: logout(); return;
            case 6: std::cout << "Terima kasih." << std::endl; exit(0);
            default: std::cout << "Pilihan salah." << std::endl; std::cin.ignore(); std::cin.get();
        }
    } while (true);
}

void menuDriver() {
    int pilihan;
    do {
        clearScreen();
        std::cout << "=== MENU DRIVER ===" << std::endl;
        std::cout << "1. Edit Profil" << std::endl;
        std::cout << "2. Lihat Pendapatan" << std::endl;
        std::cout << "3. Hapus Akun Saya" << std::endl;
        std::cout << "4. Logout" << std::endl;
        std::cout << "5. Keluar" << std::endl;
        std::cout << "Pilih: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1: editProfilSendiri(); break;
            case 2: lihatPendapatanDriver(); break;
            case 3: hapusAkunSendiri(); return;
            case 4: logout(); return;
            case 5: std::cout << "Terima kasih." << std::endl; exit(0);
            default: std::cout << "Pilihan salah." << std::endl; std::cin.ignore(); std::cin.get();
        }
    } while (true);
}

int main() {

<<<<<<< HEAD
    // akun default admin
    akunDB["admin"] = {"admin","admin","Admin",20,"0812","admin@mail.com","admin"};
=======
    // Inisialisasi akun default jika belum ada
    if (jumlahUser == 0) {
        User admin;
        strcpy(admin.username, "admin");
        strcpy(admin.password, "admin");
        strcpy(admin.namaLengkap, "Administrator");
        strcpy(admin.nomorTelepon, "081234567890");
        strcpy(admin.alamatEmail, "admin@gosimpy.com");
        strcpy(admin.alamat, "Kantor Pusat");
        strcpy(admin.role, "admin");
        admin.aktif = true;
        daftarUser[jumlahUser++] = admin;
>>>>>>> 6206245dd6cca03769c1158c3fef2680d796f0e9

        User cust;
        strcpy(cust.username, "customer-01");
        strcpy(cust.password, "customer-01");
        strcpy(cust.namaLengkap, "David Wijaya");
        strcpy(cust.nomorTelepon, "081234567891");
        strcpy(cust.alamatEmail, "customer-01@gosimpy.com");
        strcpy(cust.alamat, "Jl. Merdeka No. 10");
        strcpy(cust.role, "customer");
        cust.aktif = true;
        daftarUser[jumlahUser++] = cust;

        User driver;
        strcpy(driver.username, "driver-01");
        strcpy(driver.password, "driver-01");
        strcpy(driver.namaLengkap, "Herman Sanjaya");
        strcpy(driver.nomorTelepon, "081234567892");
        strcpy(driver.alamatEmail, "driver-01@gosimpy.com");
        strcpy(driver.alamat, "Jl. Sudirman No. 5");
        strcpy(driver.role, "driver");
        driver.aktif = true;
        daftarUser[jumlahUser++] = driver;
    }

    inisialisasiFileCSV();
    srand(time(0));

    int pilihan;
    while (true) {
<<<<<<< HEAD

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
=======
        if (!isLogin()) {
            clearScreen();
            std::cout << "=== MENU LOGIN ===" << std::endl;
            std::cout << "1. Login" << std::endl;
            std::cout << "2. Registrasi Customer" << std::endl;
            std::cout << "3. Registrasi Driver" << std::endl;
            std::cout << "4. Keluar" << std::endl;
            std::cout << "Pilih: ";
            std::cin >> pilihan;

            switch (pilihan) {
                case 1: login(); break;
                case 2: buatAkunRegistrasi("customer"); break;
                case 3: buatAkunRegistrasi("driver"); break;
                case 4: std::cout << "Terima kasih." << std::endl; return 0;
                default: std::cout << "Pilihan salah." << std::endl; std::cin.ignore(); std::cin.get();
            }
        }

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
>>>>>>> 6206245dd6cca03769c1158c3fef2680d796f0e9
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
<<<<<<< HEAD

    return 0;
}
=======
    return 0;
}
>>>>>>> 6206245dd6cca03769c1158c3fef2680d796f0e9
