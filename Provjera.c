#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"




//*************************************************************************************
//*************************************************************************************

void nazivOdabranogIzbornika(const char* tekst)
{
	system("cls");
	printf("\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t\t\xB2                                                          \xB2");
	printf("\n\t\t\t\t\xB2                 Baza podataka pacijenata                 \xB2");
	printf("\n\t\t\t\t\xB2                                                          \xB2");
	printf("\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t\n");
	printf("\t\t\t\t");
	printf(tekst);
	printf("\n\t\t\t****************************************************************************");
}

//*************************************************************************************
//*************************************************************************************

void ulaznaPoruka()
{
	nazivOdabranogIzbornika("Dobro dosli u bazu podataka");
	printf("\n\n\n\n\n");
	printf("\n\n\n\t\t\t Pritisnite tipku za pocetak rada.....");
	getch();
}

//*************************************************************************************
//*************************************************************************************

int provjeraImena(const char* ime)
{
	int tocnoIme = 1;
	int brojSlova = 0;
	int index = 0;
	brojSlova = strlen(ime);
	for (index = 0; index < brojSlova; ++index)
	{
		if (!(isalpha(ime[index])) && (ime[index] != '\n') && (ime[index] != ' '))  //isalpha() provjerava dali je znak slovo ako nije vraca 0
		{
			tocnoIme = 0;
			break;
		}
	}
	return tocnoIme;
}

//*************************************************************************************
//*************************************************************************************

int provjeraAdrese(const char* adresa)
{
	int tocnaAdresa = 1;
	int brojZnakova = 0;
	int index = 0;
	brojZnakova = strlen(adresa);

	if (brojZnakova > MAX_ADRESA_PACIJENTA)
	{
		tocnaAdresa = 0;

	}

	return tocnaAdresa;
}

//*************************************************************************************
//*************************************************************************************

int provjeraSimptoma(const char* simptomi)
{
	int tocniSimptomi = 1;
	int brojZnakova = 0;
	int index = 0;
	brojZnakova = strlen(simptomi);

	if (brojZnakova > MAX_SIMPTOMI_PACIJENATA)
	{
		tocniSimptomi = 0;

	}

	return tocniSimptomi;
}

//*************************************************************************************
//*************************************************************************************

int provjeriDatum(DATUM* provjeraDatuma)
{

	if (provjeraDatuma->gggg > MAX_GOD ||
		provjeraDatuma->gggg < MIN_GOD)
		return 0;
	if (provjeraDatuma->mm < 1 || provjeraDatuma->mm > 12)
		return 0;
	if (provjeraDatuma->dd < 1 || provjeraDatuma->dd > 31)
		return 0;

	//ogranicava unos broja dana na 30 za mjesece koji imaju samo 30 dana
	if (provjeraDatuma->mm == 4 || provjeraDatuma->mm == 6 ||
		provjeraDatuma->mm == 9 || provjeraDatuma->mm == 11)
		return (provjeraDatuma->dd <= 30);

	return 1;
}