#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Header.h"




void dodajPacijentaUbazu()
{
	PACIJENTiNFO dodajInformacijeUbazu = { 0 };
	FILE* fp = NULL;
	int status = 0;
	fp = fopen(NAZIV_DATOTEKE, "ab+");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena...\n");
		exit(1);
	}
	nazivOdabranogIzbornika("DODAJ NOVOG PACIJENTA");
	printf("\n\n\t\t\tUNESITE TRAZENE INFORMACIJE:");
	printf("\n\n");
	printf("\n\t\t\tPacijentov ID  = ");
	fflush(stdin);																				//sluzi za ciscenje ostataka u memoriji (buffera)
	scanf("%u", &dodajInformacijeUbazu.idPacijenta);
	char ocisti[5];																				//spremnik za nezeljene znakove koji su "propadali" u varijablu mbo
	fgets(ocisti, 1, stdin);

	printf("\n\t\t\tMBO pacijenta  = ");
	fflush(stdin);
	scanf("%f", &dodajInformacijeUbazu.mbo);
	fgets(ocisti, 4, stdin);

	do
	{
		printf("\n\t\t\tIme pacijenta  = ");
		fflush(stdin);
		fgets(dodajInformacijeUbazu.imePacijenta, MAX_IME_PACIJENTA, stdin);
		status = provjeraImena(dodajInformacijeUbazu.imePacijenta);
		if (status == 0)
		{
			printf("\n\t\t\tUnos sadrzava nedozvoljene znakove. Pokusajte ponovno.");
		}
	} while (status == 0);

	do
	{
		printf("\n\t\t\tPrezime pacijenta  = ");
		fflush(stdin);
		fgets(dodajInformacijeUbazu.prezime, MAX_PREZIME, stdin);
		status = provjeraImena(dodajInformacijeUbazu.prezime);
		if (status == 0)
		{
			printf("\n\t\t\tUnos sadrzava nedozvoljene znakove. Pokusajte ponovno.");
		}
	} while (status == 0);

	do
	{
		printf("\n\t\t\tAdresa pacijenta = ");
		fflush(stdin);
		fgets(dodajInformacijeUbazu.adresaPacijenta, MAX_ADRESA_PACIJENTA, stdin);
		status = provjeraAdrese(dodajInformacijeUbazu.adresaPacijenta);
		if (status == 0)
		{
			printf("\n\t\t\tUnos sadrzava nedozvoljene znakove. Pokusajte ponovno.");
		}
	} while (status == 0);

	do
	{
		printf("\n\t\t\tSimptomi pacijenta = ");
		fflush(stdin);
		fgets(dodajInformacijeUbazu.simptomiPacijenta, MAX_SIMPTOMI_PACIJENATA, stdin);
		status = provjeraSimptoma(dodajInformacijeUbazu.simptomiPacijenta);
		if (status == 0)
		{
			printf("\n\t\t\tUnos sadrzava nedozvoljene znakove. Pokusajte ponovno.");
		}
	} while (status == 0);

	do {
		printf("\n\t\t\tUnesite datum rodjenja u formatu (dd.mm.gggg): ");
		scanf("%d.%d.%d", &dodajInformacijeUbazu.datumRodjenja.dd, &dodajInformacijeUbazu.datumRodjenja.mm, &dodajInformacijeUbazu.datumRodjenja.gggg);
		status = provjeriDatum(&dodajInformacijeUbazu.datumRodjenja);
	} while (status == 0);

	fwrite(&dodajInformacijeUbazu, sizeof(dodajInformacijeUbazu), 1, fp);        //pisanje u datoteku (zapisivanje jedne strukture)
	fclose(fp);
}

//*************************************************************************************
//*************************************************************************************

void trazenjePacijenata()
{
	int pronadeno = 0;
	float mboPacijenta = 0;
	PACIJENTiNFO citanjeTrazenogPacijenta = { 0 };
	FILE* fp = NULL;
	fp = fopen(NAZIV_DATOTEKE, "rb");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka nije otvorena!\n");
		exit(1);
	}
	nazivOdabranogIzbornika("PRETRAGA PACIJENATA");

	if (fseek(fp, VELICINA_MEM_PRIJAVA, SEEK_SET) != 0)            //fseek sluzi za postavljanje pozicije u bin datoteci (u ovom slucaju se postavlja na mjesto nakon velicine memorije strukture podataka za prijavu)
	{
		fclose(fp);
		printf("\n\t\t\tGreska prilikom otvaranja datoteke!\n");
		exit(1);
	}
	printf("\n\n\t\t\tUnesite ID trazenog pacijenta:");
	fflush(stdin);
	scanf("%f", &mboPacijenta);
	while (fread(&citanjeTrazenogPacijenta, sizeof(citanjeTrazenogPacijenta), 1, fp))  //izvrsava se citanje za odabrani id pacijenta
	{
		if (citanjeTrazenogPacijenta.mbo == mboPacijenta)
		{
			pronadeno = 1;
			break;
		}
	}
	if (pronadeno)
	{
		printf("\n\t\t\tPacijentov ID = %d\n", citanjeTrazenogPacijenta.idPacijenta);
		printf("\n\t\t\tIme pacijenta = %s", citanjeTrazenogPacijenta.imePacijenta);
		printf("\n\t\t\tPrezime pacijenta = %s", citanjeTrazenogPacijenta.prezime);
		printf("\t\t\tSimptomi pacijenta= %s\n", citanjeTrazenogPacijenta.simptomiPacijenta);
		printf("\t\t\tMBO = %.0f", citanjeTrazenogPacijenta.mbo);
		printf("\n\t\t\tAdresa pacijenta = %s", citanjeTrazenogPacijenta.adresaPacijenta);
		printf("\t\t\tDatum rodjenja(dd.mm.gggg) =  (%d.%d.%d)", citanjeTrazenogPacijenta.datumRodjenja.dd,
			citanjeTrazenogPacijenta.datumRodjenja.mm, citanjeTrazenogPacijenta.datumRodjenja.gggg);
	}
	else
	{
		printf("\n\t\t\tNije pronadeno!");
	}
	fclose(fp);
	printf("\n\n\n\t\t\tPritisnite tipku za povratak u izbornik...");
	getchar();
}


//*************************************************************************************
//*************************************************************************************
int provjeraBrojaPacijenata()
{
	PACIJENTiNFO pacijentiCitanje = { 0 };
	FILE* fp = NULL;
	int brojPacijenata = 0;
	fp = fopen(NAZIV_DATOTEKE, "rb");
	if (fp == NULL)
	{
		printf("\n\t\t\tNije moguce otvoriti datoteku!");
		exit(1);
	}
	if (fseek(fp, VELICINA_MEM_PRIJAVA, SEEK_SET) != 0)
	{
		fclose(fp);

		exit(1);
	}
	rewind(fp);                            //sluzi za vracanje pozicije na pocetak datoteke
	fseek(fp, VELICINA_MEM_PRIJAVA, SEEK_SET);
	while (fread(&pacijentiCitanje, sizeof(PACIJENTiNFO), 1, fp))
	{
		brojPacijenata++;
	}
	fclose(fp);


	return brojPacijenata;
}

//*************************************************************************************
//*************************************************************************************

int pregledSvihPacijenata()
{
	int pronadeno = 0;
	unsigned int brojPacijenata = 0;
	PACIJENTiNFO pacijentiCitanje = { 0 };
	FILE* fp = NULL;
	nazivOdabranogIzbornika("PREGLED SVIH PACIJENATA");
	fp = fopen(NAZIV_DATOTEKE, "rb");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena!\n");
		exit(1);
	}
	if (fseek(fp, VELICINA_MEM_PRIJAVA, SEEK_SET) != 0)  //zato sto fseek() vraca 0 ako je pomak bio uspijesan
	{
		fclose(fp);
		printf("Greska u citanju!\n");
		exit(1);
	}

	while (fread(&pacijentiCitanje, sizeof(pacijentiCitanje), 1, fp))  //vraca integral vrstu podatka dok je moguce citati iz datoteke, odnonsno dok ne dodje do kraja
	{
		printf("\n\n\t\t\tPacijentov ID = %u\n", pacijentiCitanje.idPacijenta);
		printf("\t\t\tIme pacijenta = %s", pacijentiCitanje.imePacijenta);
		printf("\t\t\tPrezime pacijenta = %s", pacijentiCitanje.prezime);
		printf("\t\t\tSimptomi pacijenta= %s", pacijentiCitanje.simptomiPacijenta);
		printf("\t\t\tMBO = %.0f", pacijentiCitanje.mbo);
		printf("\n\t\t\tAdresa pacijenta = %s", pacijentiCitanje.adresaPacijenta);
		printf("\t\t\tDatum rodjenja pacijenta(dd.mm.gggg) =  (%d.%d.%d)\n\n", pacijentiCitanje.datumRodjenja.dd,
			pacijentiCitanje.datumRodjenja.mm, pacijentiCitanje.datumRodjenja.gggg);
		pronadeno = 1;
		brojPacijenata++;
	}
	printf("\n\t\t\tBroj pacijenata = %d\n\n", brojPacijenata);

	if (pronadeno == 0)
	{
		printf("\n\t\t\tNema zapisa!");
	}
	printf("\n\n\t\t\tPritisnite tipku za povratak u izbornik...");
	fflush(stdin);
	fclose(fp);

}

//*************************************************************************************
//*************************************************************************************



void sortirajPodatke_manje_vece(PACIJENTiNFO* pacijenti, int n)
{

	PACIJENTiNFO temp;              //privremena struktura koja sluzi kako bi se mogao promijeniti indeks dvije strukture u polju
	int i = 0;
	int j = 0;

	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			if (pacijenti[j].prezime[0] == pacijenti[j + 1].prezime[0]) {

				if (pacijenti[j].prezime[1] > pacijenti[j + 1].prezime[1]) {

					temp = pacijenti[j];
					pacijenti[j] = pacijenti[j + 1];
					pacijenti[j + 1] = temp;

				}

			}
			else if (pacijenti[j].prezime[0] > pacijenti[j + 1].prezime[0])
			{
				temp = pacijenti[j];
				pacijenti[j] = pacijenti[j + 1];
				pacijenti[j + 1] = temp;
			}
		}
	}
}

//*************************************************************************************
//*************************************************************************************

void sortirajPodatke_vece_manje(PACIJENTiNFO* pacijenti, int n)
{

	PACIJENTiNFO temp;
	int i = 0;
	int j = 0;

	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			if (pacijenti[j].prezime[0] == pacijenti[j + 1].prezime[0]) {

				if (pacijenti[j].prezime[1] < pacijenti[j + 1].prezime[1]) {

					temp = pacijenti[j];
					pacijenti[j] = pacijenti[j + 1];
					pacijenti[j + 1] = temp;

				}

			}
			else if (pacijenti[j].prezime[0] < pacijenti[j + 1].prezime[0])
			{
				temp = pacijenti[j];
				pacijenti[j] = pacijenti[j + 1];
				pacijenti[j + 1] = temp;
			}
		}
	}
}
//*************************************************************************************
//*************************************************************************************

void poredajPacijentePoPrezimenu(int brojPacijenata)
{
	nazivOdabranogIzbornika("LISTA PACIJENATA PO IMENU");
	FILE* fp = NULL;
	PACIJENTiNFO* poredajPacijente = NULL;
	poredajPacijente = (PACIJENTiNFO*)calloc((int)brojPacijenata, sizeof(PACIJENTiNFO));
	int izbor = 0;
	if (poredajPacijente == NULL)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
	fp = fopen(NAZIV_DATOTEKE, "rb");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena!\n");
		exit(EXIT_FAILURE);
	}

	else {
		fseek(fp, VELICINA_MEM_PRIJAVA, SEEK_SET);
		fread(poredajPacijente, sizeof(PACIJENTiNFO), brojPacijenata, fp);
	}
	if (brojPacijenata != 0) {
		printf("\n\n\n\n\t\t\tOdaberite opciju za sortiranje:");
		printf("\n\t\t\t****************************************************************************");

		printf("\n\t\t\t1.Od Z do A po prezimenu");
		printf("\n\t\t\t2.Od A do Z po prezimenu");
		printf("\n\t\t\t****************************************************************************");
		do {
			printf("\n\n\t\t\tUnesite broj ispred zeljene opcije:");
			scanf("%d", &izbor);
		} while (izbor < 1 || izbor>2);

		if (izbor == 1)
		{
			sortirajPodatke_vece_manje(poredajPacijente, brojPacijenata);
		}
		else if (izbor == 2)
		{
			sortirajPodatke_manje_vece(poredajPacijente, brojPacijenata);
		}

		printf("\n\n\n\t\t\tBroj pacijenata: %d", brojPacijenata);
		for (int i = 0; i < brojPacijenata; i++)
		{
			printf("\n\n\t\tPacijentov ID = %u\n", (poredajPacijente + i)->idPacijenta);
			printf("\t\t\tIme pacijenta = %s", (poredajPacijente + i)->imePacijenta);
			printf("\t\t\tPrezime pacijenta = %s", (poredajPacijente + i)->prezime);
			printf("\t\t\tSimptomi pacijenta= %s", (poredajPacijente + i)->simptomiPacijenta);
			printf("\t\t\tMBO = %.0f", (poredajPacijente + i)->mbo);
			printf("\t\t\tAdresa pacijenta = %s", (poredajPacijente + i)->adresaPacijenta);
			printf("\t\t\tDatum rodjenja pacijenta(dd.mm.gggg) =  (%d.%d.%d)\n\n", (poredajPacijente + i)->datumRodjenja.dd,
				(poredajPacijente + i)->datumRodjenja.mm, (poredajPacijente + i)->datumRodjenja.gggg);
		}
	}
	else if (brojPacijenata == 0)
	{
		printf("\n\n\t\t\tNema zapisa!");
	}
	free(poredajPacijente);
	fclose(fp);

}



//*************************************************************************************
//*************************************************************************************

void brisanjePacijenta()
{

	int pronadeno = 0;
	int idZaBrisanje = 0;
	PODATCIzaPRIJAVU datPrijava = { 0 };
	PACIJENTiNFO dodavanjePacijentaUbazu = { 0 };
	FILE* fp = NULL;
	FILE* privremenaDat = NULL;
	nazivOdabranogIzbornika("BRISANJE PACIJENATA");
	fp = fopen(NAZIV_DATOTEKE, "rb");
	if (fp == NULL)
	{
		printf("Datoteka nije pronadjena...\n");
		exit(1);
	}
	privremenaDat = fopen("privremenaDat.bin", "wb");
	if (privremenaDat == NULL)
	{
		fclose(fp);
		printf("Datoteka nije pronadena...\n");
		exit(1);
	}
	fread(&datPrijava, VELICINA_MEM_PRIJAVA, 1, fp);
	fwrite(&datPrijava, VELICINA_MEM_PRIJAVA, 1, privremenaDat);   //prepisuje podtke za prijavu u novu, privremenu datoteku
	printf("\n\t\t\tUnesite ID pacijenta kojeg zelite obrisati: ");
	scanf("%d", &idZaBrisanje);
	while (fread(&dodavanjePacijentaUbazu, sizeof(dodavanjePacijentaUbazu), 1, fp))  //cita podtake svih zaposlenika iz datoteke
	{
		if (dodavanjePacijentaUbazu.idPacijenta != idZaBrisanje)  // Ako ako id trazenog pacijenta za brisanje nije jednak trenutnom id pacijenta on ce se prepisati u novu datoteku
		{
			fwrite(&dodavanjePacijentaUbazu, sizeof(dodavanjePacijentaUbazu), 1, privremenaDat);
		}
		else
		{
			pronadeno = 1;
		}
	}

	fclose(fp);
	fclose(privremenaDat);

	remove(NAZIV_DATOTEKE); //uklanjanje stare datoteke
	rename("privremenaDat.bin", NAZIV_DATOTEKE); //mijenjanje imena privremene dat u dat koja se koristi u ostatku programa
	(pronadeno) ? printf("\n\t\t\tUspijesno obrisano.....") : printf("\n\t\t\Pacijent nije pronaden...");

}

//*************************************************************************************
//*************************************************************************************

void promjenaPodZaPrijavu(void)
{
	PODATCIzaPRIJAVU datPrijava = { 0 };
	FILE* fp = NULL;
	unsigned char korIme[MAX_KORISNICKO_IME] = { 0 };
	unsigned char lozinka[MAX_LOZINKA] = { 0 };
	unsigned char ocisti[3] = { 0 };                        //Sluzi za ciscenje buffera (zbog nepoznatog razloga enter \n je propadao u korisnicko ime)
	nazivOdabranogIzbornika("Promjena podataka za prijavu");
	fp = fopen(NAZIV_DATOTEKE, "rb+");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena...\n");
		exit(1);
	}
	fread(&datPrijava, VELICINA_MEM_PRIJAVA, 1, fp);
	if (fseek(fp, 0, SEEK_SET) != 0)  //postavljanje pozicije na pocetak datoteke, ako nije moguce dat ce se zatvoriti
	{
		fclose(fp);
		printf("\n\t\t\tGreska prilkom dohvacanja podataka!\n");
		exit(1);
	}
	fgets(ocisti, 3, stdin);
	printf("\n\n\t\t\tNovo korisnicko ime:");
	fflush(stdin);
	fgets(korIme, MAX_KORISNICKO_IME, stdin);
	printf("\n\n\t\t\tNova lozinka:");
	fflush(stdin);
	fgets(lozinka, MAX_LOZINKA, stdin);
	strncpy(datPrijava.korisnickoIme, korIme, sizeof(korIme));
	strncpy(datPrijava.lozinka, lozinka, sizeof(lozinka));
	fwrite(&datPrijava, VELICINA_MEM_PRIJAVA, 1, fp);
	fclose(fp);
	printf("\n\t\t\tPodatci uspijesno promijenjeni!\n");
	fflush(stdin);
	getchar();
	fclose(fp);

}

//*************************************************************************************
//*************************************************************************************

void prijava()
{
	unsigned char korisnickoIme[MAX_KORISNICKO_IME] = { 0 };
	unsigned char lozinka[MAX_LOZINKA] = { 0 };
	int L = 0;
	PODATCIzaPRIJAVU datPrijava = { 0 };
	FILE* fp = NULL;
	nazivOdabranogIzbornika("PRIJAVI SE!");
	fp = fopen(NAZIV_DATOTEKE, "rb");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena...\n");
		exit(1);
	}
	fread(&datPrijava, VELICINA_MEM_PRIJAVA, 1, fp);
	fclose(fp);
	do
	{
		printf("\n\n\n\t\t\t\tKorisnicko ime:");
		fgets(korisnickoIme, MAX_KORISNICKO_IME, stdin);
		printf("\n\t\t\t\tLozinka:");
		fgets(lozinka, MAX_LOZINKA, stdin);
		if ((!strcmp(korisnickoIme, datPrijava.korisnickoIme)) && (!strcmp(lozinka, datPrijava.lozinka))) //usporedjuje unesene podatke s podatcima u memoriji, strcmp vraca nulu ako su stringovi jendaki
		{
			izbornik();
		}

		else
		{
			printf("\t\t\t\tNeuspjela prijava....Pokusajte ponovno!\n\n");
			L++;
		}
	} while (L <= 3);
	if (L > 3)                          //ako su podatci netocni tri puta za redom program se zatvara
	{
		nazivOdabranogIzbornika("Neuspijela prijava");
		printf("\t\t\t\tKorisnik nije pronaden.");
		getch();
		system("cls");
	}
	fclose(fp);
}

//*************************************************************************************
//*************************************************************************************



void defaultPrijava()        // podatci za prijavu koji sluze pri prvom pokretanju programa ili dok se ne postave novi
{

	const char defaultKorIme[] = "admin\n";
	const char defaultLozinka[] = "password\n";
	PODATCIzaPRIJAVU datPrijava = { 0 };
	FILE* fp = fopen(NAZIV_DATOTEKE, "rb");
	int status = 0;
	if (fp != NULL)
	{
		status = 1;

	}
	if (!status)
	{

		fp = fopen(NAZIV_DATOTEKE, "wb");
		if (fp != NULL)                           //ako se datoteka otvara prvi put spremaju se default podatci
		{

			strncpy(datPrijava.lozinka, defaultLozinka, sizeof(defaultLozinka));
			strncpy(datPrijava.korisnickoIme, defaultKorIme, sizeof(defaultKorIme));
			fwrite(&datPrijava, VELICINA_MEM_PRIJAVA, 1, fp);
			fclose(fp);
		}
	}
	fclose(fp);

}

//*************************************************************************************
//*************************************************************************************

void izbornik()
{
	int brojPacijenata;
	int izbor = 0;
	do
	{
		nazivOdabranogIzbornika("IZBORNIK");
		printf("\n\n\n\t\t\t1.Dodavanje pacijenta");
		printf("\n\t\t\t2.Pretraga pacijenata");
		printf("\n\t\t\t3.Pregled svih pacijenata");
		printf("\n\t\t\t4.Brisanje pacijenata");
		printf("\n\t\t\t5.Poredaj pacijente po prezimenu");
		printf("\n\t\t\t6.Promjena podataka za prijavu");
		printf("\n\t\t\t0.Exit");
		printf("\n\n\n\t\t\tUnesite broj ispred zeljene opcije => ");
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			dodajPacijentaUbazu();

			break;
		case 2:
			trazenjePacijenata();
			getch();

			break;
		case 3:
			pregledSvihPacijenata(provjeraBrojaPacijenata);
			getch();

			break;
		case 4:
			brisanjePacijenta();
			getch();

			break;
		case 5:
			brojPacijenata = provjeraBrojaPacijenata();
			poredajPacijentePoPrezimenu(brojPacijenata);
			getch();


			break;
		case 6:
			fflush(stdin);
			promjenaPodZaPrijavu();
			getch();
			break;

		case 0:
			printf("\n\n\n\t\t\t\tIzlazak iz programa!!\n\n\n\n\n");
			getch();

			exit(1);
			break;
		default:
			printf("\n\n\n\t\t\tUnos nije prepoznat...Pokusaj ponovno!");
			getch();
		}
	} while (izbor != 0);
}

//*************************************************************************************
//*************************************************************************************