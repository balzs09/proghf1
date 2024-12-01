#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "prog1adatok.h"
#include "eredmenyek.h"
#include "debugmalloc.h"
int ZH_jegy(int *NagyZH)
{
    if(NagyZH[0]>NagyZH[1]) return NagyZH[0]+NagyZH[1];
     else  return 2*NagyZH[1];
}
int KisZH_jegy(int *KisZH)
{
    int KisZH_S=0;
    int min1=KisZH[0],min2=KisZH[1],min1_index=0,min2_index=1;/*az indexre azert van szukseg, mert lehetnek egyenlo eredmenyek,
    amelyekbol van amit bele kell szamitani az osszegbe es van amit nem.*/
    for(int i=2;i<6;i++)
    {
        if(KisZH[i]<min1) {min1=KisZH[i];min1_index=i;}
        else if(KisZH[i]<min2) {min2=KisZH[i];min2_index=i;}
    }
    for(int j=0;j<6;j++)
        if(j!=min1_index&&j!=min2_index) KisZH_S=KisZH_S+KisZH[j];
     return KisZH_S;
}
/*Ha minden reszeredmeny megfelelt a kovetelmenynek, 70 pontot biztosan elert az illeto diak, igy azt az esetet nem kell vizsgalni, ahol kevesebb pont van mint 70.*/
int felev_vegi(const int ossz_pont)
{
    if(ossz_pont<90) return 2;
     else if(ossz_pont<110) return 3;
       else if(ossz_pont<125) return 4;
         else    return 5;
}
/*Ez a fuggveny azt hatarozza meg, hogy az eselyesebb kimenetel tortent meg, vagy a kevesbbe eselyes. A parameter az eselyesseg tizedesben.*/
bool eselyesebb_kimenetel(int tized)
{
    int rand_szazalek=rand()%10;
    if(rand_szazalek<tized) return true;
      else return false;
}
int hianyzas_db(bool eselyesebb)
{
    if(eselyesebb==true) return rand()%4;
    else return rand()%10+5;
}
/*a tanulok eredmenyeinek legeneralasa es kiiratasa egy szoveges fajlba.*/
/*static void eredmeny_generalas()
{
    FILE *csoport_iras=file_opening("tanuloeredmenyek.txt","w");
    int rand_pont;
    for(int i=0;i<700;i++){
        for(int j=0;j<6;j++){
            if(eselyesebb_kimenetel(8)==true) rand_pont=rand()%5+6;
                else  rand_pont=rand()%6;
                fprintf(csoport_iras,"%d ",rand_pont);
        }
        for(int j=0;j<2;j++){
            if(eselyesebb_kimenetel(7)==true) rand_pont=rand()%21+20;
             else rand_pont=rand()%20;
            fprintf(csoport_iras,"%d ",rand_pont);
        }
        if(eselyesebb_kimenetel(7)==true) rand_pont=rand()%11+10;
          else rand_pont=rand()%10;
        fprintf(csoport_iras,"%d ",rand_pont);
        rand_pont=hianyzas_db(eselyesebb_kimenetel(9));
        fprintf(csoport_iras,"%d ",rand_pont);
        rand_pont=hianyzas_db(eselyesebb_kimenetel(9));
        fprintf(csoport_iras,"%d ",rand_pont);
        if(eselyesebb_kimenetel(7)==true) rand_pont=0;
          else rand_pont=rand()%10+1;
        fprintf(csoport_iras,"%d\n",rand_pont);
    }
}*/
/*A fuggveny eltarolja a diakok eredmenyeit es a szukseges tovabbi eredmenyeket kiszamolja a fenti fuggvenyek hasznalataval.*/
Diak_Profil *diak_eredmenyek(int *osszdiak_db)
{
    /*eredmeny_generalas();*/
    FILE *csoport_olvasas=file_opening("tanuloeredmenyek.txt","r");
    int diak_db=0;
    int eredmeny_tipus_db;
    Diak_Profil *diakok=Diak_tarolas(&diak_db);
    for(int i=0;i<700;i++){
        diakok[i].aktualis_eredmeny.sikeres_e=true;
        for(int j=0;j<6;j++)
             fscanf(csoport_olvasas,"%d ",&diakok[i].aktualis_eredmeny.KisZH[j]);

        diakok[i].aktualis_eredmeny.KisZH_pont=KisZH_jegy(diakok[i].aktualis_eredmeny.KisZH);
        if( diakok[i].aktualis_eredmeny.KisZH_pont<20) diakok[i].aktualis_eredmeny.sikeres_e=false;
        if(i==0) eredmeny_tipus_db++;
        for(int j=0;j<2;j++)
            fscanf(csoport_olvasas,"%d ",&diakok[i].aktualis_eredmeny.NagyZH[j]);
        diakok[i].aktualis_eredmeny.ZH_pont=ZH_jegy(diakok[i].aktualis_eredmeny.NagyZH);
        if(diakok[i].aktualis_eredmeny.ZH_pont<40) diakok[i].aktualis_eredmeny.sikeres_e=false;
        fscanf(csoport_olvasas,"%d ",&diakok[i].aktualis_eredmeny.NagyHazi);
        if(diakok[i].aktualis_eredmeny.NagyHazi<10) diakok[i].aktualis_eredmeny.sikeres_e=false;
        fscanf(csoport_olvasas,"%d ",&diakok[i].aktualis_eredmeny.lab_hianyzas);
        if(diakok[i].aktualis_eredmeny.lab_hianyzas>3) diakok[i].aktualis_eredmeny.sikeres_e=false;
        fscanf(csoport_olvasas,"%d ",&diakok[i].aktualis_eredmeny.gyak_hianyzas);
         if(diakok[i].aktualis_eredmeny.gyak_hianyzas>3) diakok[i].aktualis_eredmeny.sikeres_e=false;
        fscanf(csoport_olvasas,"%d ",&diakok[i].aktualis_eredmeny.szorgalmidb);
        diakok[i].aktualis_eredmeny.osszpont= diakok[i].aktualis_eredmeny.KisZH_pont+
        diakok[i].aktualis_eredmeny.ZH_pont+diakok[i].aktualis_eredmeny.NagyHazi+diakok[i].aktualis_eredmeny.szorgalmidb;
        if(diakok[i].aktualis_eredmeny.sikeres_e==false) diakok[i].aktualis_eredmeny.vegsojegy=0;
        else diakok[i].aktualis_eredmeny.vegsojegy=felev_vegi(diakok[i].aktualis_eredmeny.osszpont);
    }
    *osszdiak_db=diak_db;
    return diakok;
}
int eredmenytipus_hasonlitas(Diak_Profil p,char *eredmenytipus)
{
    if(strcmp("ZH1",eredmenytipus)==0) return p.aktualis_eredmeny.NagyZH[0];
    if(strcmp("ZH2",eredmenytipus)==0) return p.aktualis_eredmeny.NagyZH[1];
    if(strcmp("ZH pont",eredmenytipus)==0) return p.aktualis_eredmeny.ZH_pont;
    if(strcmp("KZH1",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH[0];
    if(strcmp("KZH2",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH[1];
    if(strcmp("KZH3",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH[2];
    if(strcmp("KZH4",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH[3];
    if(strcmp("KZH5",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH[4];
    if(strcmp("KZH6",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH[5];
   if(strcmp("kis ZH pont",eredmenytipus)==0) return p.aktualis_eredmeny.KisZH_pont;
   if(strcmp("nagy házi",eredmenytipus)==0) return p.aktualis_eredmeny.NagyHazi;
   if(strcmp("labor hiányzás",eredmenytipus)==0) return p.aktualis_eredmeny.lab_hianyzas;
   if(strcmp("gyakorlat hiányzás",eredmenytipus)==0) return p.aktualis_eredmeny.gyak_hianyzas;
   if(strcmp("szorgalmi pont",eredmenytipus)==0) return p.aktualis_eredmeny.szorgalmidb;
   if(strcmp("összes pont",eredmenytipus)==0) return p.aktualis_eredmeny.osszpont;
   if(strcmp("végsõ jegy",eredmenytipus)==0) return p.aktualis_eredmeny.lab_hianyzas;
   return 0;
}
/*Az eredmenyek lancolt listahoz fuzese.*/
Eredmeny_Lista *eredmeny_lista_hozzafuzes(Eredmeny_Lista *eleje,int adat)
{
    Eredmeny_Lista *uj=(Eredmeny_Lista*) malloc(sizeof(Eredmeny_Lista));
    uj->eredmeny=adat;
    uj->kov=NULL;
    if(eleje==NULL) return uj;
    else
    {
        Eredmeny_Lista *mozgo=eleje;
        while(mozgo->kov!=NULL) mozgo=mozgo->kov;
        mozgo->kov=uj;
        return eleje;
    }
}
/*Az eredmenyek lancolt listajanak felszabaditasa*/
void eredmeny_lista_felszabadit(Eredmeny_Lista *eleje)
{
    Eredmeny_Lista *iter=eleje;
    while(iter!=NULL)
    {
        Eredmeny_Lista *kov=iter->kov;
        free(iter);
        iter=kov;
    }
}
/*A fuggveny kiiratja az eredmenyek lancolt listajat*/
void eredmeny_lista_kiir(Eredmeny_Lista *eleje)
{
    Eredmeny_Lista *mozgo = eleje;
    while (mozgo != NULL){
        printf("%10d ",mozgo->eredmeny);
        mozgo=mozgo->kov;
    }
    printf("\n");
}
/* A fuggveny felepit egy csokkeno sorrendu listat a diakokbol,azokbol akiknek sikerult a targy.
Azok akik nem sikerultek egy kulon lancolt listaban lesznek elrendezve.A rendezes az eredmenytipus valtozoba irt ere*/
Diak_Lista_sikeres *csokkeno_felepites_sikeres(Diak_Lista_sikeres *eleje,Diak_Profil adat, char *eredmenytipus)
{
    Diak_Lista_sikeres *uj=(Diak_Lista_sikeres*) malloc(sizeof(Diak_Lista_sikeres));
    uj->tanulo=adat;
    uj->kov=NULL;
    int hasonlitando=eredmenytipus_hasonlitas(uj->tanulo,eredmenytipus);
    Diak_Lista_sikeres *lemarado=NULL;
    Diak_Lista_sikeres *mozgo=eleje;
    while(mozgo!=NULL&&eredmenytipus_hasonlitas(mozgo->tanulo,eredmenytipus)> hasonlitando){
        lemarado=mozgo;
        mozgo=mozgo->kov;
    }
    if(lemarado==NULL){
         uj->kov=eleje;
          eleje=uj;
        }
        else
        {
            lemarado->kov=uj;
            uj->kov=mozgo;
        }

    return eleje;
}
Diak_Lista_sikertelen *csokkeno_felepites_sikertelen(Diak_Lista_sikertelen *eleje,Diak_Profil adat,char *eredmenytipus)
{
    Diak_Lista_sikertelen *uj=(Diak_Lista_sikertelen*) malloc(sizeof(Diak_Lista_sikertelen));
    uj->tanulo=adat;
    uj->kov=NULL;
    int hasonlitando=eredmenytipus_hasonlitas(uj->tanulo,eredmenytipus);
    Diak_Lista_sikertelen *lemarado=NULL;
    Diak_Lista_sikertelen *mozgo=eleje;
    while(mozgo!=NULL&&eredmenytipus_hasonlitas(mozgo->tanulo,eredmenytipus)> hasonlitando){
        lemarado=mozgo;
        mozgo=mozgo->kov;
    }
    if(lemarado==NULL){
         uj->kov=eleje;
         eleje=uj;
        }
        else
        {
            lemarado->kov=uj;
            uj->kov=mozgo;
        }

    return eleje;
}
Eredmeny_Lista *minden_eredmeny_hozzafuzes(Eredmeny_Lista *eleje,Diak_Profil diak)
{
        for(int i=0;i<6;i++) eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.KisZH[i]);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.KisZH_pont);
        for(int i=0;i<2;i++) eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.NagyZH[i]);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.ZH_pont);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.NagyHazi);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.lab_hianyzas);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.gyak_hianyzas);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.szorgalmidb);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.osszpont);
        eleje=eredmeny_lista_hozzafuzes(eleje,diak.aktualis_eredmeny.vegsojegy);
        return eleje;
}
void atmeno_diak_lista_kiir_elore(Diak_Lista_sikeres *eleje)
{
    Diak_Lista_sikeres *mozgo = eleje;
    while (mozgo != NULL){
        Eredmeny_Lista *eredmeny_eleje=NULL;
        printf("%-17s",mozgo->tanulo.teljes_nev);
        printf("%8s",mozgo->tanulo.Neptun_kod);
        printf("   E%d / G%d",mozgo->tanulo.elmelet_csoport,mozgo->tanulo.gyakorlat_csoport);
        eredmeny_eleje=minden_eredmeny_hozzafuzes(eredmeny_eleje,mozgo->tanulo);
        eredmeny_lista_kiir(eredmeny_eleje);
        eredmeny_lista_felszabadit(eredmeny_eleje);
        mozgo=mozgo->kov;
    }
}
void bukott_diak_lista_kiir_elore(Diak_Lista_sikertelen *eleje)
{
    Diak_Lista_sikertelen *mozgo = eleje;
    while (mozgo != NULL){
        Eredmeny_Lista *eredmeny_eleje=NULL;
        printf("%-17s ",mozgo->tanulo.teljes_nev);
        printf("%8s ",mozgo->tanulo.Neptun_kod);
        printf("   E%d / G%d",mozgo->tanulo.elmelet_csoport,mozgo->tanulo.gyakorlat_csoport);
        eredmeny_eleje=minden_eredmeny_hozzafuzes(eredmeny_eleje,mozgo->tanulo);
        eredmeny_lista_kiir(eredmeny_eleje);
        eredmeny_lista_felszabadit(eredmeny_eleje);
        mozgo=mozgo->kov;
    }
}

void atmeno_diak_lista_felszabadit(Diak_Lista_sikeres *eleje)
{
    Diak_Lista_sikeres *iter=eleje;
    while(iter!=NULL)
    {
        Diak_Lista_sikeres *kov=iter->kov;
        free(iter);
        iter=kov;
    }
}
void bukott_diak_lista_felszabadit(Diak_Lista_sikertelen *eleje)
{
    Diak_Lista_sikertelen *iter=eleje;
    while(iter!=NULL)
    {
        Diak_Lista_sikertelen *kov=iter->kov;
        free(iter);
        iter=kov;
    }
}

