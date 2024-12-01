#ifndef PROG1ADATOK_H_INCLUDED
#define PROG1ADATOK_H_INCLUDED

typedef struct Eredmeny
{
    /*beolvasando adatok*/
    int KisZH[6];
    int NagyZH[2];
    int NagyHazi;
    int lab_hianyzas;
    int gyak_hianyzas;
    int szorgalmidb;
    /*kiszamitando adatok*/
    int ZH_pont;
    int KisZH_pont;
    int osszpont;
    int vegsojegy;
    bool sikeres_e;
}Eredmeny;
typedef struct Diak_Profil
{
    char *teljes_nev;
    char *Neptun_kod;
    Eredmeny aktualis_eredmeny;
    int elmelet_csoport,gyakorlat_csoport;
}Diak_Profil;
typedef enum Csoport_Tipus
{
    Elmelet,
    Gyakorlat
}Csoport_Tipus;
typedef struct Tanar_Profil
{
    char *teljes_nev;
    int csoport;
    Csoport_Tipus Elm_v_Gyak;
}Tanar_Profil;
FILE* file_opening(char const *fajlnev, char const *olvasas_vagy_iras);
int char_to_int(char const szam);
int csoport_sorszam_szamitas(char *csoportnev);
char *f_sztring_beolvasas(FILE *fajl, char ujsztring);
Diak_Profil *Diak_tarolas(int *diak_meret);
Tanar_Profil *Tanar_tarolas(int *tanar_meret);
#endif

