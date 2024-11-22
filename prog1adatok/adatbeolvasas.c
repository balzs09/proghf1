#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
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
/*A fuggveny random sorrendben general csoportokat.*/
/*static void diak_csoport_generalas()
{
    FILE *csoport_iras=file_opening("csoportok.txt","w");
    int eloadasdb[2]={0};
    int gyakorlatdb[25]={0};
    int rand_elm,rand_gyak;
    for(int i=0;i<700;i++)
    {
        rand_elm=rand()%2;
        rand_gyak=rand()%25;
        eloadasdb[rand_elm]++;
        gyakorlatdb[rand_gyak]++;
        while(eloadasdb[rand_elm]>350){ rand_elm=rand()%2;eloadasdb[rand_elm]++;}
        while(gyakorlatdb[rand_gyak]>28){ rand_gyak=rand()%25;gyakorlatdb[rand_gyak]++;}
        fprintf(csoport_iras,"E%d G%d\n",rand_elm+1,rand_gyak+1);
    }
    fclose(csoport_iras);
}*/
/*A fuggveny a tanarok csoportjait generalja random sorrendben.*/
/*static void tanar_csoport_generalas()
{
    FILE *csoport_iras=file_opening("csoportok.txt","w");
    int csoportdb[27]={0};
    int rand_szam;
    for(int i=0;i<27;i++)
    {
        rand_szam=rand()%27;
        csoportdb[rand_szam]++;
        while(csoportdb[rand_szam]>1) {rand_szam=rand()%27;csoportdb[rand_szam]++;}
        if(rand_szam>24) fprintf(csoport_iras,"E%d\n",rand_szam%24);
        else fprintf(csoport_iras,"G%d\n",rand_szam+1);
    }
    fclose(csoport_iras);
}*/
/*a memoriat a fofuggvenyben fel is kell szabaditani.*/
static char *sztring_beolvasas(FILE *fajl, char ujsztring)
{
   char *sor=(char*) malloc(1*sizeof(char));
   if(sor==NULL) {printf("Nem sikerult memoriat foglalni");return NULL;}
   int betu_db=0;
   char *vegleges;
   char ujbetu;
   int sikeresen=fscanf(fajl,"%c",&ujbetu);
   while(sikeresen==1&&ujbetu!=ujsztring)
    {
        vegleges=(char*) malloc((betu_db+1+1)*sizeof(char));
        if(vegleges==NULL)
        {
            printf("Nem sikerult memoriat foglalni");
            return NULL;
        }
        for(int i=0;i<betu_db;i++) vegleges[i]=sor[i];
        free(sor);
        sor=vegleges;
        vegleges[betu_db]=ujbetu;
        betu_db++;
        vegleges[betu_db]='\0';
        sikeresen=fscanf(fajl,"%c",&ujbetu);
    }
    return sor;
}
static int char_to_int(char const szam)
{
   return szam-'0';
}
/*A fuggveny visszatéríti a csoport nevében szereplõ szám -1-et. Ez alapján tárolja egy Csoport tömbben a neveket.*/
static int csoport_sorszam_szamitas(char *csoportnev)
{
    int csop_sorszam;
    if(strlen(csoportnev)>2) csop_sorszam=char_to_int(csoportnev[1])*10+char_to_int(csoportnev[2]);
         else csop_sorszam=char_to_int(csoportnev[1]);
    return  csop_sorszam;
}
bool sikeres_diak_memoriafoglalas(Diak_Profil *diakok)
{
    if(diakok==NULL)
    {
        printf("Nem sikerult memoriat foglalni");
       return false;
    }
    return true;
}
bool sikeres_tanar_memoriafoglalas(Tanar_Profil *tanarok)
{
    if(tanarok==NULL)
    {
        printf("Nem sikerult memoriat foglalni");
       return false;
    }
    return true;
}
Diak_Profil *Diak_tarolas( int *diak_meret)
{
    /*Ezeknek a soroknak a celja, hogy a kimenetrol beolvashatoak és a kimenetre kiirhatoak legyenek magyar betuk is,ami a Windows-1250 kodolással erheto el.*/
    #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif
    FILE *f_hallgatok= file_opening("hallgatoadatok.txt","r");
    Diak_Profil *osszesdiak=(Diak_Profil*)malloc(700*sizeof(Diak_Profil));/* atlagosan 700 diak kerül a ,BME VIK mernokinformatikus szakara az utobbi evek adatai alapjan*/
    bool van_memoria=sikeres_diak_memoriafoglalas(osszesdiak);
    int diak_db=0;
    char *aktualis_nev=sztring_beolvasas(f_hallgatok,'\n');
    while(strcmp(aktualis_nev,"Neptun-Kodok:")!=0&&van_memoria==true){
        osszesdiak[diak_db].teljes_nev=aktualis_nev;
        aktualis_nev=sztring_beolvasas(f_hallgatok,'\n');
        if(diak_db>699){ osszesdiak=(Diak_Profil*)realloc( osszesdiak,(diak_db+1)*sizeof(Diak_Profil));van_memoria=sikeres_diak_memoriafoglalas(osszesdiak);}
        diak_db++;
    }
    free(aktualis_nev);
    if(diak_db<700){ osszesdiak=(Diak_Profil*)realloc(osszesdiak,diak_db*sizeof(Diak_Profil));van_memoria=sikeres_diak_memoriafoglalas(osszesdiak);}
    for(int j=0;j<diak_db;j++) osszesdiak[j].Neptun_kod=sztring_beolvasas(f_hallgatok,'\n');
    /*csoportok letrehozasa, amiatt van commentben, mert csak egyszer kell a csoportokat legeneralni, hogy azutan azok valtozatlanok maradjanak.*/
    /* diak_csoport_generalas();*/
    char *elmelet_nev,*gyakorlat_nev;
    for(int i=0;i<diak_db;i++)    {
        elmelet_nev=sztring_beolvasas(f_hallgatok,' ');
        gyakorlat_nev=sztring_beolvasas(f_hallgatok,'\n');
        osszesdiak[i].elmelet_csoport=char_to_int(elmelet_nev[1]);
        free(elmelet_nev);
        osszesdiak[i].gyakorlat_csoport=csoport_sorszam_szamitas(gyakorlat_nev);
        free(gyakorlat_nev);
    }
    /*tanar_csoport_generalas();*/
    fclose(f_hallgatok);
    *diak_meret=diak_db;
    return osszesdiak;
}
Tanar_Profil *Tanar_tarolas( int *tanar_meret)
{
    /*tanar_csoport_generalas();*/
    FILE *f_csoportok=file_opening("csoportok.txt","r");
    Tanar_Profil *osszestanar=(Tanar_Profil*)malloc(27*sizeof(Tanar_Profil));
    int tanar_db=0;
    bool van_memoria=sikeres_tanar_memoriafoglalas(osszestanar);
    char *aktualis_nev=sztring_beolvasas(f_csoportok,'\n');
     while(strcmp(aktualis_nev,"Csoportok:")!=0&&van_memoria==true){
        osszestanar[tanar_db].teljes_nev=aktualis_nev;
        aktualis_nev=sztring_beolvasas(f_csoportok,'\n');
        if(tanar_db>26){ osszestanar=(Tanar_Profil*)realloc( osszestanar,tanar_db*sizeof(Tanar_Profil));van_memoria=sikeres_tanar_memoriafoglalas(osszestanar);}
        tanar_db++;
    }
    free(aktualis_nev);
    if(tanar_db<27){ osszestanar=(Tanar_Profil*)realloc(osszestanar,(tanar_db+1)*sizeof(Tanar_Profil));van_memoria=sikeres_tanar_memoriafoglalas(osszestanar);}
    for(int j=0;j<tanar_db;j++) {
            char *csoport_nev=sztring_beolvasas(f_csoportok,'\n');
            if(csoport_nev[0]=='E'){osszestanar[j].Elm_v_Gyak=Elmelet;osszestanar[j].csoport=char_to_int(csoport_nev[1]);}
            else {osszestanar[j].Elm_v_Gyak=Gyakorlat;osszestanar[j].csoport=csoport_sorszam_szamitas(csoport_nev);}
            free(csoport_nev);
    }
    fclose(f_csoportok);
    *tanar_meret=tanar_db;
    return osszestanar;
}
