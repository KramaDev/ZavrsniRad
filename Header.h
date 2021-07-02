#ifndef head_h
#define head_h


#define MAX_GOD  2021
#define MIN_GOD  1941
#define MAX_KORISNICKO_IME 20
#define MAX_LOZINKA  20
#define NAZIV_DATOTEKE  "bazaPacijenata.bin"
#define MAX_IME_PACIJENTA 15
#define MAX_PREZIME 20
#define MAX_ADRESA_PACIJENTA 150
#define MAX_SIMPTOMI_PACIJENATA 200
#define VELICINA_MEM_PRIJAVA  sizeof(PODATCIzaPRIJAVU)



typedef struct datum
{
	int gggg;
	int mm;
	int dd;
} DATUM;


typedef struct prijava
{
	char korisnickoIme[MAX_KORISNICKO_IME];
	char lozinka[MAX_LOZINKA];
} PODATCIzaPRIJAVU;



typedef struct pacijent
{
	float mbo;
	char imePacijenta[MAX_IME_PACIJENTA];
	char prezime[MAX_PREZIME];
	char adresaPacijenta[MAX_ADRESA_PACIJENTA];
	char simptomiPacijenta[MAX_SIMPTOMI_PACIJENATA];
	DATUM datumRodjenja;
	unsigned int idPacijenta;
} PACIJENTiNFO;

void izbornik();
void defaultPrijava();
void prijava();
void promjenaPodZaPrijavu(void);
void brisanjePacijenta();
void poredajPacijentePoPrezimenu(int brojPacijenata);
void sortirajPodatke_vece_manje(PACIJENTiNFO* pacijenti, int n);
void sortirajPodatke_manje_vece(PACIJENTiNFO* pacijenti, int n);
int pregledSvihPacijenata();
int provjeraBrojaPacijenata();
void trazenjePacijenata();
void dodajPacijentaUbazu();

void nazivOdabranogIzbornika(const char* tekst);
void ulaznaPoruka();
int provjeraImena(const char* ime);
int provjeraAdrese(const char* adresa);
int provjeraSimptoma(const char* simptomi);
int provjeriDatum(DATUM* provjeraDatuma);


#endif // head_h
