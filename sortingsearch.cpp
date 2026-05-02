#define _HAS_STD_BYTE 0 
#include <cstring>
#include "sortingsearch.h"
#include "functions.h"

// SORTING ASC 
void sortUserByUsernameAsc() {
    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = 0; j < jumlahUser - i - 1; j++) {
            if (strcmp(daftarUser[j].username, daftarUser[j + 1].username) > 0) {
                User temp = daftarUser[j];
                daftarUser[j] = daftarUser[j + 1];
                daftarUser[j + 1] = temp;
            }
        }
    }
}

// SORTING DESC 
void sortUserByUsernameDesc() {
    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = 0; j < jumlahUser - i - 1; j++) {
            if (strcmp(daftarUser[j].username, daftarUser[j + 1].username) < 0) {
                User temp = daftarUser[j];
                daftarUser[j] = daftarUser[j + 1];
                daftarUser[j + 1] = temp;
            }
        }
    }
}

// LINEAR SEARCH
int cariUserIndexByUsername(const char* username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

// BINARY search
User* cariUserBinary(const char* username) {
    int left = 0, right = jumlahUser - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(daftarUser[mid].username, username);

        if (cmp == 0) return &daftarUser[mid];
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    return nullptr;
}