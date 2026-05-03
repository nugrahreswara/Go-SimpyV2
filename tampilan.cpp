#define _HAS_STD_BYTE 0
#include "tampilan.h"
#include <windows.h>
#include <iostream>
#include <limits>
using namespace std;

static HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

// === WARNA ===
void warna(int fg) { SetConsoleTextAttribute(hCon, fg); }
void resetWarna()  { SetConsoleTextAttribute(hCon, 7);  }

#define W_KUNING  14
#define W_CYAN    11
#define W_HIJAU   10
#define W_MERAH   12
#define W_PUTIH   15
#define W_ABU      7

// === KOMPONEN UI ===
void garis() {
    warna(W_KUNING);
    cout << "  =========================================\n";
    resetWarna();
}

void garisDouble() {
    warna(W_KUNING);
    cout << "  =========================================\n";
    resetWarna();
}

void tampilHeader(const char* judul) {
    system("cls");
    warna(W_KUNING);
    cout << "\n  +-----------------------------------------+\n";
    cout << "  |         GO-SIMPY  ~  Ojek Sederhana    |\n";
    cout << "  +-----------------------------------------+\n";
    cout << "  |  ";
    warna(W_PUTIH);
    cout << judul;
    int pad = 41 - (int)strlen(judul);
    for (int i = 0; i < pad; i++) cout << " ";
    warna(W_KUNING);
    cout << "|\n";
    cout << "  +-----------------------------------------+\n\n";
    resetWarna();
}

void loading(const char* text, int delay) {
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(hCon, &ci);
    warna(W_CYAN);
    for (int i = 0; i < 6; i++) {
        cout << "\r  " << text;
        for (int j = 0; j <= (i % 4); j++) cout << " .";
        for (int j = (i % 4); j < 4; j++) cout << "   ";
        cout << flush;
        Sleep(delay);
    }
    warna(W_HIJAU);
    cout << "\r  " << text << " Selesai!            \n";
    resetWarna();
    ci.bVisible = TRUE;
    SetConsoleCursorInfo(hCon, &ci);
    Sleep(200);
}

void loadingBar(const char* text, int total, int delay) {
    warna(W_CYAN);
    cout << "\n  " << text << "\n  [";
    warna(W_HIJAU);
    for (int i = 0; i < total; i++) {
        cout << "#" << flush;
        Sleep(delay);
    }
    warna(W_CYAN);
    cout << "] Done!\n";
    resetWarna();
}

void menuItem(int n, const char* teks) {
    warna(W_CYAN);  cout << "  [";
    warna(W_KUNING); cout << n;
    warna(W_CYAN);  cout << "] ";
    resetWarna();    cout << teks << "\n";
}

void pause() {
    warna(W_KUNING);
    cout << "\n  Tekan Enter untuk lanjut...";
    resetWarna();
    cin.ignore();
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
            cout << "  Input harus angka!\n";
            resetWarna();
            continue;
        }
        if (pilihan < min || pilihan > max) {
            warna(W_MERAH);
            cout << "  Pilihan harus antara " << min << " - " << max << "\n";
            resetWarna();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return pilihan;
    }
}

//  TAMPIL DATA USER 
void tampilDetailUser(int idx) {
    if (idx < 0 || idx >= jumlahUser) {
        warna(W_MERAH);
        cout << "  User tidak ditemukan.\n";
        resetWarna();
        return;
    }
    User u = daftarUser[idx];
    warna(W_KUNING);
    cout << "\n  +-------------------------------------+\n";
    warna(W_CYAN);
    cout << "  | ";  warna(W_PUTIH); cout << "Username  : "; warna(W_HIJAU); cout << u.username;
    int pad = 24 - strlen(u.username);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|\n";

    cout << "  | ";  warna(W_PUTIH); cout << "Nama      : "; warna(W_ABU); cout << u.namaLengkap;
    pad = 24 - strlen(u.namaLengkap);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|\n";

    cout << "  | ";  warna(W_PUTIH); cout << "Telepon   : "; warna(W_ABU); cout << u.nomorTelepon;
    pad = 24 - strlen(u.nomorTelepon);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|\n";

    const char* email = strlen(u.alamatEmail) ? u.alamatEmail : "-";
    cout << "  | ";  warna(W_PUTIH); cout << "Email     : "; warna(W_ABU); cout << email;
    pad = 24 - strlen(email);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|\n";

    cout << "  | ";  warna(W_PUTIH); cout << "Alamat    : "; warna(W_ABU); cout << u.alamat;
    pad = 24 - strlen(u.alamat);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|\n";

    cout << "  | ";  warna(W_PUTIH); cout << "Role      : "; warna(W_CYAN); cout << u.role;
    pad = 24 - strlen(u.role);
    for(int i=0;i<pad;i++) cout<<" ";
    warna(W_KUNING); cout << "|\n";
    cout << "  +-------------------------------------+\n";
    resetWarna();
}

void tampilSemuaUserDetail() {
    for (int i = 0; i < jumlahUser; i++) {
        tampilDetailUser(i);
    }
}
