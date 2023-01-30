#include <iostream>
#include <thread>
#include "operacije_baza.hpp"
using namespace std;
void restart(FILE *file);
int main()
{
    char kljuc[7+1];
    // Path do baze podataka- preporuka je da bude negde u fajlovima systema
    // Mora biti isti path kao u Licenca/main.c fajlu
    string path = "/home/pc/Documents/linux-trial-period/Licenca/test.dat";
    FILE* file = otvoriDatoteku(path.c_str());
    SLOG *tmp = pronadjiSlog(file,111);
    if(tmp == NULL){
        cout << "Ne postoji zadati kljuc" << endl;
        return -1;
    }
    do{
        cout<<"Unesite kljuc: ";
        fflush(stdin);
        scanf("%s",kljuc);
        if(strcmp(kljuc,tmp->kljuc) == 0){
            cout << "Uspesno unet kljuc" << endl;
            // Ovde treba promeniti nazive servisa ako zelite
            obrisiSlogLogicki(file,111);
            system("shutdown -c");
            break;
        }else{
            cout << "Pogresan kljuc" << endl;
        }

    }while(true);
    fclose(file);
    return 0;
}


