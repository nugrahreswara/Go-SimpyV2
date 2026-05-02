#ifndef SORTINGSEARCH_H
#define SORTINGSEARCH_H

#include "functions.h"


void sortUserByUsernameAsc();
void sortUserByUsernameDesc();

int cariUserIndexByUsername(const char* username);
User* cariUserBinary(const char* username);

#endif