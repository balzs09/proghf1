#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
typedef enum Felhasznalo_Tipus
{
  tanar,
  diak
}Felhasznalo_Tipus;
typedef struct Prog1_Profil
{
    char *megkulonbozteto_adat;
    char *felhasznalonev;
    char *jelszo;
    Felhasznalo_Tipus tanar_vagy_diak;
}Prog1_Profil;
void tipusok_kiiras();
Diak_Profil *fomenu(int *meret);
#endif // MENU_H_INCLUDED
