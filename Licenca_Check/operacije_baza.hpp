#ifndef OPERACIJE_BAZA_HPP_INCLUDED
#define OPERACIJE_BAZA_HPP_INCLUDED
#include <string>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include <fcntl.h>
#include "linux/rtc.h"
#include "sys/ioctl.h"
#include <sys/types.h>
#include "unistd.h"

#define OZNAKA_KRAJA_DATOTEKE -1

using namespace std;
typedef struct{
    unsigned int sati;
    unsigned int minuti;
    unsigned int sekunde;
    unsigned int dan;
    unsigned int mesec;
    unsigned int godina;
}VREME;

typedef struct Slog {
	int eviBroj; //koristi se kao kljuc sloga
	char kljuc[7+1];
	VREME vreme;
	int deleted;
} SLOG;


FILE *otvoriDatoteku(const char *filename);
SLOG *pronadjiSlog(FILE *fajl, int evidBroj);
void dodajSlog(FILE *fajl, SLOG *slog);
void ispisiSveSlogove(FILE *fajl);
void ispisiSlog(SLOG *slog);
void update_vreme(VREME &vreme);
void obrisiSlogLogicki(FILE *fajl, int evidBroj);



#endif // OPERACIJE_BAZA_HPP_INCLUDED
