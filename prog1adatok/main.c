#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prog1adatok.h"
#include "debugmalloc.h"
/*22.sor*/
#ifdef _WIN32
    #include <windows.h>
#endif
/*A fuggveny kinyit egy fajlt es ha nem fogyott el a memoria, visszateriti.Parameterként a fajl nevet és azt kell megadni, hogy olvasasra vagy irasra hasznaljuk.*/
FILE* file_opening(char const *fajlnev, char const *olvasas_vagy_iras)
{
    FILE *olvasnivalo=fopen(fajlnev,olvasas_vagy_iras);
    if (olvasnivalo == NULL)
    {
        perror("Fajl megnyitása sikertelen");
        return 0;
    }
    return olvasnivalo;
}
void csoport_generalas()
{
    FILE *csoport_iras=file_opening("csoportok.txt","w");
    char eloadasos[2],gyakorlatos[25];
    int eloadasdb[2]={0};
    int gyakorlatdb[25]={0};
    int rand_elm,rand_gyak;
    for(int i=0;i<700;i++)
    {
        rand_elm=rand()%2;
        rand_gyak=rand()%25;
        eloadasdb[rand_elm]++;
        gyakorlatdb[rand_gyak]++;
        while(eloadasdb[rand_elm]>250){ rand_elm=rand()%2;eloadasdb[rand_elm]++;}
        while(gyakorlatdb[rand_gyak]>28){ rand_gyak=rand()%25;gyakorlatdb[rand_gyak]++;}
        fprintf(csoport_iras,"E%d G%d\n",rand_elm+1,rand_gyak+1);
    }

}
int main()
{
    /*Ezeknek a soroknak a celja, hogy a kimenetrol beolvashatoak és a kimenetre kiirhatoak legyenek magyar betuk is,ami a Windows-1250 kodolással erheto el.*/
    #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif
    FILE *f_hallgatok= file_opening("hallgatoadatok.txt","r");
    Diak_Profil osszesdiak[700];/* atlagosan 700 diak kerül a ,BME VIK mernokinformatikus szakara az utobbi evek adatai alapjan*/
    for(int i=0;i<700;i++) fgets(osszesdiak[i].teljes_nev,50,f_hallgatok);
    for(int j=0;j<700;j++) fgets(osszesdiak[j].Neptun_kod,7,f_hallgatok);
     for(int j=0;j<700;j++) printf("%s",osszesdiak[j].teljes_nev);
    Csoport elmelet_csoport[2],gyakorlat_csoport[25];/*2 350 fos elmeletcsoport es 25 28 fos gyakorlatcsoport*/
    /*csoportok letrehozasa*/
    srand(time(NULL));
    csoport_generalas();

}

