#include "autentikasi.h"
#include "akun.h"
#include <iostream>

bool sudahLogin = false;
string currentUser = "";
string roleUser = "";

void login() {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (akunDB.count(user) && akunDB[user].password == pass) {
        sudahLogin = true;
        currentUser = user;
        roleUser = akunDB[user].role;
        cout << "Login berhasil\n";
    } else {
        cout << "Login gagal\n";
    }
}

void logout() {
    sudahLogin = false;
    currentUser = "";
    roleUser = "";
}

bool apakah_sudah_login() {
    return sudahLogin;
}

string apa_akun_sekarang() {
    return currentUser;
}

string get_role() {
    return roleUser;
}