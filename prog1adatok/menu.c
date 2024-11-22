#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "prog1adatok.h"
#include "eredmenyek.h"
#include "menu.h"
#ifdef _WIN32
    #include <windows.h>
#endif
void hibauzenet()
{
    printf("Nem jo adatot irtal be.\n");
}
void fomenu()
{
     #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif
    printf("Irj egy \"o\"-t, ha oktató vagy, \"d\"-t ha diák vagy!\n");
    char profil_tipus;
    bool sikeres_beolvasas=false;
    Prog1_Profil prog1_felhasznalo;
    while(sikeres_beolvasas==false){
        scanf(" %c",&profil_tipus);
        if(profil_tipus=='o') {prog1_felhasznalo.tanar_vagy_diak=tanar;sikeres_beolvasas=true;}
        else if(profil_tipus=='d') {prog1_felhasznalo.tanar_vagy_diak=diak;sikeres_beolvasas=true;}
          else hibauzenet();
    }
}
