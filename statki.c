/*
Program zaliczeniowy
Wykonawca: Albert Surmacz
Data: grudzien 2018
Wersja 10.01.2019
*/
#include <stdio.h>
#include <time.h>
void instrukcje(){
    printf("\e[1;1H\e[2J");
    printf(" Witaj! \nInstrukcja gry w statki: \n-Na początku wedlug pojawiajacych sie komunikatow ustawiamy swoje statki:\n czteromasztowiec, dwa trojmasztowce, trzy dwumasztowce i cztery jednomasztowce.\n-Gdy mamy podac wspolrzedne wpisujemy dwa znaki: liczbe z zakresu 0-9 oraz litere od a do j wedlug wzoru: a0 lub 0a lub A0 lub 0A. \n\nPAMIETAJ STATKI NIE MOGA SIE STYKAC\n\n");
    printf("-Jesli chcemy pominac etap rozstawiania statkow i od razu cieszyc sie rozgrywka\n istnieje mozliwosc uruchomienia programu z opcja: -gotowe_statki\n");
    printf("Przebieg gry: \n Wybieramy jeden z trzech poziomow trudnosci.\n Wskazujemy wspolrzedne strzalu na zmiane z komputerem. \n Gra konczy sie w momencie wystrzelania wszystkich statkow jednego z zawodnikow. \n");
    printf("Oznaczenia:\n ~ - woda\n S - statek\n . - chybiony\n + - trafiony\n X - zatopiony\n");
    printf("Dodatkowe informacje:\n 1. Dla czytelnej gry zalecana maksymalizacja okna oraz powiekszenie czcionki w konsoli.\n 2. Program zostal zabezpieczony przed zlosliwym uzytkownikiem\n    i w przypadku wpisywania blednych polecen program bedzie cierpliwie\n    oczekiwal na poprawne komendy ;)\n");
    printf(" Zapraszam do gry.\n Powodzenia!\n");
}

void wyczysc_pole_gry(char ***pole_gry){
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            (*pole_gry)[i][j]='w'; /*w oznacza woda*/
        }
    }
}

void rysuj_moje_pole_gry(char ***pole_gry){
    int i,j;
    printf("\e[1;1H\e[2J");/*odswierza ekran*/
    printf("TWOJE POLE GRY\n ");
    for(i=0;i<10;i++){
        printf(" %d",i);
    }
    for(i=0;i<10;i++){
        printf("\n");
        printf("%c", (int)'A'+i);
        for (j=0;j<10;j++){
            switch ((*pole_gry)[j][i]){
            case 'w':
            printf(" ~");
            break;
            case 's':
            printf(" S");
            break;
            case 't':
            printf(" +");
            break;
            case 'p':
            printf(" o");
            break;
            case 'z':
            printf(" X");
            break;
            default:
            printf("%c",(*pole_gry)[j][i]);
            }
        }
    }
}

void rysuj_pola_gry(char ***pole_gry, char ***pole_gry_przeciwnika){
    int i,j;
    printf("\e[1;1H\e[2J");
    printf("TWOJE POLE GRY\n ");
    for(i=0;i<10;i++){
        printf(" %d",i);
    }
    for(i=0;i<10;i++){
        printf("\n");
        printf("%c", (int)'A'+i);
        for (j=0;j<10;j++){
            switch ((*pole_gry)[j][i]){
            case 'w':
            printf(" ~");
            break;
            case 's':
            printf(" S");
            break;
            case 't':
            printf(" +");
            break;
            case 'p':
            printf(" .");
            break;
            case 'z':
            printf(" X");
            break;
            default:
            printf("%c",(*pole_gry)[j][i]);
            }
        }
    }
    printf("\n\nPOLE GRY PRZECIWNIKA\n ");
        for(i=0;i<10;i++){
        printf(" %d",i);
    }
    for(i=0;i<10;i++){
        printf("\n");
        printf("%c", (int)'A'+i);
        for (j=0;j<10;j++){
            switch ((*pole_gry_przeciwnika)[j][i]){
            case 'w':/*woda*/
            printf(" ~");
            break;
            case 's':
            printf(" ~");/*statek przeciwnika nie jest widoczny*/
            break;
            case 't':/*trafiony*/
            printf(" +");
            break;
            case 'p':/*pudlo*/
            printf(" .");
            break;
            case 'z':
            printf(" X");
            break;
            default:
            printf("%c",(*pole_gry_przeciwnika)[j][i]);
            }
        }
    }
    printf("\n\n");
}

void wskaz_wspolrzedneXY(int *wspolrzednaX, int *wspolrzednaY){
    char XY[20];
    int i;
    i=scanf("%s",XY);
/*wpisane a0 A0 itp*/
    if(XY[0]>64 && XY[0]<75){
        *wspolrzednaY = XY[0]-65;
    }
    if(XY[0]>96 && XY[0]<107){
        *wspolrzednaY = XY[0]-97;
    }
    if(XY[1]>47 && XY[1]<58){
        *wspolrzednaX = XY[1]-48;
    }
/*wpisane odwrotnie 0a 0A..*/
    if(XY[1]>64 && XY[1]<75){
        *wspolrzednaY = XY[1]-65;
    }
    if(XY[1]>96 && XY[1]<107){
        *wspolrzednaY = XY[1]-97;
    }
    if(XY[0]>47 && XY[0]<58){
        *wspolrzednaX = XY[0]-48;
    }
/*gdy wpisane zle za pierwszym razem*/
    while( (!( ( ( XY[0]>64 && XY[0]<75 ) || ( XY[0]>96 && XY[0]<107 ) ) && ( XY[1]>47 && XY[1]<58 ) && (XY[2]=='\0') )) && (!( ( ( XY[1]>64 && XY[1]<75 ) || ( XY[1]>96 && XY[1]<107 ) ) && ( XY[1]>47 && XY[0]<58 ) && (XY[2]=='\0') ))  ){
    printf("UWAGA: wspolrzedne zostaly wpisane niepoprawnie! \nWpisz jeszcze raz:\n");
    i=scanf("%s",XY);
        if(XY[0]>64 && XY[0]<75){
            *wspolrzednaY = XY[0]-65;
        }
        if(XY[0]>96 && XY[0]<107){
            *wspolrzednaY = XY[0]-97;
        }
        if(XY[1]>47 && XY[1]<58){
            *wspolrzednaX = XY[1]-48;
        }
        if(XY[1]>64 && XY[1]<75){
            *wspolrzednaY = XY[1]-65;
        }
        if(XY[1]>96 && XY[1]<107){
            *wspolrzednaY = XY[1]-97;
        }
        if(XY[0]>47 && XY[0]<58){
            *wspolrzednaX = XY[0]-48;
        }
    }
}

int sprawdz_pole_i_jego_otoczenie(int wspolrzednaX, int wspolrzednaY, char ***pole_gry){
    if(wspolrzednaX>9)return -1;
    if(wspolrzednaY>9)return -1;
    if(wspolrzednaX==0){
        if(wspolrzednaY==0){
            if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY+1]=='s')){
                return -1;/*-1 CZYLI ZNALAZLEM STATEK W OTOCZENIU CZYLI NIE BEDE MOGL POSTAWIC STATKU*/
            }else{
                return 1;/*1 CZYLI NIE ZNALAZLEM STATKU W OTOCZENIU CZYLI BEDE STAWIAL STATEK*/
            }
        }else if(wspolrzednaY==9){
            if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY-1]=='s')){
                return -1;
            }else{
                return 1;
            }
        }else{/*lewa krawedz*/
            if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY+1]=='s') ){
                return -1;
            }else{
                return 1;
            }
        }
    }else if(wspolrzednaX==9){
        if(wspolrzednaY==0){
            if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY+1]=='s')){
                return -1;
            }else{
                return 1;
            }
        }else if(wspolrzednaY==9){
            if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY-1]=='s')){
                return -1;
            }else{
                return 1;
            }
        }else{/*prawa krawedz*/
            if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY-1]=='s') ){
                return -1;
            }else{
                return 1;
            }
        }
    }else if(wspolrzednaY==0){
         if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX+1][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY+1]=='s') ){
                return -1;
            }else{
                return 1;
            }
    }else if(wspolrzednaY==9){
         if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX+1][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY-1]=='s') ){
                return -1;
            }else{
                return 1;
            }
    }else{/*JESTEM W SRODKU I MUSZE SPRAWDZIC 9 POL*/
        if( ((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY]=='s') ||((*pole_gry)[wspolrzednaX+1][wspolrzednaY]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX+1][wspolrzednaY-1]=='s') || ((*pole_gry)[wspolrzednaX-1][wspolrzednaY+1]=='s') ||((*pole_gry)[wspolrzednaX+1][wspolrzednaY+1]=='s') || ((*pole_gry)[wspolrzednaX][wspolrzednaY+1]=='s')){
                return -1;
            }else{
                return 1;
            }
    }
}

int sprawdz_czy_pole_ma_kontakt_z_zatopionym(int X, int Y, char **pole_gry){

    if(X==0){
        if(Y==0){
            if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X+1][Y]=='z') ||((pole_gry)[X][Y+1]=='z') || ((pole_gry)[X+1][Y+1]=='z')){
                return 0;
            }else{
                return 1;
            }
        }else if(Y==9){
            if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X+1][Y]=='z') ||((pole_gry)[X][Y-1]=='z') || ((pole_gry)[X+1][Y-1]=='z')){
                return 0;
            }else{
                return 1;
            }
        }else{/*lewa krawedz*/
            if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X+1][Y]=='z') ||((pole_gry)[X][Y-1]=='z') || ((pole_gry)[X][Y+1]=='z') || ((pole_gry)[X+1][Y-1]=='z') || ((pole_gry)[X+1][Y+1]=='z') ){
                return 0;
            }else{
                return 1;
            }
        }
    }else if(X==9){
        if(Y==0){
            if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X-1][Y]=='z') ||((pole_gry)[X][Y+1]=='z') || ((pole_gry)[X-1][Y+1]=='z')){
                return 0;
            }else{
                return 1;
            }
        }else if(Y==9){
            if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X-1][Y]=='z') ||((pole_gry)[X][Y-1]=='z') || ((pole_gry)[X-1][Y-1]=='z')){
                return 0;
            }else{
                return 1;
            }
        }else{/*prawa krawedz*/
            if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X-1][Y]=='z') ||((pole_gry)[X][Y-1]=='z') || ((pole_gry)[X][Y+1]=='z') || ((pole_gry)[X-1][Y+1]=='z') || ((pole_gry)[X-1][Y-1]=='z') ){
                return 0;
            }else{
                return 1;
            }
        }
    }else if(Y==0){
         if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X-1][Y]=='z') ||((pole_gry)[X+1][Y]=='z') || ((pole_gry)[X][Y+1]=='z') || ((pole_gry)[X-1][Y+1]=='z') || ((pole_gry)[X+1][Y+1]=='z') ){
                return 0;
            }else{
                return 1;
            }
    }else if(Y==9){
         if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X-1][Y]=='z') ||((pole_gry)[X+1][Y]=='z') || ((pole_gry)[X-1][Y-1]=='z') || ((pole_gry)[X][Y-1]=='z') || ((pole_gry)[X+1][Y-1]=='z') ){
                return 0;
            }else{
                return 1;
            }
    }else{/*JESTEM W SRODKU I MUSZE SPRAWDZIC 9 POL*/
        if( ((pole_gry)[X][Y]=='z') || ((pole_gry)[X-1][Y]=='z') ||((pole_gry)[X+1][Y]=='z') || ((pole_gry)[X-1][Y-1]=='z') || ((pole_gry)[X][Y-1]=='z') || ((pole_gry)[X+1][Y-1]=='z') || ((pole_gry)[X-1][Y+1]=='z') ||((pole_gry)[X+1][Y+1]=='z') || ((pole_gry)[X][Y+1]=='z')){
                return 0;
            }else{
                return 1;
            }
    }
}

void wstaw_jednomasztowiec(char ***pole_gry){
    int wspolrzednaX, wspolrzednaY;
    int poprawnosc_pola=99;/*wartosci -1 to niepoprawne, 1 to poprawne*/
    printf("\nWskaz wspolrzedne swojego jednomasztowca:\n");
    wskaz_wspolrzedneXY(&wspolrzednaX, &wspolrzednaY);
    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
    while(poprawnosc_pola!=1){
        printf("UWAGA: Statek styka sie z innym statkiem!\nWskaz wspolrzedne swojego jednomasztowca ponownie:\n");
        wskaz_wspolrzedneXY(&wspolrzednaX, &wspolrzednaY);
	poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
    }
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    rysuj_moje_pole_gry(pole_gry);
}

void wstaw_dwumasztowiec(char ***pole_gry){
    int i, poprawnosc_pola=99, poprawnosc_pola_2=99, wspolrzednaX=99, wspolrzednaY=99;
    char orientacja_statku[20];
    do{
        rysuj_moje_pole_gry(pole_gry);
        printf("\nUstaw swój dwumasztowiec:\nBy ustawic w pionie wpisz 1, by ustawic w poziomie wpisz 2:\n");
	i=scanf("%s", orientacja_statku);
    }while ( !( ( (orientacja_statku[0]=='1') || (orientacja_statku[0]=='2') ) && (orientacja_statku[1]=='\0') ) );
    printf("Wskaz pierwsza wspolrzedna swojego dwumasztowca: \n");
    if(orientacja_statku[0]=='1'){
        wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
        poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
        poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
    }else{
        wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
        poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
        poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
    }
    while(poprawnosc_pola!=1 || poprawnosc_pola_2!=1){
        printf("UWAGA: Statek wychodzi poza pole gry lub styka sie z innym statkiem!");
        printf("\nWskaz pierwsza wspolrzedna swojego trzymasztowca ponownie: \n");
        if(orientacja_statku[0]=='1'){
            wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
	    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
        }else{
            wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
            poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
        }
    }
    if(orientacja_statku[0]=='1'){
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+1]='s';
    }else{
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+1][wspolrzednaY]='s';
    }
    rysuj_moje_pole_gry(pole_gry);
}

void wstaw_trzymasztowiec(char ***pole_gry){
    int i, poprawnosc_pola=99, poprawnosc_pola_2=99, poprawnosc_pola_3=99, wspolrzednaX=99, wspolrzednaY=99;
    char orientacja_statku[20];
    do{
        rysuj_moje_pole_gry(pole_gry);
        printf("\nUstaw swój trzymasztowiec:\nBy ustawic w pionie wpisz 1, by ustawic w poziomie wpisz 2: \n");
	i=scanf("%s", orientacja_statku);
    }while ( !( ( (orientacja_statku[0]=='1') || (orientacja_statku[0]=='2') ) && (orientacja_statku[1]=='\0') ) );
    printf("Wskaz pierwsza wspolrzedna swojego trzymasztowca: \n");
    if(orientacja_statku[0]=='1'){
        wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
        poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
        poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
        poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+2, pole_gry);
    }else{
        wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
        poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
        poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
        poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+2, wspolrzednaY, pole_gry);
    }
    while(poprawnosc_pola!=1 || poprawnosc_pola_2!=1 || poprawnosc_pola_3!=1){
        printf("UWAGA: Statek wychodzi poza pole gry lub styka sie z innym statkiem!");
        printf("\nWskaz pierwsza wspolrzedna swojego trzymasztowca ponownie: \n");
        if(orientacja_statku[0]=='1'){
            wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
	    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
	    poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+2, pole_gry);
        }else{
            wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
            poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
            poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+2, wspolrzednaY, pole_gry);
        }
    }
    if(orientacja_statku[0]=='1'){
        (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX][wspolrzednaY+1]='s';
        (*pole_gry)[wspolrzednaX][wspolrzednaY+2]='s';
    }else{
        (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX+1][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX+2][wspolrzednaY]='s';
    }
    rysuj_moje_pole_gry(pole_gry);
}

void wstaw_czteromasztowiec(char ***pole_gry){
    int i, poprawnosc_pola=99, poprawnosc_pola_2=99, poprawnosc_pola_3=99, poprawnosc_pola_4=99, wspolrzednaX=99, wspolrzednaY=99;
    char orientacja_statku[20];
    do{
        rysuj_moje_pole_gry(pole_gry);
        printf("\nUstaw swój czteromasztowiec:\nBy ustawic w pionie wpisz 1, by ustawic w poziomie wpisz 2: \n");
	i=scanf("%s", orientacja_statku);
    }while ( !( ( (orientacja_statku[0]=='1') || (orientacja_statku[0]=='2') ) && (orientacja_statku[1]=='\0') ) );

    printf("Wskaz pierwsza wspolrzedna swojego czteromasztowca: \n");
    if(orientacja_statku[0]=='1'){
        wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
        poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
        poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
        poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+2, pole_gry);
        poprawnosc_pola_4 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+3, pole_gry);
    }else{
        wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
        poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
        poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
        poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+2, wspolrzednaY, pole_gry);
        poprawnosc_pola_4 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+3, wspolrzednaY, pole_gry);
    }
    while(poprawnosc_pola!=1 || poprawnosc_pola_2!=1 || poprawnosc_pola_3!=1 ||  poprawnosc_pola_4!=1){
        printf("UWAGA: Statek wychodzi poza pole gry!");
        printf("\nWskaz pierwsza wspolrzedna swojego czteromasztowca ponownie: \n");
        if(orientacja_statku[0]=='1'){
            wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
	    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
	    poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+2, pole_gry);
	    poprawnosc_pola_4 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+3, pole_gry);
        }else{
            wskaz_wspolrzedneXY(&wspolrzednaX,&wspolrzednaY);
            poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
            poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+2, wspolrzednaY, pole_gry);
            poprawnosc_pola_4 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+3, wspolrzednaY, pole_gry);
        }
    }
    if(orientacja_statku[0]=='1'){
        (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX][wspolrzednaY+1]='s';
        (*pole_gry)[wspolrzednaX][wspolrzednaY+2]='s';
        (*pole_gry)[wspolrzednaX][wspolrzednaY+3]='s';
    }else{
        (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX+1][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX+2][wspolrzednaY]='s';
        (*pole_gry)[wspolrzednaX+3][wspolrzednaY]='s';
    }
    rysuj_moje_pole_gry(pole_gry);
}

/*statki przeciwnika ustawiane metodą brute force*/
void wstaw_jednomasztowiec_automatycznie(char ***pole_gry){
    int wspolrzednaX, wspolrzednaY, liczba_losowa, poprawnosc_pola=99;

    while(poprawnosc_pola!=1){
        liczba_losowa = rand();
        wspolrzednaX = liczba_losowa%10;
        liczba_losowa = rand();
        wspolrzednaY = liczba_losowa%10;
	poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
    }
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
}

void wstaw_dwumasztowiec_automatycznie(char ***pole_gry){
    int wspolrzednaX, wspolrzednaY, liczba_losowa, poprawnosc_pola=99, poprawnosc_pola_2=99, orientacja;/*orientacja 1 -pion,0 -poziom*/
    while(poprawnosc_pola!=1 || poprawnosc_pola_2!=1){
        liczba_losowa = rand();
	orientacja = liczba_losowa%2;
        liczba_losowa = rand();
        wspolrzednaX = liczba_losowa%10;
        liczba_losowa = rand();
        wspolrzednaY = liczba_losowa%10;
        if(orientacja==1){
	    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
        }else{
            poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
        }
    }
    if(orientacja==1){
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+1]='s';
    }else{
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+1][wspolrzednaY]='s';
    }
}

void wstaw_trzymasztowiec_automatycznie(char ***pole_gry){
    int wspolrzednaX, wspolrzednaY, liczba_losowa, poprawnosc_pola=99, poprawnosc_pola_2=99, poprawnosc_pola_3=99, orientacja;
    while(poprawnosc_pola!=1 || poprawnosc_pola_2!=1 || poprawnosc_pola_3!=1){
        liczba_losowa = rand();
	orientacja = liczba_losowa%2;
        liczba_losowa = rand();
        wspolrzednaX = liczba_losowa%10;
        liczba_losowa = rand();
        wspolrzednaY = liczba_losowa%10;
        if(orientacja==1){
	    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
            poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+2, pole_gry);
        }else{
            poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
            poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+2, wspolrzednaY, pole_gry);
        }
    }
    if(orientacja==1){
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+1]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+2]='s';
    }else{
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+1][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+2][wspolrzednaY]='s';
    }
}

void wstaw_czteromasztowiec_automatycznie(char ***pole_gry){
    int wspolrzednaX, wspolrzednaY, liczba_losowa, poprawnosc_pola=99, poprawnosc_pola_2=99, poprawnosc_pola_3=99, poprawnosc_pola_4=99, orientacja;
    while(poprawnosc_pola!=1 || poprawnosc_pola_2!=1 || poprawnosc_pola_3!=1 || poprawnosc_pola_4!=1){
        liczba_losowa = rand();
	orientacja = liczba_losowa%2;
        liczba_losowa = rand();
        wspolrzednaX = liczba_losowa%10;
        liczba_losowa = rand();
        wspolrzednaY = liczba_losowa%10;
        if(orientacja==1){
	    poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+1, pole_gry);
            poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+2, pole_gry);
            poprawnosc_pola_4 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY+3, pole_gry);
        }else{
            poprawnosc_pola =  sprawdz_pole_i_jego_otoczenie(wspolrzednaX, wspolrzednaY, pole_gry);
            poprawnosc_pola_2 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+1, wspolrzednaY, pole_gry);
            poprawnosc_pola_3 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+2, wspolrzednaY, pole_gry);
            poprawnosc_pola_4 = sprawdz_pole_i_jego_otoczenie(wspolrzednaX+3, wspolrzednaY, pole_gry);
        }
    }
    if(orientacja==1){
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+1]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+2]='s';
    (*pole_gry)[wspolrzednaX][wspolrzednaY+3]='s';
    }else{
    (*pole_gry)[wspolrzednaX][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+1][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+2][wspolrzednaY]='s';
    (*pole_gry)[wspolrzednaX+3][wspolrzednaY]='s';
    }
}

void sprawdz_czy_zatopiony(char ***pole_gry, int *wspolrzednaX, int *wspolrzednaY, int *zatopiony){
    int x, y, k;
    x = *wspolrzednaX;
    y = *wspolrzednaY;
    (*pole_gry)[x][y]='g';/*ustalam na g zeby nie sprawdzalo spowrotem tego pola*/
/*sprawdzam najpierw czy ma kontakt z s*/
    /*narozniki*/
    if(x==0 && y==0){
        if(((*pole_gry)[x+1][y]=='s')||((*pole_gry)[x][y+1]=='s')) *zatopiony=0;
    }
    if(x==9 && y==0){
        if(((*pole_gry)[x-1][y]=='s')||((*pole_gry)[x][y+1]=='s')) *zatopiony=0;
    }
    if(x==9 && y==9){
        if(((*pole_gry)[x-1][y]=='s')||((*pole_gry)[x][y-1]=='s')) *zatopiony=0;
    }
    if(x==0 && y==9){
        if(((*pole_gry)[x+1][y]=='s')||((*pole_gry)[x][y-1]=='s')) *zatopiony=0;
    }
    /*krawedzie bez naroznikow*/
    if(x>0&&x<9&&y==0){
        if(((*pole_gry)[x+1][y]=='s')||((*pole_gry)[x-1][y]=='s')||((*pole_gry)[x][y+1]=='s')) *zatopiony=0;
    }
    if(x>0&&x<9&&y==9){
        if(((*pole_gry)[x+1][y]=='s')||((*pole_gry)[x-1][y]=='s')||((*pole_gry)[x][y-1]=='s')) *zatopiony=0;
    }
    if(y>0&&y<9&&x==0){
        if(((*pole_gry)[x+1][y]=='s')||((*pole_gry)[x][y-1]=='s')||((*pole_gry)[x][y+1]=='s')) *zatopiony=0;
    }
    if(y>0&&y<9&&x==9){
        if(((*pole_gry)[x-1][y]=='s')||((*pole_gry)[x][y-1]=='s')||((*pole_gry)[x][y+1]=='s')) *zatopiony=0;
    }
    /*srodek*/
    if(x>0&&x<9&&y>0&&y<9){
        if(((*pole_gry)[x+1][y]=='s')||((*pole_gry)[x-1][y]=='s')||((*pole_gry)[x][y+1]=='s')||((*pole_gry)[x][y-1]=='s')) *zatopiony=0;
    }
/*sprawdzam czy ma kontakt z t, jak ma kontakt to od nowa dla tego pola sprawdzam*/
    /*narozniki*/
    if(x==0 && y==0){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
        }
    }
    if(x==9 && y==0){
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
        }
        if((*pole_gry)[x][y+1]=='t'){
            k=y+1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    if(x==9 && y==9){
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    if(x==0 && y==9){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    /*krawedzie bez naroznikow*/
    if(x>0&&x<9&&y==0){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    if(x>0&&x<9&&y==9){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
            sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    if(y>0&&y<9&&x==0){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
        }
    }
    if(y>0&&y<9&&x==9){
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    /*srodek*/
    if(x>0&&x<9&&y>0&&y<9){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    sprawdz_czy_zatopiony(pole_gry, &k, &y, zatopiony);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    sprawdz_czy_zatopiony(pole_gry, &x, &k, zatopiony);
	}
    }
    (*pole_gry)[x][y]='t';/*ustalam na t spowrotem bo juz i tak nie wejdzie do tego pola*/
}

void zatop_statek(char*** pole_gry, int *wspolrzednaX, int *wspolrzednaY){
    int x, y, k;
    x = *wspolrzednaX;
    y = *wspolrzednaY;
    (*pole_gry)[x][y]='z';/*gdy wchodze na pole to topie a potem ide dalej*/
    if(x==0 && y==0){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    zatop_statek(pole_gry, &x, &k);
        }
    }
    if(x==9 && y==0){
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    zatop_statek(pole_gry, &k, &y);
        }
        if((*pole_gry)[x][y+1]=='t'){
            k=y+1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
    if(x==9 && y==9){
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
    if(x==0 && y==9){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
    if(x>0&&x<9&&y==0){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
    if(x>0&&x<9&&y==9){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
            zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
    if(y>0&&y<9&&x==0){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    zatop_statek(pole_gry, &x, &k);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    zatop_statek(pole_gry, &x, &k);
        }
    }
    if(y>0&&y<9&&x==9){
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    zatop_statek(pole_gry, &x, &k);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
    if(x>0&&x<9&&y>0&&y<9){
        if((*pole_gry)[x+1][y]=='t'){
	    k=x+1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x-1][y]=='t'){
	    k=x-1;
	    zatop_statek(pole_gry, &k, &y);
	}
        if((*pole_gry)[x][y+1]=='t'){
	    k=y+1;
	    zatop_statek(pole_gry, &x, &k);
	}
        if((*pole_gry)[x][y-1]=='t'){
	    k=y-1;
	    zatop_statek(pole_gry, &x, &k);
	}
    }
}

void oddaj_strzal(char ***pole_gry, int *liczba_masztow_przeciwnika, int *trafiony_zatopiony){
    int wspolrzednaX, wspolrzednaY, zatopiony=5;
    printf("Podaj wspolrzedne strzalu:\n");
    wskaz_wspolrzedneXY(&wspolrzednaX, &wspolrzednaY);
    while( (*pole_gry)[wspolrzednaX][wspolrzednaY]=='p' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='t'|| (*pole_gry)[wspolrzednaX][wspolrzednaY]=='z'){
        printf("UWAGA: Juz tutaj strzelales!\nPonow probe:\n");
        wskaz_wspolrzedneXY(&wspolrzednaX, &wspolrzednaY);
    }
    if((*pole_gry)[wspolrzednaX][wspolrzednaY]=='w'){/*pudlo*/
        (*pole_gry)[wspolrzednaX][wspolrzednaY]='p';
    }
    if((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s'){/*trailem*/
        (*pole_gry)[wspolrzednaX][wspolrzednaY]='t';
        *liczba_masztow_przeciwnika-=1;/*zmniejszam liczbe masztow*/
	zatopiony=1;
        sprawdz_czy_zatopiony(pole_gry, &wspolrzednaX, &wspolrzednaY, &zatopiony);
        if(zatopiony==0){
            (*pole_gry)[wspolrzednaX][wspolrzednaY]='t';/*0 jak posiada zywego sasiada*/
	}else{
	    zatop_statek(pole_gry, &wspolrzednaX, &wspolrzednaY);
	    *trafiony_zatopiony+=1;
        }
    }
}

void strzal_przeciwnika(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *poziom_trudnosci, int *czy_juz_zatopiony, int *x, int *y){
    int liczba_losowa, wspolrzednaX, wspolrzednaY, zatopiony, losowa, celnosc, czy_obok_zatopionego=1;

    if(*poziom_trudnosci==1){
        do{
            liczba_losowa = rand();
            wspolrzednaX = liczba_losowa%10;
            liczba_losowa = rand();
            wspolrzednaY = liczba_losowa%10;
            czy_obok_zatopionego = sprawdz_czy_pole_ma_kontakt_z_zatopionym(wspolrzednaX, wspolrzednaY, *pole_gry);
printf("%d ",czy_obok_zatopionego);
        }while((*pole_gry)[wspolrzednaX][wspolrzednaY]=='p' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='t' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='z'|| czy_obok_zatopionego == 0 );

        if((*pole_gry)[wspolrzednaX][wspolrzednaY]=='w'){
            (*pole_gry)[wspolrzednaX][wspolrzednaY]='p';
        }
        if((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s'){
            (*pole_gry)[wspolrzednaX][wspolrzednaY]='t';
            *liczba_masztow_moja-=1;
            zatopiony=1;
            sprawdz_czy_zatopiony(pole_gry, &wspolrzednaX, &wspolrzednaY, &zatopiony);
            if(zatopiony==0){
	        *czy_juz_zatopiony=2;
		*x = wspolrzednaX;
		*y = wspolrzednaY;
                (*pole_gry)[wspolrzednaX][wspolrzednaY]='t';
	    }else{
	        zatop_statek(pole_gry, &wspolrzednaX, &wspolrzednaY);
	        *trafiony_zatopiony_moj+=1;
            }
        }
    }else{
        if(*poziom_trudnosci==2)celnosc=5;
        if(*poziom_trudnosci==3)celnosc=2;
        losowa = rand();
        if(losowa%celnosc==0){
            do{
                liczba_losowa = rand();
                wspolrzednaX = liczba_losowa%10;
                liczba_losowa = rand();
                wspolrzednaY = liczba_losowa%10;
            czy_obok_zatopionego = sprawdz_czy_pole_ma_kontakt_z_zatopionym(wspolrzednaX, wspolrzednaY, *pole_gry);
printf("%d ",czy_obok_zatopionego);
            }while((*pole_gry)[wspolrzednaX][wspolrzednaY]=='p' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='t' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='z'|| (*pole_gry)[wspolrzednaX][wspolrzednaY]=='w'|| czy_obok_zatopionego == 0 );
        }else{
            do{
                liczba_losowa = rand();
                wspolrzednaX = liczba_losowa%10;
                liczba_losowa = rand();
                wspolrzednaY = liczba_losowa%10;
            }while((*pole_gry)[wspolrzednaX][wspolrzednaY]=='p' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='t' || (*pole_gry)[wspolrzednaX][wspolrzednaY]=='z' );
        }
        if((*pole_gry)[wspolrzednaX][wspolrzednaY]=='w'){
            (*pole_gry)[wspolrzednaX][wspolrzednaY]='p';
        }
        if((*pole_gry)[wspolrzednaX][wspolrzednaY]=='s'){
            (*pole_gry)[wspolrzednaX][wspolrzednaY]='t';
            *liczba_masztow_moja-=1;
	    zatopiony=1;
            sprawdz_czy_zatopiony(pole_gry, &wspolrzednaX, &wspolrzednaY, &zatopiony);
            if(zatopiony==0){
	        *czy_juz_zatopiony=2;
		*x = wspolrzednaX;
		*y = wspolrzednaY;
                (*pole_gry)[wspolrzednaX][wspolrzednaY]='t';
	    }else{
	        zatop_statek(pole_gry, &wspolrzednaX, &wspolrzednaY);
	        *trafiony_zatopiony_moj+=1;
            }
        }
    }
}



void strzal_przeciwnika_po_trafieniu(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *czy_juz_zatopiony, int X, int Y,int *trzeci_celny, int *trzeci2x, int *trzeci2y, int *trzeci3x, int *trzeci3y){
    int gora, prawo, dol, lewo;/*wartosc 5 mowi ze moge tam strzelac*/
    int liczba_losowa;
    int strzal, zatop;
    int x,y;
x=X;
y=Y; 
    Y--;
    if(Y>=0){
        gora = sprawdz_czy_pole_ma_kontakt_z_zatopionym(X, Y, *pole_gry);
        if(((*pole_gry)[X][Y]=='s' || (*pole_gry)[X][Y]=='w' )&& gora==1 ){
            gora=5;
        }  
    }
    Y++;

    X++;
    if(X<10){
        prawo = sprawdz_czy_pole_ma_kontakt_z_zatopionym(X, Y, *pole_gry);
        if( ((*pole_gry)[X][Y]=='s' ||(*pole_gry)[X][Y]=='w' )&& prawo==1 ){
            prawo=5;
        }  
    }
    X--;

    X--;
    if(X>=0){
        lewo = sprawdz_czy_pole_ma_kontakt_z_zatopionym(X, Y, *pole_gry);
        if(((*pole_gry)[X][Y]=='s' || (*pole_gry)[X][Y]=='w') && lewo==1 ){
            lewo=5;
        }  
    }
    X++;

    Y++;
    if(Y<10){
        dol = sprawdz_czy_pole_ma_kontakt_z_zatopionym(X, Y, *pole_gry);
        if(( (*pole_gry)[X][Y]=='s' || (*pole_gry)[X][Y]=='w' )&& dol==1 ){
            dol=5;
        }  
    }
    Y--;
/*losuje tak dlugo az znajde gdzie jeszcze moge strzelac*/
    strzal==0;
    while (strzal==0){
        liczba_losowa = rand();
        liczba_losowa=liczba_losowa%4;
        if(liczba_losowa==0&&gora==5)strzal=1;
        if(liczba_losowa==1&&prawo==5)strzal=2;
        if(liczba_losowa==2&&lewo==5)strzal=3;
        if(liczba_losowa==3&&dol==5)strzal=4;
    }

    if(strzal==1)Y--;
    if(strzal==2)X++;
    if(strzal==3)X--;
    if(strzal==4)Y++;

    if((*pole_gry)[X][Y]=='w'){
        (*pole_gry)[X][Y]='p';
    }
    if((*pole_gry)[X][Y]=='s'){
        (*pole_gry)[X][Y]='t';
        *liczba_masztow_moja-=1;
        zatop=1;
        sprawdz_czy_zatopiony( pole_gry, &x, &y, &zatop);
        if(zatop==0){
           *czy_juz_zatopiony=2;
/*tutaj wiem ze juz drugi strzal byl celny a statek dalej nie jest zatopiony*/
           *trzeci_celny=1;
           *trzeci2x=x;
           *trzeci2y=y;
	   *trzeci3x=X;
	   *trzeci3y=Y;
        }else{
             *trafiony_zatopiony_moj+=1;
             *czy_juz_zatopiony=1;
             zatop_statek(pole_gry, &X, &Y);
        }
    }
}

/*MUSZE DOSTAC WSPOLRZEDNE POPRZEDNICH STRZALOW*/
void trzeci_celny_strzal_przeciwnika(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *czy_juz_zatopiony,int *trzeci_celny, int *trzeci2x, int *trzeci2y,int *trzeci3x, int *trzeci3y, int *czwarty_celny){
    int gora, prawo, lewo,dol,strzal,liczba_losowa,strzalx,strzaly,x1,x2,y1,y2,x,y,zatopiony,x3;
/*sprawdzam czy w pionie czy w poziomie byl ten statek co go zaczalem zatapiac*/
/*poziom*/
x=*trzeci2x;
x3=*trzeci3x;
y=*trzeci2y;
    if(*trzeci2x!=*trzeci3x){
        if(x>x3){
            x1=*trzeci2x;
            x2=*trzeci3x;
        }else{
            x1=*trzeci3x;
            x2=*trzeci2x;
        }
        y1=*trzeci2y;

    x1++;
    if(x1<10){
        prawo = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x1, y1, *pole_gry);
        if(((*pole_gry)[x1][y1]=='s' || (*pole_gry)[x1][y1]=='w' )&& prawo==1 ){
            prawo=5;/**/
        }  
    }
    x1--;

    x2--;
    if(x2>=0){
        lewo = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x2, y1, *pole_gry);
        if(((*pole_gry)[x2][y1]=='s' || (*pole_gry)[x2][y1]=='w' )&& lewo==1 ){
            lewo=5;/**/
        }  
    }
    x2++;


    }else{/*pion*/
        if(*trzeci2y>*trzeci3y){
            y1=*trzeci2y;
            y2=*trzeci3y;
        }else{
            y1=*trzeci3y;
            y2=*trzeci2y;
        }
        x1=*trzeci2x;

    y1++;
    if(y1<10){
        dol = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x1, y1, *pole_gry);
        if(((*pole_gry)[x1][y1]=='s' || (*pole_gry)[x1][y1]=='w' )&& dol==1 ){
            dol=5;/**/
        }  
    }
    y1--;

    y2--;
    if(y2>=0){
        gora = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x1, y2, *pole_gry);
        if(((*pole_gry)[x1][y2]=='s' || (*pole_gry)[x1][y2]=='w' )&& gora==1 ){
            gora=5;/**/
        }  
    }
    y2++;


    }

    strzal==0;
    while (strzal==0){
        liczba_losowa = rand();
        liczba_losowa=liczba_losowa%4;
        if(liczba_losowa==0&&gora==5)strzal=1;
        if(liczba_losowa==1&&prawo==5)strzal=2;
        if(liczba_losowa==2&&lewo==5)strzal=3;
        if(liczba_losowa==3&&dol==5)strzal=4;
    }



    if(strzal==1){
        y2--;
        strzaly=y2;
        strzalx=x1;

    }
    if(strzal==2){
        x1++;
        strzalx=x1;
        strzaly=y1;
    }
    if(strzal==3){
        x2--;
        strzalx=x2;
        strzaly=y1;
    }
    if(strzal==4){
        y1++;
        strzaly=y1;
        strzalx=x1;
    }


    if((*pole_gry)[strzalx][strzaly]=='w'){
        (*pole_gry)[strzalx][strzaly]='p';
    }
    if((*pole_gry)[strzalx][strzaly]=='s'){
        (*pole_gry)[strzalx][strzaly]='t';
        *liczba_masztow_moja-=1;
	zatopiony=1;
        sprawdz_czy_zatopiony( pole_gry, &x, &y, &zatopiony);
        if(zatopiony==0){
           *czy_juz_zatopiony=2;
           *czwarty_celny=1;
           *trzeci3x=strzalx;
           *trzeci3y=strzaly;





        }else{
             *trafiony_zatopiony_moj+=1;
             zatop_statek(pole_gry, &strzalx, &strzaly);
             *czy_juz_zatopiony=1;
             *trzeci_celny=0;
             *czy_juz_zatopiony=0;

        }
    }
}


/*PROBLEM JEST JAK WSPOLRZEDNE PIERWSZEGO TRAFIONEGO NIE SA NA KRANCU*/
void czwarty_celny_strzal_przeciwnika(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *czy_juz_zatopiony,int *trzeci_celny,int *X, int *Y, int *trzeci2x, int *trzeci2y,int *trzeci3x, int *trzeci3y, int *czwarty_celny, int *piaty){
    int gora, prawo, lewo,dol,strzal,liczba_losowa,strzalx,strzaly,x1,x2,y1,y2,x,y,zatopiony,x3,y3;
printf("czwarty");
x=*trzeci2x;
y=*trzeci2y;

x3=*trzeci3x;
y3=*trzeci3y;


if(*piaty==1){
strzalx=*X;
strzaly=*Y;

    if((*pole_gry)[strzalx][strzaly]=='s'){
        (*pole_gry)[strzalx][strzaly]='t';
        *liczba_masztow_moja-=1;
	zatopiony=1;
        sprawdz_czy_zatopiony( pole_gry, &strzalx, &strzaly, &zatopiony);
        if(zatopiony==0){
           *czy_juz_zatopiony=2;
           *czwarty_celny=1;
        }else{
             *trafiony_zatopiony_moj+=1;
             zatop_statek(pole_gry, &strzalx, &strzaly);
             *czy_juz_zatopiony=0;
             *trzeci_celny=0;
	     *czwarty_celny=0;

        }
     }
    *piaty=0;
}else{

    if(*trzeci2x!=*trzeci3x){
        if(x>x3){
            x1=*trzeci2x;/*x1 statek w poziomie a x1 to pierwszy trafiony strzal w ten statek*/
            x2=*trzeci3x;
        }else{

            x1=*trzeci3x;
            x2=*trzeci2x;
        }
        y1=*trzeci2y;


    x1++;
    if(x1<10){
        prawo = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x1, y1, *pole_gry);
        if(((*pole_gry)[x1][y1]=='s' || (*pole_gry)[x1][y1]=='w' )&& prawo==1 ){
            prawo=5;/**/
        }  
    }
    x1--;




    x2--;
    if(x2>=0){
        lewo = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x2, y1, *pole_gry);
        if(((*pole_gry)[x2][y1]=='s' || (*pole_gry)[x2][y1]=='w' )&& lewo==1 ){
            lewo=5;/**/
        }  
    }
    x2++;

    }else{/*pion*/
        if(*trzeci2y>*trzeci3y){
            y1=*trzeci2y;
            y2=*trzeci3y;
        }else{
            y1=*trzeci3y;
            y2=*trzeci2y;
        }
        x1=*trzeci2x;


    y1++;
    if(y1<10){

        dol = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x1, y1, *pole_gry);
        if(((*pole_gry)[x1][y1]=='s' || (*pole_gry)[x1][y1]=='w' )&& dol==1 ){
            dol=5;
        }  
    }
    y1--;


    y2--;
    if(y2>=0){
        gora = sprawdz_czy_pole_ma_kontakt_z_zatopionym(x1, y2, *pole_gry);
        if(((*pole_gry)[x1][y2]=='s' || (*pole_gry)[x1][y2]=='w' )&& gora==1 ){
            gora=5;
        }  
    }
    y2++;


    }

    strzal==0;
    while (strzal==0){
        liczba_losowa = rand();
        liczba_losowa=liczba_losowa%4;
        if(liczba_losowa==0&&gora==5)strzal=1;
        if(liczba_losowa==1&&prawo==5)strzal=2;
        if(liczba_losowa==2&&lewo==5)strzal=3;
        if(liczba_losowa==3&&dol==5)strzal=4;
    }

    if(strzal==1){
        y2--;
        strzaly=y2;
        strzalx=x1;
	y2++;    
    }else if(strzal==2){
        x1++;
        strzalx=x1;
        strzaly=y1;
	x1--;
    }else if(strzal==3){
        x2--;
        strzalx=x2;
        strzaly=y1;
	x2++;   
    }else if(strzal==4){
        y1++;
        strzaly=y1;
        strzalx=x1;
        y1--;
       }



    if((*pole_gry)[strzalx][strzaly]=='w'){
        (*pole_gry)[strzalx][strzaly]='p';
        
       *piaty=1;
	if(strzal==1){
	    *X=strzalx;
	    *Y=strzaly+4;
        }
	if(strzal==2){
	    *X=strzalx-4;
	    *Y=strzaly;
        }
	if(strzal==3){
	    *X=strzalx+4;
	    *Y=strzaly;
        }
	if(strzal==4){
	    *X=strzalx;
	    *Y=strzaly-4;
        }


    }
    if((*pole_gry)[strzalx][strzaly]=='s'){
        (*pole_gry)[strzalx][strzaly]='t';
	   *piaty=0;
        *liczba_masztow_moja-=1;
	zatopiony=1;
        sprawdz_czy_zatopiony( pole_gry, &x, &y, &zatopiony);
        if(zatopiony==0){
           *czy_juz_zatopiony=2;
           *czwarty_celny=1;
        }else{
             *trafiony_zatopiony_moj+=1;
             zatop_statek(pole_gry, &strzalx, &strzaly);
             *czy_juz_zatopiony=0;
             *trzeci_celny=0;
	     *czwarty_celny=0;

        }
    }





}

}

















