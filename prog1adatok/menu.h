#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
typedef enum Felhasznalo
{
  tanar,
  diak
}Felhasznalo;
typedef struct Prog1_Profil
{
    char *felhasznalonev;
    char *jelszo;
    Felhasznalo tanar_vagy_diak;
}Prog1_Profil;
void fomenu();
#endif // MENU_H_INCLUDED
