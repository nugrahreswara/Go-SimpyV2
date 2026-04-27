#ifndef VALIDASI_H
#define VALIDASI_H

#include <string>
using namespace std;

bool email_valid(string email);
bool username_terdaftar(string username);
bool nomor_terdaftar(string nomor);
bool email_terdaftar(string email);
int validasi_input_umur(string umur);

#endif