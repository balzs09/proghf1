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
int ZH_jegy( int *NagyZH);
int KisZH_jegy( int *KisZH);
int felev_vegi(const int ossz_pont);
Diak_Profil *diak_eredmenyek(int *osszdiak_db);
void lista_m();
#endif // EREDMENYEK_H_INCLUDED
