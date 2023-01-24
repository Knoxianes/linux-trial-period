#include "operacije_baza.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
void update_vreme(VREME &vreme){


    int fd;
    struct rtc_time rtc_tm;

    fd = open("/dev/rtc0", O_RDONLY);
    if (fd == -1) {
        perror("/dev/rtc0");
        return;
    }

    if (ioctl(fd, RTC_RD_TIME, &rtc_tm) == -1) {
        perror("ioctl");
        return;
    }
    vreme.sati = rtc_tm.tm_hour;
    vreme.minuti = rtc_tm.tm_min;
    vreme.sekunde = rtc_tm.tm_sec;
    vreme.dan = rtc_tm.tm_mday;
    vreme.mesec = rtc_tm.tm_mon+1;
    vreme.godina = rtc_tm.tm_year + 1900;

    close(fd);

}
FILE *otvoriDatoteku(const char *filename){
    FILE* file = fopen(filename,"rb+");
    if(file == NULL){
        file = fopen(filename,"wb");
        SLOG blok;
		blok.eviBroj = OZNAKA_KRAJA_DATOTEKE;
		fwrite(&blok, sizeof(SLOG), 1, file);
        return file;
    }else{
        return file;
    }
}
SLOG *pronadjiSlog(FILE *fajl, int evidBroj){
    if (fajl == NULL) {
		return NULL;
	}
    fseek(fajl, 0, SEEK_SET);
	SLOG blok;
	while (fread(&blok, sizeof(SLOG), 1, fajl)){
        if(blok.eviBroj == OZNAKA_KRAJA_DATOTEKE){
            return NULL;
        }else{
            if(blok.eviBroj == evidBroj){
                SLOG *tmp = (SLOG*)malloc(sizeof(SLOG));
                memcpy(tmp, &blok, sizeof(SLOG));
				return tmp;
            }
        }
	}
	return NULL;
}
void dodajSlog(FILE *fajl, SLOG *slog){
    if (fajl == NULL) {
		return;
	}
    SLOG *slogStari = pronadjiSlog(fajl, slog->eviBroj);
	if (slogStari != NULL) {
        return;
    }

    SLOG blok;
	fseek(fajl, -sizeof(SLOG), SEEK_END);
	fread(&blok, sizeof(SLOG), 1, fajl);
	if (blok.eviBroj == OZNAKA_KRAJA_DATOTEKE) {
            //Ovo je mesto gde se nalazi slog sa oznakom
            //kraja datoteke; tu treba upisati novi slog.
			memcpy(&blok, slog, sizeof(SLOG));

		}
    fseek(fajl, -sizeof(SLOG), SEEK_CUR);
    fwrite(&blok, sizeof(SLOG), 1, fajl);
    SLOG noviBlok;
    noviBlok.eviBroj = OZNAKA_KRAJA_DATOTEKE;
    fwrite(&noviBlok, sizeof(SLOG), 1, fajl);
    fflush(fajl);
}
void ispisiSlog(SLOG *slog){
    printf("%3d      %7s    %02d-%02d-%4d %02d:%02d",
        slog->eviBroj,
        slog->kljuc,
		slog->vreme.dan,
		slog->vreme.mesec,
		slog->vreme.godina,
		slog->vreme.sati,
		slog->vreme.minuti
		);
}
void ispisiSveSlogove(FILE *fajl){
    if (fajl == NULL) {
		return;
	}

	fseek(fajl, 0, SEEK_SET);
	SLOG blok;
	int rbBloka = 0;
	printf("BL Evid.Br   Kljuc      Dat.Vrem\n");
	while (fread(&blok, sizeof(SLOG), 1, fajl)) {
			if (blok.eviBroj == OZNAKA_KRAJA_DATOTEKE) {
				printf("B%d *\n", rbBloka);
                break;
			}
			if (!blok.deleted) {
                printf("B%d ", rbBloka);
                ispisiSlog(&blok);
                printf("\n");
            }
    }
    rbBloka++;
}
void obrisiSlogLogicki(FILE *fajl, int evidBroj) {
	if (fajl == NULL) {
		printf("Datoteka nije otvorena!\n");
		return;
	}
	fseek(fajl, 0, SEEK_SET);
	SLOG blok;
	while (fread(&blok, sizeof(SLOG), 1, fajl)) {
            if (blok.eviBroj == OZNAKA_KRAJA_DATOTEKE) {
                printf("Nema tog sloga u datoteci\n");
                return;
            }

			if (blok.eviBroj == evidBroj && blok.deleted != 1) {

				blok.deleted = 1;
				fseek(fajl, -sizeof(SLOG), SEEK_CUR);
				fwrite(&blok, sizeof(SLOG), 1, fajl);
				fflush(fajl);
				return;
			}
		}
}
