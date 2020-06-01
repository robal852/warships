/* 
Program zaliczeniowy
Wykonawca: Albert Surmacz
Data: grudzien 2018
Wersja 10.01.2019
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "statki.h"

int main(int argc, char *argv[]){
    int i, j, k, l=1, op=0, liczba_masztow_moja, liczba_masztow_przeciwnika, komunikat_moj, komunikat_przeciwnika, komunikat;
    int zatopiony2=1, trafiony_zatopiony_moj=0, zatopiony1=1, trafiony_zatopiony=0, poziom_trudnosci;
    int X, Y, czy_juz_zatopiony;/*1 tak juz zatopiony lub nie zacząłem zadnego zatapiać jeszcze, 2 nie jeszcze nie zatopiony ale juz trafiony byl*/
    int trzeci_celny,czwarty_celny;/*1 gdy przeciwnik chce strzelic trzeci raz w ten sam statek*/
    int trzeci2x,trzeci2y, trzeci3x, trzeci3y,piaty;
    char **pole_gry = malloc(10*sizeof(char*));
    srand(time(0));
    for(i=0;i<10;i++){
        pole_gry[i]=malloc(10*sizeof(char));
    }
    char **pole_gry_przeciwnika = malloc(10*sizeof(char*));
    for(i=0;i<10;i++){
        pole_gry_przeciwnika[i]=malloc(10*sizeof(char));
    }
    char opcja[7]="--help";
    char opcja_2[3]="-h";
    char opcja_3[15]="-gotowe_statki";

    for(i=1;i<argc;i++){
        j = strcmp(argv[i], opcja);
        k = strcmp(argv[i], opcja_2);
	l = strcmp(argv[i], opcja_3);
	if(l==0) op=1;
        if(j==0||k==0){
            instrukcje();
	return 0;
	}    
    }
    wyczysc_pole_gry(&pole_gry);
    wyczysc_pole_gry(&pole_gry_przeciwnika);
    if(op==1){
	wstaw_czteromasztowiec_automatycznie(&pole_gry);
	wstaw_trzymasztowiec_automatycznie(&pole_gry);
	wstaw_trzymasztowiec_automatycznie(&pole_gry);
	wstaw_dwumasztowiec_automatycznie(&pole_gry);
	wstaw_dwumasztowiec_automatycznie(&pole_gry);
	wstaw_dwumasztowiec_automatycznie(&pole_gry);
	wstaw_jednomasztowiec_automatycznie(&pole_gry);
	wstaw_jednomasztowiec_automatycznie(&pole_gry);
	wstaw_jednomasztowiec_automatycznie(&pole_gry);
	wstaw_jednomasztowiec_automatycznie(&pole_gry);
    }else{
        rysuj_moje_pole_gry(&pole_gry);
        wstaw_czteromasztowiec(&pole_gry);
        wstaw_trzymasztowiec(&pole_gry);
        wstaw_trzymasztowiec(&pole_gry);
        wstaw_dwumasztowiec(&pole_gry);
        wstaw_dwumasztowiec(&pole_gry);
        wstaw_dwumasztowiec(&pole_gry);
        wstaw_jednomasztowiec(&pole_gry);
        wstaw_jednomasztowiec(&pole_gry);
        wstaw_jednomasztowiec(&pole_gry);
        wstaw_jednomasztowiec(&pole_gry);
    }
    wstaw_czteromasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_trzymasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_trzymasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_dwumasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_dwumasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_dwumasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_jednomasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_jednomasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_jednomasztowiec_automatycznie(&pole_gry_przeciwnika);
    wstaw_jednomasztowiec_automatycznie(&pole_gry_przeciwnika);

    do{
        printf("\e[1;1H\e[2J");
        printf("\n Wybierz poziom trudnosci:\n LATWY   wpisz 1\n SREDNI  wpisz 2\n EKSPERT wpisz 3\n");
	k=scanf("%d", &poziom_trudnosci);
    }while ( !( (poziom_trudnosci==1) || (poziom_trudnosci==2)  || (poziom_trudnosci==3) ) );

    rysuj_pola_gry(&pole_gry, &pole_gry_przeciwnika);

    liczba_masztow_moja=20;
    liczba_masztow_przeciwnika=20;
    komunikat_moj=liczba_masztow_przeciwnika;
    komunikat_przeciwnika=liczba_masztow_moja;
    for(;;){
        oddaj_strzal(&pole_gry_przeciwnika, &liczba_masztow_przeciwnika, &trafiony_zatopiony);
        rysuj_pola_gry(&pole_gry, &pole_gry_przeciwnika);
        if(liczba_masztow_przeciwnika==0){
            printf("GRATULACJE\n");
            break;
        }
/*PRZED ODDANIEM STRZALU PRZECIWNIKA SPRAWDZAM CZY NIE ZACZĄŁ JUŻ ZATAPIAĆ JAKIEGOŚ STATKU WIĘC BĘDZIE STRZELAŁ INNĄ FUNKCJĄ JEŚLI ZACZĄŁ ZATAPIAĆ JAKIŚ STATEK ALE NIE ZATOPIŁ JESZCZE
A JESLI JUZ ZATOPIŁ LUB JESZCZE ZADNEGO NIE ZACZĄŁ ZATAPIAĆ TO STRZELAM NORMALNĄ FUNKCJĄ TYLKO MUSI ZWRÓCIĆ MI INFO ZE JEŚLI ZACZYNAM KOGOŚ ZATAPIAĆ*/
        if(czy_juz_zatopiony==2){
	    if(czwarty_celny==1){
	        czwarty_celny_strzal_przeciwnika(&pole_gry, &liczba_masztow_moja, &trafiony_zatopiony_moj, &czy_juz_zatopiony,&trzeci_celny, &X, &Y,&trzeci2x,&trzeci2y, &trzeci3x, &trzeci3y,&czwarty_celny, &piaty );
	    }else if(trzeci_celny==1){
		trzeci_celny_strzal_przeciwnika(&pole_gry, &liczba_masztow_moja, &trafiony_zatopiony_moj, &czy_juz_zatopiony,&trzeci_celny, &trzeci2x, &trzeci2y, &trzeci3x, &trzeci3y,&czwarty_celny);
	    }else{
		strzal_przeciwnika_po_trafieniu(&pole_gry, &liczba_masztow_moja, &trafiony_zatopiony_moj, &czy_juz_zatopiony, X, Y,&trzeci_celny, &trzeci2x, &trzeci2y, &trzeci3x, &trzeci3y);
            }
        }else{
		strzal_przeciwnika(&pole_gry, &liczba_masztow_moja, &trafiony_zatopiony_moj, &poziom_trudnosci, &czy_juz_zatopiony, &X, &Y);
	}
        rysuj_pola_gry(&pole_gry, &pole_gry_przeciwnika);
/*jesli trafilem to l masztow przeciwnika sie mniejszyla o 1*/
        if(komunikat_moj-liczba_masztow_przeciwnika==1){
            komunikat_moj=liczba_masztow_przeciwnika;
	    if(zatopiony2-trafiony_zatopiony==0){
		printf(" TRAFIONY-ZATOPIONY!\n");
		zatopiony2++;
	    }else{
                komunikat = rand();
                komunikat = komunikat%7;
                switch (komunikat){
                    case 0:
                    printf(" TRAFIONY!\n");
                    break;
                    case 1:
                    printf(" JESZCZE RAZ I POJDZIE W PIACH!\n");
                    break;
                    case 2:
                    printf(" PRZECIWNIK OBERWAL!\n");
                    break;
                    case 3:
                    printf(" PODOBALO SIE..? MAM WIECEJ!\n");
                    break;
                    case 4:
                    printf(" DORWALISMY GO!\n");
                    break;
                    case 5:
                    printf(" WESZLO JAK W MASLO!\n");
                    break;
                    case 6:
                    printf(" TO MUSIAL POCZUC!\n");
                    break;
                }
	    }
        }else{
            komunikat = rand();
            komunikat = komunikat%3;
            switch (komunikat){
                case 0:
                printf(" PUDLO!\n");
                break;
                case 1:
                printf(" TYM GO NIE POKONAMY!\n");
                break;
                case 2:
                printf(" BYLO BLISKO!\n");
                break;
	        }
        }
/*po strzale przeciwnika*/
        if(komunikat_przeciwnika-liczba_masztow_moja==1){
            komunikat_przeciwnika=liczba_masztow_moja;
	    if(zatopiony1-trafiony_zatopiony_moj==0){
		printf(" NASZ STATEK POSZEDL NA DNO!\n");
		zatopiony1++;
	    }else{
                komunikat = rand();
                komunikat = komunikat%3;
                switch (komunikat){
                    case 0:
                    printf(" PRZECIWNIK TRAFIL!\n");
                    break;
                    case 1:
                    printf(" DOSTALISMY!\n");
                    break;
                    case 2:
                    printf(" OBERWALISMY!\n");
                    break;
	        }
	    }
        }else{
            komunikat = rand();
            komunikat = komunikat%3;
            switch (komunikat){
                case 0:
                printf(" PRZECIWNIK SPUDLOWAL!\n");
                break;
                case 1:
                printf(" MIELISMY SZCZESCIE!\n");
                break;
                case 2:
                printf(" CHYBA STRZELAL PANU BOGU W OKNO!\n");
                break;
            }
        }
        if(liczba_masztow_moja==0){
            printf("PRZECIWNIK WYGRAL\n");
            break;
        }
    }
    printf("KONIEC GRY\n");
return 0;
}

