#ifndef EREDMENYEK_H_INCLUDED
#define EREDMENYEK_H_INCLUDED
#include "prog1adatok.h"

typedef struct Eredmeny_Lista
{
    int eredmeny;
    struct Eredmeny_Lista *kov;
}Eredmeny_Lista;
/*a kovetelmenyeket teljesito tanulokbol alkotott lancolt lista*/
typedef struct Diak__Lista_sikeres
{
    Diak_Profil tanulo;
    struct Diak__Lista_sikeres *kov;
}Diak_Lista_sikeres;
/*a kovetelmenyeket nem teljesito tanulokat tartalmazo lancolt lista*/
typedef struct Diak_Lista_sikertelen
{
    Diak_Profil tanulo;
    struct Diak_Lista_sikertelen *kov;
}Diak_Lista_sikertelen;
Diak_Profil *diak_eredmenyek(int *osszdiak_db);
int eredmenytipus_hasonlitas(Diak_Profil p,char *eredmenytipus);
Eredmeny_Lista *minden_eredmeny_hozzafuzes(Eredmeny_Lista *eleje,Diak_Profil diak);
void eredmeny_lista_kiir(Eredmeny_Lista *eleje);
void eredmeny_lista_felszabadit(Eredmeny_Lista *eleje);
Diak_Lista_sikeres *csokkeno_felepites_sikeres(Diak_Lista_sikeres *eleje,Diak_Profil adat, char *eredmenytipus);
Diak_Lista_sikertelen *csokkeno_felepites_sikertelen(Diak_Lista_sikertelen *eleje,Diak_Profil adat,char *eredmenytipus);
void atmeno_diak_lista_kiir_elore(Diak_Lista_sikeres *eleje);
void bukott_diak_lista_kiir_elore(Diak_Lista_sikertelen *eleje);
void atmeno_diak_lista_felszabadit(Diak_Lista_sikeres *eleje);
void bukott_diak_lista_felszabadit(Diak_Lista_sikertelen *eleje);
void lista_m();
#endif // EREDMENYEK_H_INCLUDED
