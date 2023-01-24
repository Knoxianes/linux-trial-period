#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include "operacije_baza.hpp"
#define DUZINA 3
using namespace std;
void start(VREME &vreme, FILE* file);
void check(FILE *file);
int main()
{
    VREME vreme;
    string path = "/root/Desktop/ProjekatCNC/Licenca/test.dat";
    FILE* file = otvoriDatoteku(path.c_str());
    start(vreme,file);
    return 0;
}
void start(VREME &vreme, FILE* file){
    update_vreme(vreme);
    SLOG *slog = pronadjiSlog(file,111);
    if( slog == NULL){
        SLOG tmp;
        int eviBroj;
        char kljuc[7+1];
        fflush(stdin);
        cout << "Unesite kljuc (7 karaktera): ";
        scanf("%s",kljuc);
        cout << "Unesite eviBroj: ";
        fflush(stdin);
        scanf("%d", &eviBroj);
        tmp.eviBroj = eviBroj;
        strcpy(tmp.kljuc,kljuc);
        tmp.vreme.dan = vreme.dan;
        tmp.vreme.sati = vreme.sati;
        tmp.vreme.minuti = vreme.minuti;
        if(vreme.mesec <= 12 - DUZINA){
            tmp.vreme.mesec = vreme.mesec + DUZINA;
            tmp.vreme.godina = vreme.godina;
        }else{
            tmp.vreme.mesec = vreme.mesec + DUZINA - 12;
            tmp.vreme.godina = vreme.godina + 1;
        }
        dodajSlog(file,&tmp);

    }else{
        if(slog->vreme.godina <= vreme.godina && slog->vreme.mesec <= vreme.mesec && slog->vreme.dan <= vreme.dan && slog->vreme.sati <= vreme.sati && slog->vreme.minuti < vreme.minuti && slog->deleted != 1){
            thread t1(check,file);
            t1.join();
        }else{
            fclose(file);
        }
    }
}
void check(FILE* file){
    fclose(file);
    system("xterm -hold -e \"/root/Desktop/ProjekatCNC/Licenca_Check/bin/Debug/Licenca_Check\"");
}

