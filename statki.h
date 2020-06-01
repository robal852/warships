void instrukcje();
void wyczysc_pole_gry(char ***pole_gry);
void rysuj_moje_pole_gry(char ***pole_gry);
void rysuj_pola_gry(char ***pole_gry, char ***pole_gry_przeciwnika);
void wskaz_wspolrzedneXY(int *wspolrzednaX, int *wspolrzednaY);
int sprawdz_pole_i_jego_otoczenie(int wspolrzednaX, int wspolrzednaY,char ***pole_gry);
int sprawdz_czy_pole_ma_kontakt_z_zatopionym(int X, int Y, char ***pole_gry);
void wstaw_jednomasztowiec(char ***pole_gry);
void wstaw_dwumasztowiec(char ***pole_gry);
void wstaw_trzymasztowiec(char ***pole_gry);
void wstaw_czteroomasztowiec(char ***pole_gry);
void wstaw_jednomasztowiec_automatycznie(char ***pole_gry);
void wstaw_dwumasztowiec_automatycznie(char ***pole_gry);
void wstaw_trzymasztowiec_automatycznie(char ***pole_gry);
void wstaw_czteromasztowiec_automatycznie(char ***pole_gry);
void strzal_przeciwnika(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *poziom_trudnosci, int *czy_juz_zatopiony, int *X, int *Y);
void oddaj_strzal(char ***pole_gry, int *liczba_masztow_przeciwnika, int *trafiony_zatopiony);
void sprawdz_czy_zatopiony(char ***pole_gry, int *wspolrzednaX, int *wspolrzednaY, int *zatopiony);
void zatop_statek(char*** pole_gry, int *wspolrzednaX, int *wspolrzednaY);
void strzal_przeciwnika_po_trafieniu(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *czy_juz_zatopiony, int X, int Y,int *trzeci_celny, int *trzeci2x, int *trzeci2y, int *trzeci3x, int *trzeci3y);
void trzeci_celny_strzal_przeciwnika(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *czy_juz_zatopiony, int *trzeci_celny, int *trzeci2x, int *trzeci2y, int *trzeci3x, int *trzeci3y, int *czwarty_celny);
void czwarty_celny_strzal_przeciwnika(char ***pole_gry, int *liczba_masztow_moja, int *trafiony_zatopiony_moj, int *czy_juz_zatopiony,int *trzeci_celny,int *X, int *Y, int *trzeci2x, int *trzeci2y,int *trzeci3x, int *trzeci3y, int *czwarty_celny, int *piaty);
