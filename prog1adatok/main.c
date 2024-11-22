#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "debugmalloc.h"
#include "prog1adatok.h"
#include "eredmenyek.h"
#include "menu.h"
int main()
{
   srand(time(NULL));
  /* Diak_Profil *minden_diak=Diak_tarolas(&db_diak);
   for(int i=0;i<db_diak;i++)
   {
       printf("%s %s E%d G%d\n",minden_diak[i].teljes_nev,minden_diak[i].Neptun_kod,minden_diak[i].elmelet_csoport,minden_diak[i].gyakorlat_csoport);
       free(minden_diak[i].teljes_nev);free(minden_diak[i].Neptun_kod);
   }
   free(minden_diak);
   Tanar_Profil *minden_tanar=Tanar_tarolas(&db_tanar);
    for(int i=0;i<db_tanar;i++)
    {if(minden_tanar[i].Elm_v_Gyak==Elmelet)printf("%s E%d\n",minden_tanar[i].teljes_nev,minden_tanar[i].csoport);
     else printf("%s G%d\n",minden_tanar[i].teljes_nev,minden_tanar[i].csoport);
      free(minden_tanar[i].teljes_nev);
    }
   free(minden_tanar);*/
   /*int szam=eredmenyes();*/
  /* Diak_Profil *minden_diak=diak_eredmenyek(&db_diak);
   for(int i=0;i<db_diak;i++)
   {
       printf("%s %s E%d G%d\n",minden_diak[i].teljes_nev,minden_diak[i].Neptun_kod,minden_diak[i].elmelet_csoport,minden_diak[i].gyakorlat_csoport);
       free(minden_diak[i].teljes_nev);free(minden_diak[i].Neptun_kod);
   }
   free(minden_diak);*/
   /*lista_m();*/
   fomenu();
   return 0;

}


