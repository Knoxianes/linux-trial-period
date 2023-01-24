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
    string path = "/root/Desktop/Licenca/test.dat";
    FILE* file = otvoriDatoteku(path.c_str());
    SLOG *tmp = pronadjiSlog(file,111);
    if(tmp == NULL){
        cout << "Ne postoji zadati kljuc" << endl;
        return -1;
    }
    thread t1(restart,file);
    t1.detach();
    do{
        cout<<"Unesite kljuc: ";
        fflush(stdin);
        scanf("%s",kljuc);
        if(strcmp(kljuc,tmp->kljuc) == 0){
            cout << "Uspesno unet kljuc" << endl;
            // OVDE TREBA DA STOJI FUNCKIJA KOJA CE DA DISEJBLUJE SERVICE
            system("service serice_name stop");
            system("systemctl disable service_name");
            obrisiSlogLogicki(file,111);
            terminate();
            break;
        }else{
            cout << "Pogresan kljuc" << endl;
        }

    }while(true);
    fclose(file);
    return 0;
}
void restart(FILE* file){
    sleep(1800);
    fclose(file);
    system("reboot -h now");
}

