#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "debugmalloc.h"
#include "prog1adatok.h"
#include "eredmenyek.h"
#include "menu.h"
void f_eredmeny_lista_kiir(Eredmeny_Lista *eleje,FILE *hova)
{
    Eredmeny_Lista *mozgo = eleje;
    while (mozgo != NULL){
        fprintf(hova,"%10d ",mozgo->eredmeny);
        mozgo=mozgo->kov;
    }
    fprintf(hova,"\n");
}
void f_atmeno_diak_lista_kiir_elore(Diak_Lista_sikeres *eleje,FILE *hova)
{
    Diak_Lista_sikeres *mozgo = eleje;
    while (mozgo != NULL){
        Eredmeny_Lista *eredmeny_eleje=NULL;
        fprintf(hova,"%-25s",mozgo->tanulo.teljes_nev);
        fprintf(hova,"%8s",mozgo->tanulo.Neptun_kod);
        fprintf(hova,"   E%d / G%d",mozgo->tanulo.elmelet_csoport,mozgo->tanulo.gyakorlat_csoport);
        if(mozgo->tanulo.gyakorlat_csoport<10) fprintf(hova," ");
        eredmeny_eleje=minden_eredmeny_hozzafuzes(eredmeny_eleje,mozgo->tanulo);
        f_eredmeny_lista_kiir(eredmeny_eleje,hova);
        eredmeny_lista_felszabadit(eredmeny_eleje);
        mozgo=mozgo->kov;
    }

}
void f_tipusok_kiiras(FILE *hova)
{
    fprintf(hova,"%-23s","Név:") ;
    fprintf(hova,"%11s","Neptun-kód:");
    fprintf(hova,"%11s","Csoportok:");
    for(int i=0;i<6;i++)
    {
            char sorszam='0'+i+1;
            int hossz=strlen("KZH");
            char *kiszh=(char*) malloc(sizeof(char)*(hossz+2));
            strcpy(kiszh,"KZH");
            kiszh[hossz]=sorszam;
            kiszh[hossz+1]='\0';
            fprintf(hova,"%10s:",kiszh);
            free(kiszh);
    }
    fprintf(hova,"%11s","kZH pont:");
    fprintf(hova,"%9s","ZH1:" );
    fprintf(hova,"%11s","ZH2:");
    fprintf(hova,"%11s","ZH pont:");

    fprintf(hova,"%11s","nagy hf:");
    fprintf(hova,"%11s","lab h:");
    fprintf(hova,"%11s","gyak h:");
    fprintf(hova,"%11s","szorgalmi:");
    fprintf(hova,"%11s","összpont:");
    fprintf(hova,"%11s\n","jegy:");
}
void f_bukott_diak_lista_kiir_elore(Diak_Lista_sikertelen *eleje,FILE *hova)
{
    Diak_Lista_sikertelen *mozgo = eleje;
    while (mozgo != NULL){
        Eredmeny_Lista *eredmeny_eleje=NULL;
        fprintf(hova,"%-25s",mozgo->tanulo.teljes_nev);
        fprintf(hova,"%8s",mozgo->tanulo.Neptun_kod);
        fprintf(hova,"   E%d / G%d",mozgo->tanulo.elmelet_csoport,mozgo->tanulo.gyakorlat_csoport);
        if(mozgo->tanulo.gyakorlat_csoport<10) fprintf(hova," ");
        eredmeny_eleje=minden_eredmeny_hozzafuzes(eredmeny_eleje,mozgo->tanulo);
        f_eredmeny_lista_kiir(eredmeny_eleje,hova);
        eredmeny_lista_felszabadit(eredmeny_eleje);
        mozgo=mozgo->kov;
    }
}
int main()
{
   srand(time(NULL));
   FILE *sorrend=file_opening("eredmenysorrend.txt","w");
   int diak_db;
   Diak_Profil *diakok=fomenu(&diak_db);
   Diak_Lista_sikeres *sikeresek_eleje=NULL;
   Diak_Lista_sikertelen *sikertelenek_eleje=NULL;
   f_tipusok_kiiras(sorrend);
    for(int i=0;i<diak_db;i++)
        if(diakok[i].aktualis_eredmeny.vegsojegy>0)
            sikeresek_eleje=csokkeno_felepites_sikeres(sikeresek_eleje,diakok[i],"összes pont");
          else sikertelenek_eleje=csokkeno_felepites_sikertelen(sikertelenek_eleje,diakok[i],"összes pont");
    f_atmeno_diak_lista_kiir_elore(sikeresek_eleje,sorrend);
    f_bukott_diak_lista_kiir_elore(sikertelenek_eleje,sorrend);
    for(int i=0;i<diak_db;i++) {free(diakok[i].Neptun_kod);free(diakok[i].teljes_nev);}
    free(diakok);
    atmeno_diak_lista_felszabadit(sikeresek_eleje);
    bukott_diak_lista_felszabadit(sikertelenek_eleje);
   return 0;
}


