#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include "operacije_baza.hpp"
#define DUZINA 3 //Duzina koliko meseci traje trail period max 12
using namespace std;
void start(VREME &vreme, FILE* file);
void check(FILE *file);
int main()
{
    VREME vreme;
    
    // Path gde zelite da se kreira baza podataka, preporuka negde u system fajlovima
    string path = "/home/pc/Documents/linux-trial-period/Licenca/test.dat";
    while(true){
        FILE* file = otvoriDatoteku(path.c_str());
        start(vreme,file);
        sleep(60);
    }
    return 0;
}
void start(VREME &vreme, FILE* file){
    update_vreme(vreme);
    SLOG *slog = pronadjiSlog(file,111);
    if( slog == NULL){
        SLOG tmp;
        char kljuc[7+1];
        fflush(stdin);
        cout << "Unesite kljuc (7 karaktera): ";
        scanf("%s",kljuc);
        tmp.eviBroj = 111;
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
        fclose(file);

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
    // Path do Licenca_Check.exe fajla da bi pokrenuo sledecu aplikaciju
    system("shutdown -r +30");
    system("xterm -hold -e '/home/pc/Documents/linux-trial-period/Licenca_Check/licenca_check'");
    
}

