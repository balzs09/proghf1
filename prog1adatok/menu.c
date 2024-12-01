#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h> /*a karakterenkénti , a képernyõn nem látható jelszóbeolvasáshoz szükséges. Külsõ forrás is fel lett használva ennek megvalósítására.*/
#include "debugmalloc.h"
#include "prog1adatok.h"
#include "eredmenyek.h"
#include "menu.h"
#ifdef _WIN32
    #include <windows.h>
#endif
void hibauzenet()
{
    printf("Nem jó adatot irtál be.\n");
}
void beolvas_kimenetrol(char *beolvasott_betu,char lehetoseg_1, char lehetoseg_2)
{
    bool sikeres_beolvasas=false;
     while(sikeres_beolvasas==false){
        scanf(" %c",beolvasott_betu);
        if(*beolvasott_betu==lehetoseg_1||*beolvasott_betu==lehetoseg_2) sikeres_beolvasas=true;
          else hibauzenet();
    }
}
void tanar_vagy_diak_beolvasas(Prog1_Profil *regisztralo)
{
    printf("Irj egy \"o\"-t, ha oktató vagy, \"d\"-t ha diák vagy!\n");
    char profil_tipus;
    beolvas_kimenetrol(&profil_tipus,'o','d');
    if(profil_tipus=='o') regisztralo->tanar_vagy_diak=tanar;
    else if(profil_tipus=='d') regisztralo->tanar_vagy_diak=diak;
}
 char *sztring_beolvasas( char ujsztring)
{
   char *sor=(char*) malloc(1*sizeof(char));
   if(sor==NULL) {printf("Nem sikerult memoriat foglalni");return NULL;}
   int betu_db=0;
   char *vegleges;
   char ujbetu;
   int sikeresen=scanf(" %c",&ujbetu);
   while(sikeresen==1&&ujbetu!=ujsztring)
    {
        vegleges=(char*) malloc((betu_db+1+1)*sizeof(char));
        if(vegleges==NULL)
        {
            printf("Nem sikerult memoriat foglalni");
            return NULL;
        }
        for(int i=0;i<betu_db;i++) vegleges[i]=sor[i];
        free(sor);
        sor=vegleges;
        vegleges[betu_db]=ujbetu;
        betu_db++;
        vegleges[betu_db]='\0';
        sikeresen=scanf("%c",&ujbetu);
    }
    return sor;
}
void jelszo_enkoder(char *jelszo,FILE *regisztralt_jelszavak)
{
    for(int i=0;jelszo[i]!='\0';i++){
        int hanyados=jelszo[i]/7;
        int maradek=jelszo[i]%7;
        fprintf(regisztralt_jelszavak,"%d %d ",hanyados,maradek);
    }
    fprintf(regisztralt_jelszavak," ");
}
char *jelszo_dekoder(FILE *regisztralt_jelszavak)
{
    char *jelszo=(char*) malloc(21*sizeof(char));
    int hanyados=0,maradek=0,db_betu=0;
    bool sikeres_beolvasas=true;
    while(sikeres_beolvasas==true)
    {
        fscanf(regisztralt_jelszavak,"%d %d",&hanyados,&maradek);
        if(hanyados==-1&&maradek==-1)
            sikeres_beolvasas=false;
        else{
            jelszo[db_betu]=(char)(7*hanyados+maradek);
            db_betu++;
        }
    }
    jelszo[db_betu]='\0';
    if(db_betu<20) jelszo=(char*)realloc(jelszo,sizeof(char*)*(db_betu+1));
    return jelszo;
}
/*Kiirja azok adatait, akik már regisztráltak*/
void regisztralo_kiiras(Prog1_Profil *regisztralt)
{
    FILE *regisztralok=fopen("regisztralas_adatok.txt","a");
    fprintf(regisztralok,"%s ",regisztralt->felhasznalonev);
    fprintf(regisztralok,"%s ",regisztralt->megkulonbozteto_adat);
    jelszo_enkoder(regisztralt->jelszo,regisztralok);
    fprintf(regisztralok,"%d %d ",-1,-1);
    if(regisztralt->tanar_vagy_diak==tanar) fprintf(regisztralok,"tanár");
    else fprintf(regisztralok,"diák");
    fprintf(regisztralok,"\n");
    fclose(regisztralok);
}
Prog1_Profil *regisztralt_profilok(int *meret)
{
    FILE *regisztralasok=fopen("regisztralas_adatok.txt","r");
    int alap_meret=10,reg_db=0;
    Prog1_Profil *regisztraltak=(Prog1_Profil*) malloc(sizeof(Prog1_Profil)*alap_meret);
    char *username=f_sztring_beolvasas(regisztralasok,' ');
    char *tanar_vagy_diak;
    bool sikeres_beolvasas;
    if(username==NULL) {sikeres_beolvasas=false;printf("Nem sikerült olvasni.");}
    else sikeres_beolvasas=true;
    while(sikeres_beolvasas)
    {
        regisztraltak[reg_db].felhasznalonev=strdup(username);
        regisztraltak[reg_db].megkulonbozteto_adat=f_sztring_beolvasas(regisztralasok,' ');
        regisztraltak[reg_db].jelszo=jelszo_dekoder(regisztralasok);
        tanar_vagy_diak=f_sztring_beolvasas(regisztralasok,'\n');
        if(tanar_vagy_diak[1]=='t') regisztraltak[reg_db].tanar_vagy_diak=tanar;
        else regisztraltak[reg_db].tanar_vagy_diak=diak;
        free(tanar_vagy_diak);
        free(username);
        username=NULL;
        reg_db++;
        username=f_sztring_beolvasas(regisztralasok,' ');
        if(username==NULL) sikeres_beolvasas=false;
        if(reg_db>=alap_meret&&sikeres_beolvasas) {alap_meret+=10;regisztraltak=(Prog1_Profil*) realloc(regisztraltak,sizeof(Prog1_Profil)*alap_meret);}
    }
    if(reg_db<alap_meret) regisztraltak=(Prog1_Profil*) realloc(regisztraltak,sizeof(Prog1_Profil)*(reg_db));
    *meret=reg_db;
    fclose(regisztralasok);
    return regisztraltak;
}
int volt_mar_felhasznalonev(Prog1_Profil *bejelentkezo,Prog1_Profil **regisztraltak,int const meret)
{
    for(int i=0;i<meret;i++)
        if(strcmp(bejelentkezo->felhasznalonev,(*regisztraltak)[i].felhasznalonev)==0) return i;
    return -1;
}
void uj_felhasznalonev(Prog1_Profil *felhasznalonev_szerzo)
{
   int profil_db=0;
   Prog1_Profil *regisztraltak=regisztralt_profilok(&profil_db);
   printf("Add meg a felhasználóneved, legyen legalább 5 betû es ne legyen space benne!\n");
   bool sikeres_beolvasas=false;
   while(sikeres_beolvasas==false)
   {felhasznalonev_szerzo->felhasznalonev=sztring_beolvasas('\n');
    bool volt_e_mar=false;
    for(int i=0;i<profil_db;i++)
        if(strcmp(felhasznalonev_szerzo->felhasznalonev,regisztraltak[i].felhasznalonev)==0) volt_e_mar=true;
    if(volt_e_mar==true) printf("A felhasználónév már foglalt.\n");
    else if(strlen(felhasznalonev_szerzo->felhasznalonev)<5||strchr(felhasznalonev_szerzo->felhasznalonev,' ')) hibauzenet();
     else sikeres_beolvasas=true;
   }
   for(int i=0;i<profil_db;i++){
        free(regisztraltak[i].jelszo);
        free(regisztraltak[i].megkulonbozteto_adat);
   }
   free(regisztraltak);
}
void uj_jelszo(Prog1_Profil *jelszo_szerzo)
{
    bool sikeres_beolvasas=false,helyes=true;
    int kisbetu=0,nagybetu=0,szamjegy=0;
    jelszo_szerzo->jelszo=(char*) malloc(sizeof(char)*21);
    int jelszo_hossz=0;
    printf("Add meg a jelszavad. Minimum 8, maximum 20 karakter lehet. Figyelj arra is ,hogy elég erõs legyen!\n");
    while(sikeres_beolvasas==false){
        helyes=true;
        char uj_karakter=_getch();
        jelszo_hossz=1;
        while(jelszo_hossz<21&&uj_karakter!='\r')
        {
            if(uj_karakter>='a'&&uj_karakter<='z') kisbetu++;
            if(uj_karakter>='A'&&uj_karakter<='Z') nagybetu++;
            if(uj_karakter>='0'&&uj_karakter<='9') szamjegy++;
            if(uj_karakter=='\b'){
            jelszo_hossz--;
            printf("\b \b");
            if(jelszo_szerzo->jelszo[jelszo_hossz]>='a'&&jelszo_szerzo->jelszo[jelszo_hossz]<='z') kisbetu--;
            if(jelszo_szerzo->jelszo[jelszo_hossz]>='A'&&jelszo_szerzo->jelszo[jelszo_hossz]<='Z') nagybetu--;
            if(jelszo_szerzo->jelszo[jelszo_hossz]>='0'&&jelszo_szerzo->jelszo[jelszo_hossz]<='9') szamjegy--;
            }
            else{
            jelszo_szerzo->jelszo[jelszo_hossz]=uj_karakter;
            printf("*");
            jelszo_hossz++;
        }
        uj_karakter=_getch();
        }
        jelszo_szerzo->jelszo[jelszo_hossz]='\0';
        printf("\n");
        if(strlen(jelszo_szerzo->jelszo)<9) {printf("Túl rövid jelszó.\n");helyes=false;}
        if(szamjegy==0) {printf("Nincs benne számjegy.\n");helyes=false;}
        if(nagybetu==0) {printf("Nincs benne nagybetû.\n");helyes=false;}
        if(kisbetu==0) {printf("Nincs benne kisbetû.\n");helyes=false;}
        if(strchr(jelszo_szerzo->jelszo,' ')) {printf("Nem lehet benne space.\n");helyes=false;}
        if(helyes==true) sikeres_beolvasas=true;
    }
    if(jelszo_hossz<20) {jelszo_szerzo->jelszo=realloc(jelszo_szerzo->jelszo,sizeof(char)*(jelszo_hossz+1));
    if(jelszo_szerzo->jelszo==NULL) printf("Nem sikerült memóriát foglalni.");}
}
int regisztralas( Prog1_Profil *regisztralo_profil,Diak_Profil **diakok, Tanar_Profil **tanarok,int *diak_meret,int *tanar_meret)
{
    tanar_vagy_diak_beolvasas(regisztralo_profil);
    int sorszam=0;
    bool talalt_e=false;
    int diak_db=0,tanar_db=0;
    *diakok=diak_eredmenyek(&diak_db);/*ezt a fuggyenyt kell meghivni, hogy kesobb tudjuk felhasznalni az eredmenyeket is*/
    if(regisztralo_profil->tanar_vagy_diak==diak){
        int diak_sorszam=0;
        while(talalt_e==false){
            printf("Add meg a Neptun-kódod, majd üss be egy entert!\n");
            regisztralo_profil->megkulonbozteto_adat=sztring_beolvasas('\n');
            for(int i=0;i<diak_db &&talalt_e==false;i++)
                  {
                      if(strcmp(regisztralo_profil->megkulonbozteto_adat,(*diakok)[i].Neptun_kod)==0) {talalt_e=true;diak_sorszam=i;}
                  }
            if(talalt_e==false){hibauzenet();free(regisztralo_profil->megkulonbozteto_adat);}
        }
        talalt_e=false;
        sorszam=diak_sorszam;
    }
    else{
        int tanar_sorszam=0;
        *tanarok=Tanar_tarolas(&tanar_db);
        while(talalt_e==false){
            printf("Add meg a csoportod nevét, majd üss be egy entert!\n");
            regisztralo_profil->megkulonbozteto_adat=sztring_beolvasas('\n');
            char ora_tipus=regisztralo_profil->megkulonbozteto_adat[0];
            Csoport_Tipus elm_v_gyak;
         int csoportszam=0;
            if(ora_tipus=='E') {csoportszam=char_to_int(regisztralo_profil->megkulonbozteto_adat[1]);elm_v_gyak=Elmelet;}
               else {csoportszam=csoport_sorszam_szamitas(regisztralo_profil->megkulonbozteto_adat);elm_v_gyak=Gyakorlat;}
            for(int i=0;i<tanar_db&&talalt_e==false;i++)
                if(elm_v_gyak==(*tanarok)[i].Elm_v_Gyak&&csoportszam==(*tanarok)[i].csoport) {talalt_e=true;tanar_sorszam=i;}
            if(talalt_e==false){hibauzenet();free(regisztralo_profil->megkulonbozteto_adat);}
        }
        sorszam=tanar_sorszam;
    }
    uj_felhasznalonev(regisztralo_profil);
    uj_jelszo(regisztralo_profil);
    printf("\n");
    *diak_meret=diak_db;
    *tanar_meret=tanar_db;
    return sorszam;
}
Prog1_Profil *bejelentkezes(Prog1_Profil *bejelentkezo,int *reg_db)
{
    printf("Add meg a felhasználónevedet! \n");
    int profil_db=0;
    Prog1_Profil *regisztraltak=regisztralt_profilok(&profil_db);
    bejelentkezo->felhasznalonev=sztring_beolvasas('\n');
    int sorszam=-1;
    while(sorszam==-1)
    {
        sorszam=volt_mar_felhasznalonev(bejelentkezo,&regisztraltak,profil_db);
        if(sorszam==-1){
                printf("Nincs regisztrálva ez a felhasználónév.\n");
                free(bejelentkezo->felhasznalonev);
                bejelentkezo->felhasznalonev=sztring_beolvasas('\n');
        }
    }
    uj_jelszo(bejelentkezo);
    while(strcmp(bejelentkezo->jelszo,regisztraltak[sorszam].jelszo)!=0) {
          printf("Helytelen jelszót adtál meg.\n");
          uj_jelszo(bejelentkezo);
    }
    free(bejelentkezo->jelszo);
    bejelentkezo->jelszo=regisztraltak[sorszam].jelszo;
    bejelentkezo->megkulonbozteto_adat=regisztraltak[sorszam].megkulonbozteto_adat;
    bejelentkezo->tanar_vagy_diak=regisztraltak[sorszam].tanar_vagy_diak;
    *reg_db=profil_db;
    return regisztraltak;
}
int bejelentkezes_vagy_regisztracio(Prog1_Profil *felhasznalo,Diak_Profil **reg_diakok, Tanar_Profil **reg_tanarok,int *diak_meret,int *tanar_meret,bool *bejelentkezett)
{
    printf("Bejelentkezni (b) vagy regisztrálni szeretnél (r)?\n");
    char log_v_reg;
    bool regisztralt=true;
    beolvas_kimenetrol(&log_v_reg,'b','r');
    int sorszam=-1;
    if(log_v_reg=='r'){

            sorszam=regisztralas(felhasznalo,reg_diakok,reg_tanarok,diak_meret,tanar_meret);
            regisztralo_kiiras(felhasznalo);
            }
    else{
            regisztralt=false;
         int regisztralas_db;
        Prog1_Profil *regisztraltak=bejelentkezes(felhasznalo,&regisztralas_db);
        if(felhasznalo==NULL) printf("Hiba");
        bool talalt_e=false;
        *reg_diakok=diak_eredmenyek(diak_meret);
        if(*reg_diakok==NULL) printf("hiba");
        if(felhasznalo->tanar_vagy_diak==diak){
             for(int i=0;i<*diak_meret &&talalt_e==false;i++){
             if(strcmp(felhasznalo->megkulonbozteto_adat,(*reg_diakok)[i].Neptun_kod)==0){ sorszam=i;talalt_e=true;}
        }
        }
        else{
            *reg_tanarok=Tanar_tarolas(tanar_meret);
             char ora_tipus=felhasznalo->megkulonbozteto_adat[0];
              Csoport_Tipus elm_v_gyak;
             int csoportszam=0;
            if(ora_tipus=='E') {csoportszam=char_to_int(felhasznalo->megkulonbozteto_adat[1]);elm_v_gyak=Elmelet;}
            else {csoportszam=csoport_sorszam_szamitas(felhasznalo->megkulonbozteto_adat);elm_v_gyak=Gyakorlat;}
            for(int i=0;i<*tanar_meret&&talalt_e==false;i++)
                if(elm_v_gyak==(*reg_tanarok)[i].Elm_v_Gyak&&csoportszam==(*reg_tanarok)[i].csoport) {talalt_e=true;sorszam=i;}
        }
        for(int j=0;j<regisztralas_db;j++)
        {
          free(regisztraltak[j].megkulonbozteto_adat);
          free(regisztraltak[j].jelszo);
        }
        free(felhasznalo->felhasznalonev);
        free(regisztraltak);
    }
    if(regisztralt==true) {*bejelentkezett=false;printf("hello");}
    else *bejelentkezett=true;
    return sorszam;
}
void tipusok_kiiras()
{
    printf("%-15s","Név:") ;
    printf("%11s","Neptun-kód:");
    printf("%11s","Csoportok:");
    for(int i=0;i<6;i++)
    {
            char sorszam='0'+i+1;
            int hossz=strlen("KZH");
            char *kiszh=(char*) malloc(sizeof(char)*(hossz+2));
            strcpy(kiszh,"KZH");
            kiszh[hossz]=sorszam;
            kiszh[hossz+1]='\0';
            printf("%10s:",kiszh);
            free(kiszh);
    }
     printf("%11s","kZH pont:");
     printf("%9s","ZH1:" );
     printf("%11s","ZH2:");
     printf("%11s","ZH pont:");
     printf("%11s","nagy hf:");
     printf("%11s","lab h:");
     printf("%11s","gyak h:");
     printf("%11s","szorgalmi:");
     printf("%11s","összpont:");
     printf("%11s\n","jegy:");
}
void diak_kiiratas(Diak_Profil bejelentkezo)
{
     tipusok_kiiras();
     printf("%-17s",bejelentkezo.teljes_nev);
     printf("%8s",bejelentkezo.Neptun_kod);
     printf("   E%d / G%d",bejelentkezo.elmelet_csoport,bejelentkezo.gyakorlat_csoport);
     Eredmeny_Lista *tanulo_eredmenyei=NULL;
     tanulo_eredmenyei=minden_eredmeny_hozzafuzes(tanulo_eredmenyei,bejelentkezo);
     eredmeny_lista_kiir(tanulo_eredmenyei);
     eredmeny_lista_felszabadit(tanulo_eredmenyei);
     printf("\n");
     if(bejelentkezo.aktualis_eredmeny.gyak_hianyzas>3) printf("Túl sok gyakorlatról hiányoztál. ");
     if(bejelentkezo.aktualis_eredmeny.lab_hianyzas>3) printf("Túl sok laborról hiányoztál. ");
     if(bejelentkezo.aktualis_eredmeny.ZH_pont<40) printf("Nem értél el elég pontot a ZH-kon.Pót zht kell írnod.");
     if(bejelentkezo.aktualis_eredmeny.NagyHazi<10) printf("Nem sikerült elég pontot szerezned a nagy házidra. Nagy házi pótlást kell leadj. ");
     if(bejelentkezo.aktualis_eredmeny.KisZH_pont<20) printf("Túl kevés pontot szereztél a kis ZH-kon. ");
     if(bejelentkezo.aktualis_eredmeny.vegsojegy==0) printf("Nem teljesitetted a tantárgykövetelményeket.\n ");
     printf("\n");
}
void csoport_kiiratas(Tanar_Profil bejelentkezo,Diak_Profil **diakok, int diak_db)
{
    printf("Oktató neve:%s Csoport neve:",bejelentkezo.teljes_nev);
    if(bejelentkezo.Elm_v_Gyak==Elmelet) printf("E%d\n",bejelentkezo.csoport);
                                    else printf("G%d\n",bejelentkezo.csoport);
    bool kilepes=false;
    char kilepo_karakter;
    while(kilepes==false){
        printf("Mi alapján szeretnéd rangsorolni?\n");
    printf("Következõket lehet választani:ZH1,ZH2,ZH pont,KZH1,KZH2,KZH3,KZH4,KZH5,KZH6,kis ZH pont,");
    printf("nagy házi,labor hiányzás,gyakorlat hiányzás,szorgalmi pont,összes pont,végsõ jegy.\n");
    bool sikeres_beolvasas=false;
    char *rangsor_tipus;
    while(sikeres_beolvasas==false){

        rangsor_tipus=sztring_beolvasas('\n');
        if(eredmenytipus_hasonlitas((*diakok)[0],rangsor_tipus)==0) hibauzenet();
        else sikeres_beolvasas=true;
    }
    tipusok_kiiras();
    Diak_Lista_sikeres *sikeresek_eleje=NULL;
    if(strcmp(rangsor_tipus,"végsõ jegy")==0){
            Diak_Lista_sikertelen *sikertelenek_eleje=NULL;
            for(int i=0;i<diak_db;i++)
            if((bejelentkezo.Elm_v_Gyak==Elmelet&&(*diakok)[i].elmelet_csoport==bejelentkezo.csoport)||
               (bejelentkezo.Elm_v_Gyak==Gyakorlat&&(*diakok)[i].gyakorlat_csoport==bejelentkezo.csoport)){
                if((*diakok)[i].aktualis_eredmeny.vegsojegy>0)
                    sikeresek_eleje=csokkeno_felepites_sikeres(sikeresek_eleje,(*diakok)[i],"összes pont");
                 else sikertelenek_eleje=csokkeno_felepites_sikertelen(sikertelenek_eleje,(*diakok)[i],"összes pont");
            }

            atmeno_diak_lista_kiir_elore(sikeresek_eleje);
            bukott_diak_lista_kiir_elore(sikertelenek_eleje);
            atmeno_diak_lista_felszabadit(sikeresek_eleje);
            bukott_diak_lista_felszabadit(sikertelenek_eleje);
    }
    else{
        for(int i=0;i<diak_db;i++)
            if((bejelentkezo.Elm_v_Gyak==Elmelet&&(*diakok)[i].elmelet_csoport==bejelentkezo.csoport)||
               (bejelentkezo.Elm_v_Gyak==Gyakorlat&&(*diakok)[i].gyakorlat_csoport==bejelentkezo.csoport))
              {
                  sikeresek_eleje=csokkeno_felepites_sikeres(sikeresek_eleje,(*diakok)[i],rangsor_tipus);
              }
         atmeno_diak_lista_kiir_elore(sikeresek_eleje);
         atmeno_diak_lista_felszabadit(sikeresek_eleje);
    }
    free(rangsor_tipus);
    printf("Irj egy *-ot ha ki szeretnél lépni, bármi mást ha folytatni szeretnéd.(elõször amit irsz nem számit)\n");
    while (getchar() != '\n');
    kilepo_karakter=getchar();
    while (getchar() != '\n');
    if(kilepo_karakter=='*') {kilepes=true;}
    }
}
Diak_Profil *fomenu(int *meret)
{
    #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif
    Prog1_Profil prog1_felhasznalo;
    Diak_Profil *keresett_diak=NULL;
    Tanar_Profil *keresett_tanar=NULL;
    int db_diak=0,db_tanar=0;
    bool bejelentkezett=false;
    int keresett_sorszam=bejelentkezes_vagy_regisztracio(&prog1_felhasznalo,&keresett_diak,&keresett_tanar,&db_diak,&db_tanar,&bejelentkezett);
    if(keresett_diak==NULL) printf("Hiba");
    if(prog1_felhasznalo.tanar_vagy_diak==diak)
        diak_kiiratas(keresett_diak[keresett_sorszam]);
    else{
        csoport_kiiratas(keresett_tanar[keresett_sorszam],&keresett_diak,db_diak);
        for(int i=0;i<db_tanar;i++) free(keresett_tanar[i].teljes_nev);
        free(keresett_tanar);
    }
    if(bejelentkezett==false){
        free(prog1_felhasznalo.megkulonbozteto_adat);
        free(prog1_felhasznalo.jelszo);
        free(prog1_felhasznalo.felhasznalonev);
    }
    *meret=db_diak;
    return keresett_diak;
}
