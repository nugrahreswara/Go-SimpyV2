#define _HAS_STD_BYTE 0
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "functions.h"
#include "utils.h"

using namespace std;

bool usernameTerdaftar(const char* username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0)
            return true;
    }
    return false;
}

bool nomorTerdaftar(const char* nomor) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].nomorTelepon, nomor) == 0)
            return true;
    }
    return false;
}

bool emailTerdaftar(const char* email) {
    if (strlen(email) == 0) return false;
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].alamatEmail, email) == 0)
            return true;
    }
    return false;
}

bool validasiUsername(const char* username) {
    int len = strlen(username);
    if (len < 3 || len > 15) return false;
    if (!((username[0] >= 'a' && username[0] <= 'z') ||
          (username[0] >= 'A' && username[0] <= 'Z')))
        return false;
    for (int i = 0; i < len; i++) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') || c == '_' || c == '-'))
            return false;
    }
    return true;
}

bool validasiNomorTelepon(const char* nomor) {
    int panjangNomor = strlen(nomor);
    if (panjangNomor < 10 || panjangNomor > 15) return false;
    if (nomor[0] != '0' && nomor[0] != '8') return false;

    bool angkaMuncul[10] = {};
    int jumlahAngkaUnik = 0;
    for (int i = 0; i < panjangNomor; i++) {
        if (nomor[i] < '0' || nomor[i] > '9') return false;
        int nilaiAngka = nomor[i] - '0';
        if (!angkaMuncul[nilaiAngka]) {
            angkaMuncul[nilaiAngka] = true;
            jumlahAngkaUnik++;
        }
    }
    return jumlahAngkaUnik >= 4;
}

bool validasiEmail(const char* email) {
    if (strlen(email) == 0) return true;

    int panjangEmail = strlen(email);
    int posisiAt = -1;
    int jumlahAt = 0;
    for (int i = 0; i < panjangEmail; i++) {
        if (email[i] == '@') { posisiAt = i; jumlahAt++; }
    }

    if (jumlahAt != 1 || posisiAt == 0 || posisiAt == panjangEmail - 1)
        return false;
    if (email[0] == '.' || email[posisiAt - 1] == '.') return false;
    for (int i = 0; i < posisiAt; i++) {
        if (email[i] == '.' && email[i + 1] == '.') return false;
    }

    bool adaTitikDiDomain = false;
    for (int i = posisiAt + 1; i < panjangEmail; i++) {
        if (email[i] == '.') {
            if (i == posisiAt + 1 || i == panjangEmail - 1) return false;
            if (email[i - 1] == '.') return false;
            adaTitikDiDomain = true;
        }
    }
    return adaTitikDiDomain;
}

bool validasiNama(const char* nama) {
    int len = strlen(nama);
    if (len < 3 || len > 50) return false;
    if (nama[0] == ' ' || nama[len - 1] == ' ') return false;
    for (int i = 0; i < len - 1; i++) {
        if (nama[i] == ' ' && nama[i + 1] == ' ') return false;
    }
    for (int i = 0; i < len; i++) {
        char c = nama[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' '))
            return false;
    }
    bool adaSpasi = false;
    for (int i = 1; i < len - 1; i++) {
        if (nama[i] == ' ') { adaSpasi = true; break; }
    }
    return adaSpasi;
}

bool validasiPassword(const char* password) {
    int len = strlen(password);
    if (len < 8 || len > 20) return false;
    bool hurufBesar=false, hurufKecil=false, angka=false, simbol=false;
    for (int i = 0; i < len; i++) {
        char c = password[i];
        if (c>='A'&&c<='Z') hurufBesar=true;
        else if (c>='a'&&c<='z') hurufKecil=true;
        else if (c>='0'&&c<='9') angka=true;
        else if (c=='!'||c=='@'||c=='#'||c=='$'||c=='%'||c=='_'||c=='-'||c=='.') simbol=true;
        else return false;
    }
    return hurufBesar && hurufKecil && angka && simbol;
}

bool validasiAlamat(const char* alamat) {
    int len = strlen(alamat);
    if (len < 5) return false;
    bool adaHuruf = false;
    for (int i = 0; i < len; i++) {
        char c = alamat[i];
        if ((c>='a'&&c<='z')||(c>='A'&&c<='Z')) adaHuruf = true;
        else if (!((c>='0'&&c<='9')||c==' '||c=='.'||c==','||c=='-'||c=='/'||c=='('||c==')'))
            return false;
    }
    return adaHuruf;
}
