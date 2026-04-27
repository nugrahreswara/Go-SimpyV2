#include "validasi.h"
#include "akun.h"

bool email_valid(string email) {
    return email.find("@") != string::npos && email.find(".") != string::npos;
}

bool username_terdaftar(string username) {
    return akunDB.count(username);
}

bool nomor_terdaftar(string nomor) {
    for (auto &a : akunDB)
        if (a.second.nomor_telepon == nomor) return true;
    return false;
}

bool email_terdaftar(string email) {
    for (auto &a : akunDB)
        if (a.second.alamat_email == email) return true;
    return false;
}

int validasi_input_umur(string umurStr) {
    try {
        int umur = stoi(umurStr);
        if (umur >= 13 && umur <= 100) return umur;
    } catch (...) {}
    return -1;
}