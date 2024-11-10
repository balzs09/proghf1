typedef enum Felhasznalo
{
  tanar,
  diak
}Felhasznalo;
typedef struct Prog1_Profil
{
    char felhasznalonev[50];
    char jelszo[50];
    Felhasznalo tanar_vagy_diak;
}Prog1_Profil;
/*a tobbi eredmeny (kis zhk osszege, felev vegi jegy) kiszamithato*/
typedef struct eredmeny
{
    int KisZH[6];
    int NagyZH[2];
    int NagyHazi;
    int hianyzas;
}eredmeny;
typedef struct Diak_Profil
{
    /*100 karaktert meghcalado nev nagyon-nagyon ritka, ezert veheto ez a hatarnak*/
    char teljes_nev[100];
    /*a neptun kod minden diaknak egy egyedi 6 karakterbol allo kod(+1 az üres karakter)*/
    char Neptun_kod[7];
    eredmeny aktualis_eredmeny;
}Diak_Profil;
typedef enum Csoport_tipus
{
    elmelet,
    gyakorlat
}Csoport_tipus;
typedef struct Csoport
{
    char Csoport_nev[5];
    Diak_Profil *diakok;
    char tanar_nev;
    Csoport_tipus elm_v_gyak;
}Csoport;


