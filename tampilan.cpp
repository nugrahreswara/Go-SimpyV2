#define _HAS_STD_BYTE 0
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
#include <limits>
#include <cstring>
#include <cstdlib>
#include "tampilan.h"

using namespace std;

// === WARNA ===
#ifdef _WIN32
    static HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    
    void warna(int fg) { SetConsoleTextAttribute(hCon, fg); }
    void resetWarna()  { SetConsoleTextAttribute(hCon, 7);  }
#else
    void warna(int fg) {
        switch(fg) {
            case 14: cout << "\033[33m"; break; // kuning
            case 11: cout << "\033[36m"; break; // cyan
            case 10: cout << "\033[32m"; break; // hijau
            case 12: cout << "\033[31m"; break; // merah
            case 15: cout << "\033[37m"; break; // putih
            case 7:  cout << "\033[0m";  break; // reset
            default: cout << "\033[0m"; break;
        }
    }
    void resetWarna() { cout << "\033[0m"; }
#endif

#define W_KUNING  14
#define W_CYAN    11
#define W_HIJAU   10
#define W_MERAH   12
#define W_PUTIH   15
#define W_ABU      7

// === KOMPONEN UI ===
void garis() {
    warna(W_KUNING);
    cout << "  =========================================" << endl;
    resetWarna();
}

void garisDouble() {
    warna(W_KUNING);
    cout << "  =========================================" << endl;
    resetWarna();
}

void tampilHeader(const char* judul) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    warna(W_KUNING);
    cout <<
    endl << "  +-----------------------------------------+" << endl;
    cout << "  |         GO-SIMPY  ~  Ojek Sederhana     |" << endl;
    cout << "  +-----------------------------------------+" << endl;
    cout << "  |";
    warna(W_PUTIH);
    cout << judul;
    int pad = 41 - (int)strlen(judul);
    for (int i = 0; i < pad; i++) cout << " ";
    warna(W_KUNING);
    cout << "|" << endl;
    cout << "  +-----------------------------------------+" << endl << endl;
    resetWarna();
}

void loading(const char* text, int delay) {
    #ifdef _WIN32
        CONSOLE_CURSOR_INFO ci = {1, FALSE};
        SetConsoleCursorInfo(hCon, &ci);
    #endif
    warna(W_CYAN);

    for (int i = 0; i < 6; i++) {
        cout << "\r  " << text;
        for (int j = 0; j <= (i % 4); j++) {
            cout << " .";
        }

        for (int j = (i % 4); j < 4; j++) {
            cout << "   ";
        }

        cout << flush;
        #ifdef _WIN32
            Sleep(delay);
        #else
            usleep(delay * 1000);
        #endif
    }

    warna(W_HIJAU); cout << "\r  " << text << " Selesai!            " << endl; resetWarna();
    #ifdef _WIN32
        ci.bVisible = TRUE;
        SetConsoleCursorInfo(hCon, &ci);
        Sleep(200);
    #else
        usleep(200000);
    #endif
}

void loadingBar(const char* text, int total, int delay) {
    warna(W_CYAN);
    cout << endl << "  " << text << endl << "  [";
    warna(W_HIJAU);

    for (int i = 0; i < total; i++) {
        cout << "#" << flush;
        #ifdef _WIN32
                Sleep(delay);
        #else
                usleep(delay * 1000);
        #endif
    }

    warna(W_CYAN);
    cout << "] Done!" << endl;
    resetWarna();
}

void menuItem(int n, const char* teks) {
    warna(W_CYAN);  cout << "  [";
    warna(W_KUNING); cout << n;
    warna(W_CYAN);  cout << "] ";
    resetWarna();    cout << teks << endl;
}

// ganti nama dari pause()
void waitEnter() { 
    warna(W_KUNING);
    cout << endl << "  Tekan Enter untuk lanjut...";
    resetWarna();
    cin.get();
}

int inputMenu(int min, int max) {
    int pilihan;
    while (true) {
        warna(W_KUNING);
        cout << "  Pilih: ";
        resetWarna();
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            warna(W_MERAH);
            cout << "  Input harus angka!" << endl;
            resetWarna();
            continue;
        }

        if (pilihan < min || pilihan > max) {
            warna(W_MERAH);
            cout << "  Pilihan harus antara " << min << " - " << max << endl;
            resetWarna();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return pilihan;
    }
}

// TAMPIL DATA USER 
void tampilDetailUser(int idx) {
    if (idx < 0 || idx >= jumlahUser) {
        warna(W_MERAH);
        cout << "  User tidak ditemukan." << endl;
        resetWarna();
        return;
    }

    User u = daftarUser[idx];
    warna(W_KUNING);
    cout << endl << "  +-------------------------------------+" << endl;
    warna(W_CYAN);
    cout << "  | ";  warna(W_PUTIH); cout << "Username  : "; warna(W_HIJAU); cout << u.username;
    int pad = 24 - (int)strlen(u.username);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|" << endl;

    cout << "  | ";  warna(W_PUTIH); cout << "Nama      : "; warna(W_ABU); cout << u.namaLengkap;
    pad = 24 - (int)strlen(u.namaLengkap);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|" << endl;

    cout << "  | ";  warna(W_PUTIH); cout << "Telepon   : "; warna(W_ABU); cout << u.nomorTelepon;
    pad = 24 - (int)strlen(u.nomorTelepon);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|" << endl;

    const char* email = (strlen(u.alamatEmail) ? u.alamatEmail : "-");
    cout << "  | ";  warna(W_PUTIH); cout << "Email     : "; warna(W_ABU); cout << email;
    pad = 24 - (int)strlen(email);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|" << endl;

    cout << "  | ";  warna(W_PUTIH); cout << "Alamat    : "; warna(W_ABU); cout << u.alamat;
    pad = 24 - (int)strlen(u.alamat);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|" << endl;

    cout << "  | ";  warna(W_PUTIH); cout << "Role      : "; warna(W_CYAN); cout << u.role;
    pad = 24 - (int)strlen(u.role);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|" << endl;
    cout << "  +-------------------------------------+" << endl;
    resetWarna();
}

void tampilSemuaUserDetail() {
    for (int i = 0; i < jumlahUser; i++) {
        tampilDetailUser(i);
    }
}
