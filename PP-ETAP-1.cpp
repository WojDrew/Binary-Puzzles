// PP-ETAP-!.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<stdio.h>
#include<cstdlib>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"conio2.h"

#define WEKTORX_MENU 1		//
#define WEKTORY_MENU 1		//	stale sluzace do zmiany polozenia planszy i legendy
#define WEKTORX_BORDER 45	//
#define WEKTORY_BORDER 1	//
#define PRAWDA 1
#define FALSZ 0
#define NIEMODYFIKOWALNY 0
#define MODYFIKOWALNY 1
#define MIN_PROC 35
#define MAX_PROC 45
#define TRYB_KOLUMNY 0			//
#define TRYB_WIERSZE 1			//  flagi sluzace do wywolywania niektorych funkcji w odpowiednich celach (by nie powielac kodu)
#define TRYB_WPISANIE 1			//
#define TRYB_PODSWIETLENIE 0	//

typedef struct pole {	//struktura opisujaca jedno pole
	int kolor = WHITE;
	int kolortla = BLACK;
	char znak;
	int flaga = MODYFIKOWALNY; //flaga okreslajaca czy pole jest modyfikowalne
}pole_t;

void border(int rozmiar);
void wypisz(pole_t **tab, int rozmiar);
pole_t** inicjuj(int rozmiar);
int regula_1(pole_t **tab, int y, int x, char zn, int rozmiar);
int regula_2(pole_t **tab, int y, int x, char zn, int rozmiar);
int regula_3(pole_t **tab, int y, int x, char zn, int rozmiar);
int* inicjuj_int(int rozmiar);
void wypelnij_0(int *tab, int rozmiar);
void wypelnij_spacjami(char *tab, int rozmiar);
void utworz_szablon_dom(pole_t** tab, int rozmiar);
void wyczysc_plansze(pole_t **tab, int rozmiar);
void losowa_plansza(pole_t **tab, int rozmiar);
void podpowiedz(pole_t **tab, int x, int y, int rozmiar, char *podpowiedz_tab, char *ktora_regula);
int wszystkie_reguly(pole_t **tab, int y, int x, char zn, int rozmiar);
void ktora_regula(pole_t **tab, int x, int y, char zn, int rozmiar, char *reg_1, char *reg_2, char *reg_3);
void utworz_szablon(pole_t** tab, int rozmiar);
void zmiana_rozmiaru(pole_t **tab, int *rozmiar, int *y, int *x);
void mozliwosc_ukonczenia(pole_t **tab, int rozmiar);
char** inicjuj_char(int rozmiar);
char** podpowiedz_do_reguly_2(pole_t **tab, int rozmiar, char zn, int tryb);
int zepsucie_planszy(pole_t **tab, int rozmiar);
void jednoznaczne_pola(pole_t**tab, int rozmiar, int tryb);
void czarne_tlo(pole_t **tab, int rozmiar);														
int mozliwosc_ukonczenia2(pole_t **tab, int rozmiar);		
void usuwanie_pamieci(int rozmiar, pole_t **tab, char **kolumny_c_0, char **kolumny_c_1, char **wiersze_c_1, char **wiersze_c_0);
																								// flaga okreslajaca czy tryb auto. detekcji konca
																								// gry jest wl.
																								//		|
int main() {																					//		|
	int rozmiar = 12, zn = 0, x = rozmiar, y = rozmiar, attr = 7, back = 0, zero = 0, flaga = FALSZ, flaga2 = FALSZ, flaga3 = FALSZ;
	char txt[32], bufor[20], bufor1[20];												// ^
	char podpowiedz_tab[50], ktora_regula_tab[50];										// |
	char **wiersze_c_1, **wiersze_c_0, **kolumny_c_1, **kolumny_c_0;					// flaga okreslajaca czy pola jednoznaczne sa
	wiersze_c_1 = inicjuj_char(rozmiar);												//aktualnie podswietlone
	wiersze_c_0 = inicjuj_char(rozmiar);
	kolumny_c_1 = inicjuj_char(rozmiar);
	kolumny_c_0 = inicjuj_char(rozmiar);
	// jeżeli program jest kompilowany w czystym języku C
	// należy wywołać poniższą linię
#ifndef __cplusplus
	Conio2_Init();
#endif
	pole_t **tab;// tablica przechowywujaca pola planszy
	tab = inicjuj(rozmiar);
	utworz_szablon_dom(tab, rozmiar);
	sprintf(podpowiedz_tab, "Miejsce na podpowiedz");
	sprintf(ktora_regula_tab, "Miejsce na podpowiedz");

	// settitle ustawia tytuł okienka
	settitle("Wojciech Drewek s171838");
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		kolumny_c_1 = podpowiedz_do_reguly_2(tab, rozmiar, '1', TRYB_KOLUMNY);
		kolumny_c_0 = podpowiedz_do_reguly_2(tab, rozmiar, '0', TRYB_KOLUMNY);
		wiersze_c_1 = podpowiedz_do_reguly_2(tab, rozmiar, '1', TRYB_WIERSZE);
		wiersze_c_0 = podpowiedz_do_reguly_2(tab, rozmiar, '0', TRYB_WIERSZE);

		border(rozmiar);

		if (flaga2 == PRAWDA || flaga3 == PRAWDA)
		{
			gotoxy(WEKTORX_BORDER - 1, WEKTORY_BORDER + rozmiar + 2);
			cputs("1:");
			for (int i = 0; i < rozmiar; i++) {
				for (int j = 0; j < 2; j++) {
					gotoxy(WEKTORX_BORDER + i + 1, rozmiar + j + 3);
					putch(kolumny_c_1[i][j]);
				}
			}
			gotoxy(WEKTORX_BORDER - 1, WEKTORY_BORDER + rozmiar + 4);
			cputs("0:");
			for (int i = 0; i < rozmiar; i++) {
				for (int j = 0; j < 2; j++) {
					gotoxy(WEKTORX_BORDER + i + 1, rozmiar + j + 5);
					putch(kolumny_c_0[i][j]);
				}
			}

			gotoxy(rozmiar + WEKTORX_BORDER + 3, WEKTORY_BORDER);
			cputs("1:");
			for (int i = 0; i < rozmiar; i++) {
				gotoxy(rozmiar + WEKTORX_BORDER + 3, WEKTORY_BORDER + i + 1);
				cputs(wiersze_c_1[i]);
			}
			gotoxy(rozmiar + WEKTORX_BORDER + 6, WEKTORY_BORDER);
			cputs("0:");
			for (int i = 0; i < rozmiar; i++) {
				gotoxy(rozmiar + WEKTORX_BORDER + 6, WEKTORY_BORDER + i + 1);
				cputs(wiersze_c_0[i]);
			}
		}
		flaga3 = FALSZ;

		gotoxy(WEKTORX_MENU  + WEKTORX_BORDER, WEKTORY_MENU + rozmiar + 8);
		cputs(podpowiedz_tab);
		gotoxy(WEKTORX_MENU  + WEKTORX_BORDER, WEKTORY_MENU + rozmiar + 9);
		cputs(ktora_regula_tab);

		gotoxy(WEKTORX_MENU, WEKTORY_MENU);
		cputs("Wojciech Drewek s171838");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 1);
		cputs("ESC = wyjscie");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 2);
		cputs("strzalki = poruszanie");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 3);
		cputs("o = wygenerowanie losowej planszy");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 4);
		cputs("n = nowa gra");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 5);
		cputs("p = podpowiedz");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 6);
		cputs("r = zmiana rozmiaru");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 7);
		cputs("a = tryb aut. detekcji konca gry");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 8);
		cputs("k = spr. czy mozna ukonczyc gre");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 9);
		cputs("j = podswietlenie jednoznacznych pol");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 10);
		cputs("w = wpisanie cyfr w jednoznaczne pola");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 11);
		cputs("    o ile pola te sa podswietlone ");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 12);
		cputs("d =  wyswietlenie podp. do reguly 2");
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 13);
		_itoa(x, bufor, 10);
		_itoa(y, bufor1, 10);
		cputs("Pozycja kursora x=");
		cputs(bufor);
		cputs(" y=");
		cputs(bufor1);

		if (zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf(txt, "kod klawisza: 0x%02x", zn);
		gotoxy(WEKTORX_MENU, WEKTORY_MENU + 14);
		cputs(txt);
		if (flaga2 == PRAWDA)
		{
			gotoxy(WEKTORX_MENU, WEKTORY_MENU + 15);
			cputs("Tryb automatycznej detekcji konca gry wl.");
		}
		if (mozliwosc_ukonczenia2(tab, rozmiar) == FALSZ && flaga2 == PRAWDA){
			gotoxy(WEKTORX_MENU, WEKTORY_MENU + 16);
			cputs("Nie mozna ukonczyc gry");
		}
		else if(mozliwosc_ukonczenia2(tab, rozmiar) == PRAWDA && flaga2 == PRAWDA){
			gotoxy(WEKTORX_MENU, WEKTORY_MENU + 16);
			cputs("Mozna ukonczyc gre");
		}

		wypisz(tab, rozmiar);

		gotoxy(WEKTORX_BORDER + x, y + WEKTORY_BORDER);

		zero = 0;
		zn = getch();
		sprintf(podpowiedz_tab, "Miejsce na podpowiedz");
		sprintf(ktora_regula_tab, "Miejsce na podpowiedz");

		if (zn == 0)
		{
			czarne_tlo(tab, rozmiar);
			zero = 1;
			zn = getch();
			if (zn == 0x48 && y > 1)
				y--;
			else if (zn == 0x50 && y < rozmiar) y++;
			else if (zn == 0x4b && x > 1) x--;
			else if (zn == 0x4d && x < rozmiar) x++;
		}
		else if (zn == '1' && wszystkie_reguly(tab, y, x, zn, rozmiar) && tab[y - 1][x - 1].flaga == MODYFIKOWALNY)
		{
			tab[y - 1][x - 1].znak = '1';
			tab[y - 1][x - 1].kolor = RED;
			czarne_tlo(tab, rozmiar);
		}
		else if (zn == '0' && wszystkie_reguly(tab, y, x, zn, rozmiar) && tab[y - 1][x - 1].flaga == MODYFIKOWALNY)
		{
			tab[y - 1][x - 1].znak = '0';
			tab[y - 1][x - 1].kolor = RED;
			czarne_tlo(tab, rozmiar);
		}
		else if (zn == 'o' || zn == 'O')
		{
			losowa_plansza(tab, rozmiar);
			czarne_tlo(tab, rozmiar);
		}
		else if (zn == 'n' || zn == 'N')
		{
			rozmiar = 12;
			tab = inicjuj(rozmiar);
			x = rozmiar;
			y = rozmiar;
			wyczysc_plansze(tab, rozmiar);
			utworz_szablon_dom(tab, rozmiar);
			czarne_tlo(tab, rozmiar);
		}
		else if (zn == 'p' || zn == 'P')
		{
			podpowiedz(tab, x, y, rozmiar, podpowiedz_tab, ktora_regula_tab);
			czarne_tlo(tab, rozmiar);
		}
		else if (zn == 'r' || zn == 'R')
		{
			char zn1 = ' ', zn2 = ' ', liczba[2];
			zn1 = getch();
			zn2 = getch();
			sprintf(liczba, "%c%c", zn1, zn2);
			rozmiar = atoi(liczba);
			tab = inicjuj(rozmiar);
			zmiana_rozmiaru(tab, &rozmiar, &y, &x);
			czarne_tlo(tab, rozmiar);
		}
		else if (zn == 'k' || zn == 'K')
		{
			czarne_tlo(tab, rozmiar);
			mozliwosc_ukonczenia(tab, rozmiar);
		}
		else if (zn == 't' || zn == 'T')
		{
			wyczysc_plansze(tab, rozmiar);
		}
		else if (zn == 'j' || zn == 'J')
		{
			czarne_tlo(tab, rozmiar);
			jednoznaczne_pola(tab, rozmiar, TRYB_PODSWIETLENIE);
			flaga = PRAWDA;
		}
		else if ((zn == 'w' || zn == 'W') && flaga == PRAWDA)
		{
			jednoznaczne_pola(tab, rozmiar, TRYB_WPISANIE);
			flaga = FALSZ;
		}
		else if (zn == 'a' || zn == 'A')
		{
			flaga2 = (flaga2++) % 2;
		}
		else if (zn == 'd')
		{
			flaga3 = PRAWDA;
		}
		else
		{
			czarne_tlo(tab, rozmiar);
		}
	} while (zn != 27);

	usuwanie_pamieci(rozmiar, tab, kolumny_c_0, kolumny_c_1, wiersze_c_1, wiersze_c_0);

	return 0;
}



pole_t** inicjuj(int rozmiar)//inicjuje rozmiar planszy
{
	pole_t **tab;
	tab = new pole_t*[rozmiar];
	for (int i = 0; i<rozmiar; i++)
	{
		tab[i] = new pole_t[rozmiar];
	}
	return tab;
}

int* inicjuj_int(int rozmiar)
{
	int *tab;
	tab = new int[rozmiar];
	return tab;
}

char** inicjuj_char(int rozmiar)
{
	char **tab;
	tab = new char*[rozmiar];
	for (int i = 0; i<rozmiar; i++)
	{
		tab[i] = new char[2];
	}
	return tab;
}

void border(int rozmiar)//wypisuje ramke
{
	for (int i = 1; i <= rozmiar + 2; i++)
	{
		gotoxy(WEKTORX_BORDER, i + WEKTORY_BORDER - 1);
		for (int j = 1; j <= rozmiar + 2; j++)
		{
			if (i == 1 || i == rozmiar + 2 || j == 1 || j == rozmiar + 2)
				putch('#');
			else
				putch(' ');
		}
	}
}

void wypisz(pole_t **tab, int rozmiar)//wypisuje plansze
{
	for (int i = 0; i<rozmiar; i++)
	{
		gotoxy(WEKTORX_BORDER + 1, i + WEKTORY_BORDER + 1);
		for (int j = 0; j<rozmiar; j++)
		{
			textbackground(tab[i][j].kolortla);
			textcolor(tab[i][j].kolor);
			putch(tab[i][j].znak);
		}
	}
}

int regula_1(pole_t **tab, int y, int x, char zn, int rozmiar)
{
	if (y>1 && tab[y - 1][x].znak == zn && tab[y - 2][x].znak == zn)
		return FALSZ;
	if (y<rozmiar - 2 && tab[y + 1][x].znak == zn && tab[y + 2][x].znak == zn)
		return FALSZ;
	if (x>1 && tab[y][x - 1].znak == zn && tab[y][x - 2].znak == zn)
		return FALSZ;
	if (x<rozmiar - 2 && tab[y][x + 1].znak == zn && tab[y][x + 2].znak == zn)
		return FALSZ;
	if (y>0 && y<rozmiar - 1 && tab[y - 1][x].znak == zn && tab[y + 1][x].znak == zn)
		return FALSZ;
	if (x>0 && x<rozmiar - 1 && tab[y][x - 1].znak == zn && tab[y][x + 1].znak == zn)
		return FALSZ;
	return PRAWDA;

}

void wypelnij_0(int *tab, int rozmiar)
{
	for (int i = 0; i<rozmiar; i++)
		tab[i] = 0;
}
void wypelnij_spacjami(char *tab, int rozmiar)
{
	for (int i = 0; i<rozmiar; i++)
		tab[i] = ' ';

}

int regula_2(pole_t **tab, int y, int x, char zn, int rozmiar)
{
	int *kolumny = inicjuj_int(rozmiar); wypelnij_0(kolumny, rozmiar);
	int *wiersze = inicjuj_int(rozmiar); wypelnij_0(wiersze, rozmiar);

	for (int i = 0; i<rozmiar; i++)
	{
		for (int j = 0; j<rozmiar; j++)
		{
			if (tab[i][j].znak == zn)
			{
				kolumny[j]++;
				wiersze[i]++;
			}
		}
	}

	if (kolumny[x]<rozmiar / 2 && wiersze[y]<rozmiar / 2)
		return PRAWDA;
	else
		return FALSZ;
	delete[]kolumny;
	delete[]wiersze;
}

int regula_3(pole_t **tab, int y, int x, char zn, int rozmiar)
{
	int* kolumny = inicjuj_int(rozmiar); wypelnij_0(kolumny, rozmiar);
	int* wiersze = inicjuj_int(rozmiar); wypelnij_0(wiersze, rozmiar);

	for (int i = 0; i<rozmiar; i++) {
		for (int j = 0; j<rozmiar; j++) {
			if (tab[i][j].znak != '.') {
				kolumny[j]++;
				wiersze[i]++;
			}
		}
	}


	for (int i = 0; i<rozmiar; i++) {
		if (i != x && kolumny[i] == rozmiar) {
			for (int j = 0; j <= rozmiar; j++) {
				if (j <rozmiar && j != y && tab[j][i].znak != tab[j][x].znak)
					break;
				if (j == rozmiar && zn == tab[y][i].znak)
					return FALSZ;
			}
		}
		if (i != y && wiersze[i] == rozmiar) {
			for (int j = 0; j <= rozmiar; j++) {
				if (j <rozmiar && j != x && tab[i][j].znak != tab[y][j].znak)
					break;
				if (j == rozmiar && zn == tab[i][x].znak)
					return FALSZ;
			}
		}
	}
	return PRAWDA;

	delete[]kolumny;
	delete[]wiersze;
}

int wszystkie_reguly(pole_t **tab, int y, int x, char zn, int rozmiar)
{
	if (regula_1(tab, y - 1, x - 1, zn, rozmiar) && regula_2(tab, y - 1, x - 1, zn, rozmiar) && regula_3(tab, y - 1, x - 1, zn, rozmiar))
		return PRAWDA;
	else
		return FALSZ;
}

void utworz_szablon_dom(pole_t** tab, int rozmiar)//tworzy szablon domyslny
{
	FILE* pl;
	pl = fopen("plansza.txt", "r");
	for (int i = 0; i<rozmiar; i++) {
		for (int j = 0; j<rozmiar; j++) {
			tab[i][j].znak = fgetc(pl);
			if (tab[i][j].znak != '.')
			{
				tab[i][j].flaga = NIEMODYFIKOWALNY;
			}
		}
	}
	fclose(pl);
}

void utworz_szablon(pole_t** tab, int rozmiar)
{
	char nazwa_pliku[20];
	sprintf(nazwa_pliku, "plansza%dx%d.txt", rozmiar, rozmiar);
	FILE* pl;
	pl = fopen(nazwa_pliku, "r");
	for (int i = 0; i<rozmiar; i++) {
		for (int j = 0; j<rozmiar; j++) {
			tab[i][j].znak = fgetc(pl);
			if (tab[i][j].znak != '.')
			{
				tab[i][j].flaga = NIEMODYFIKOWALNY;
			}
		}
	}
	fclose(pl);
}

void losowa_plansza(pole_t **tab, int rozmiar)
{
	wyczysc_plansze(tab, rozmiar);
	int x, y, i = 0;
	double procent_1_pola = 100.0 / pow(rozmiar, 2), procent_wyp = 0, procent_rand;
	char zn;
	srand(time(NULL));
	procent_rand = rand() % 10 + 35;
	while (procent_wyp < procent_rand && i++ < pow(rozmiar, 2)) {
		x = rand() % rozmiar;
		y = rand() % rozmiar;
		zn = rand() % 2 + 48;

		if (wszystkie_reguly(tab, y + 1, x + 1, zn, rozmiar) && tab[y][x].flaga == MODYFIKOWALNY)
		{
			tab[y][x].znak = zn;
			tab[y][x].flaga = NIEMODYFIKOWALNY;
			procent_wyp += procent_1_pola;
			if (zepsucie_planszy(tab, rozmiar) == FALSZ)
			{
				tab[y][x].znak = '.';
				tab[y][x].flaga = MODYFIKOWALNY;
				procent_wyp -= procent_1_pola;
			}
		}

	}
}

int zepsucie_planszy(pole_t **tab, int rozmiar)//sprawdza czy wpisanie znaku nie posuje sytuacji gdzies na planszy
{
	for (int i = 0; i<rozmiar; i++) {
		for (int j = 0; j<rozmiar; j++) {
			if (tab[i][j].flaga == MODYFIKOWALNY && wszystkie_reguly(tab, i + 1, j + 1, '1', rozmiar) == FALSZ && wszystkie_reguly(tab, i + 1, j + 1, '0', rozmiar) == FALSZ)
				return FALSZ;
		}
	}
	return PRAWDA;
}

void wyczysc_plansze(pole_t **tab, int rozmiar)
{
	for (int i = 0; i<rozmiar; i++) {
		for (int j = 0; j<rozmiar; j++) {
			tab[i][j].znak = '.';
			tab[i][j].flaga = MODYFIKOWALNY;
			tab[i][j].kolor = WHITE;
			tab[i][j].kolortla = BLACK;
		}
	}

}

void podpowiedz(pole_t **tab, int x, int y, int rozmiar, char *podpowiedz_tab, char *ktora_regula_tab)
{
	char reg_1 = ' ', reg_2 = ' ', reg_3 = ' ', reg_1_bis = ' ', reg_2_bis = ' ', reg_3_bis = ' ';
	sprintf(podpowiedz_tab, "Miejsce na podpowiedz");
	sprintf(ktora_regula_tab, "Miejsce na podpowiedz");
	if (tab[y - 1][x - 1].flaga == NIEMODYFIKOWALNY)
		sprintf(podpowiedz_tab, "To pole jest niemodyfikowalne");
	else if (wszystkie_reguly(tab, y, x, '0', rozmiar) && wszystkie_reguly(tab, y, x, '1', rozmiar))
		sprintf(podpowiedz_tab, "W tym polu mozesz wpisac 0 i 1");
	else if (wszystkie_reguly(tab, y, x, '1', rozmiar))
	{
		sprintf(podpowiedz_tab, "W tym polu mozesz wpisac tylko 1");
		ktora_regula(tab, x, y, '0', rozmiar, &reg_1, &reg_2, &reg_3);
		sprintf(ktora_regula_tab, "Wpisanie 0 przeczyloby regulom %c %c %c", reg_1, reg_2, reg_3);
	}
	else if (wszystkie_reguly(tab, y, x, '0', rozmiar))
	{
		sprintf(podpowiedz_tab, "W tym polu mozesz wpisac tylko 0");
		ktora_regula(tab, x, y, '1', rozmiar, &reg_1, &reg_2, &reg_3);
		sprintf(ktora_regula_tab, "Wpisanie 1 przeczyloby regulom %c %c %c", reg_1, reg_2, reg_3);
	}
	else
	{
		sprintf(podpowiedz_tab, "Nic nie mozesz tu wpisac");
		ktora_regula(tab, x, y, '1', rozmiar, &reg_1, &reg_2, &reg_3);
		ktora_regula(tab, x, y, '0', rozmiar, &reg_1_bis, &reg_2_bis, &reg_3_bis);
		sprintf(ktora_regula_tab, "Wpisanie 1 przeczyloby regulom %c %c %c a 0 regulom %c %c %c", reg_1, reg_2, reg_3, reg_1_bis, reg_2_bis, reg_3_bis);
	}
}

void ktora_regula(pole_t **tab, int x, int y, char zn, int rozmiar, char *reg_1, char *reg_2, char *reg_3)// ktora regula blokuje wpisania cyfry
{
	if (regula_1(tab, y - 1, x - 1, zn, rozmiar) == FALSZ)
		*reg_1 = '1';
	if (regula_2(tab, y - 1, x - 1, zn, rozmiar) == FALSZ)
		*reg_2 = '2';
	if (regula_3(tab, y - 1, x - 1, zn, rozmiar) == FALSZ)
		*reg_3 = '3';
}

void zmiana_rozmiaru(pole_t **tab, int *rozmiar, int *y, int *x)
{
	if (*rozmiar == 10)
	{
		*x = *rozmiar;
		*y = *rozmiar;
		wyczysc_plansze(tab, *rozmiar);
		utworz_szablon(tab, *rozmiar);
	}
	else if (*rozmiar == 8)
	{
		*x = *rozmiar;
		*y = *rozmiar;
		wyczysc_plansze(tab, *rozmiar);
		utworz_szablon(tab, *rozmiar);
	}
	else if (*rozmiar == 6)
	{
		*x = *rozmiar;
		*y = *rozmiar;
		wyczysc_plansze(tab, *rozmiar);
		utworz_szablon(tab, *rozmiar);
	}
	else
	{
		*x = *rozmiar;
		*y = *rozmiar;
		wyczysc_plansze(tab, *rozmiar);
		losowa_plansza(tab, *rozmiar);
	}
}

void mozliwosc_ukonczenia(pole_t **tab, int rozmiar)
{
	for (int i = 0; i<rozmiar; i++)
	{
		for (int j = 0; j<rozmiar; j++)
		{
			if (tab[i][j].znak == '.' && wszystkie_reguly(tab, i + 1, j + 1, '1', rozmiar) == FALSZ && wszystkie_reguly(tab, i + 1, j + 1, '0', rozmiar) == FALSZ)
				tab[i][j].kolortla = GREEN;
		}
	}
}

char** podpowiedz_do_reguly_2(pole_t **tab, int rozmiar, char zn, int tryb)//zwraca tablice z zapisana iloscia cyfr w wierszu lub kolumnie
{
	int *kolumny = inicjuj_int(rozmiar); wypelnij_0(kolumny, rozmiar);
	int *wiersze = inicjuj_int(rozmiar); wypelnij_0(wiersze, rozmiar);
	char **wiersze_c = inicjuj_char(rozmiar);
	char **kolumny_c = inicjuj_char(rozmiar);

	for (int i = 0; i<rozmiar; i++)
	{
		for (int j = 0; j<rozmiar; j++)
		{
			if (tab[i][j].znak == zn)
			{
				kolumny[j]++;
				wiersze[i]++;
			}
		}
	}

	if (tryb == TRYB_KOLUMNY)
	{
		for (int i = 0; i<rozmiar; i++)
			_itoa(kolumny[i], kolumny_c[i], 10);
		return kolumny_c;
	}
	else
	{
		for (int i = 0; i<rozmiar; i++)
			_itoa(wiersze[i], wiersze_c[i], 10);
		return wiersze_c;
	}

	delete[]kolumny;
	delete[]wiersze;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]kolumny_c[i];
	}
	delete[]kolumny_c;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]wiersze_c[i];
	}
	delete[]wiersze_c;
}

void jednoznaczne_pola(pole_t **tab, int rozmiar, int tryb)// modyfikuje kolor tla jednoznacznych pol lub wpisuje tab cyfry (w zaleznosci od trybu)
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (wszystkie_reguly(tab, i + 1, j + 1, '0', rozmiar) == FALSZ && wszystkie_reguly(tab, i + 1, j + 1, '1', rozmiar) && tab[i][j].znak == '.')
			{
				if (tryb == TRYB_PODSWIETLENIE)
					tab[i][j].kolortla = MAGENTA;
				else if (tryb == TRYB_WPISANIE && (tab[i][j].kolortla == LIGHTGREEN || tab[i][j].kolortla == MAGENTA))
				{
					tab[i][j].kolor = RED;
					tab[i][j].znak = '1';
				}
			}
			else if (wszystkie_reguly(tab, i + 1, j + 1, '0', rozmiar) && wszystkie_reguly(tab, i + 1, j + 1, '1', rozmiar) == FALSZ && tab[i][j].znak == '.')
			{
				if (tryb == TRYB_PODSWIETLENIE)
					tab[i][j].kolortla = LIGHTGREEN;
				else if (tryb == TRYB_WPISANIE && (tab[i][j].kolortla == LIGHTGREEN || tab[i][j].kolortla == MAGENTA))
				{
					tab[i][j].kolor = RED;
					tab[i][j].znak = '0';
				}
			}
		}
	}
}

void czarne_tlo(pole_t **tab, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			tab[i][j].kolortla = BLACK;
		}
	}
}

int mozliwosc_ukonczenia2(pole_t **tab, int rozmiar)
{
	for (int i = 0; i<rozmiar; i++)
	{
		for (int j = 0; j<rozmiar; j++)
		{
			if (tab[i][j].znak == '.' && wszystkie_reguly(tab, i + 1, j + 1, '1', rozmiar) == FALSZ && wszystkie_reguly(tab, i + 1, j + 1, '0', rozmiar) == FALSZ)
				return FALSZ;
		}
	}
	return PRAWDA;
}

void usuwanie_pamieci(int rozmiar, pole_t **tab, char **kolumny_c_0, char **kolumny_c_1, char **wiersze_c_1, char **wiersze_c_0)
{
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]tab[i];
	}
	delete[]tab;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]kolumny_c_0[i];
	}
	delete[]kolumny_c_0;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]kolumny_c_1[i];
	}
	delete[]kolumny_c_1;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]wiersze_c_1[i];
	}
	delete[]wiersze_c_1;
	for (int i = 0; i < rozmiar; i++)
	{
		delete[]wiersze_c_0[i];
	}
	delete[]wiersze_c_0;
}