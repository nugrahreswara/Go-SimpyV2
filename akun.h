#ifndef AKUN_H
#define AKUN_H

#include <string>
#include <map>
using namespace std;

struct Akun {
    string username;
    string password;
    string nama_lengkap;
    int umur;
    string nomor_telepon;
    string alamat_email;
    string role;
};

extern map<string, Akun> akunDB;

#endif