/* kompilacja: 
        Sun C: cc -Xc test_obrazy_PC.c -lm
        GNU C: gcc -o test_obrazy_PC -pedantic -Wall test_obrazy_PC.c -lm*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>                                                            /*dodajemy bibliotekę matematycną ponieważ potrzebujemy wartości bezwzględnej i potęg*/

#define MAX 512       /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										                                                              *
 * \param[in]  plik_we uchwyt do pliku z obrazem w formacie PGM			                *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		              *
 * \param[out] wymx szerokosc obrazka						                                    *
 * \param[out] wymy wysokosc obrazka						                                    *
 * \param[out] szarosci liczba odcieni szarosci					                            *
 * \return     liczba wczytanych pikseli						                                *
 ************************************************************************************/

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }
  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  if(*wymx>MAX)                                           /*dodajemy dwa warunki informujące nas gdy wymiary obrazu są nieprawidłowe*/
  {
    printf("Blad: Niewłaściwe wymiary obrazu\n");
  }
  else if(*wymy>MAX)
  {
    printf("Blad: Niewłaściwe wymiary obrazu\n");
  }
  else if(*wymy>MAX && *wymx>MAX)
  {
    printf("Blad: Niewłaściwe wymiary obrazu\n");
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int zapisz(FILE *plik_wy,int obraz_pgm[][MAX],int wymx,int wymy, int szarosci)
{
  int i, j;
  fprintf(plik_wy,"P2\n");                                                              /*wpisujemy magiczne P2*/
  fprintf(plik_wy,"%d %d\n%d \n", wymx, wymy, szarosci);                                /*wpisujemy wymiary wierszy, kolumn oraz maksymalną szarość*/
  for(i=0;i<wymy;i++)
  {
    for(j=0;j<wymx;j++)
    {
      fprintf(plik_wy,"%d ", obraz_pgm[i][j]);                                          /*wpisujemy wartości tablic, spacja jest bardzo ważna, inaczej otrzymamy jedną długą liczbę*/
    }
    fprintf(plik_wy,"\n");                                                              /*po wypisaniu całego wiersza przechodzimy do nowego wiersza dla lepszej czytelności*/
  }
}
/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) 
{
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void negatyw(int obraz_pgm[][MAX],int wymx,int wymy, int szarosci)                      
{
  int i,j;
  for(i=0;i<wymy;i++)
  {
    for(j=0;j<wymx;j++)
    {
      obraz_pgm[i][j]=szarosci-obraz_pgm[i][j];                                         /*pętla wykonująca warunek negatywu podany w pdf w operacjach przetwarzania obrazów*/
    }
  }
}
void progowanie(float proc_p, int obraz_pgm[][MAX],int wymx,int wymy, int szarosci)     
{
  int i,j;
  int prog;                                                                             /*wprowadzamy dwie zmienne prog i proc_p, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=szarosci*proc_p/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  for(i=0;i<wymy;i++)
  {
    for(j=0;j<wymx;j++)
    {
      if(obraz_pgm[i][j]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
      {
        obraz_pgm[i][j]=0;
      }
      else
      {
        obraz_pgm[i][j]=szarosci;
      }
    }
  }
}
void korekcja_gamma(float gamma1, int obraz_pgm[][MAX],int wymx,int wymy, int szarosci)  
{
  int i,j;                                                                               /*dodajemy zmienną gamma1, oznacza ona wartość gammy podaną przez użytkownika*/
  for(i=0;i<wymy;i++)
  {
    for(j=0;j<wymx;j++)
    {
      obraz_pgm[i][j]=pow((float)obraz_pgm[i][j]/szarosci,1/gamma1)*szarosci;            /*obliczamy korekcję wg wzoru, musimy przypisać jednej zmiennej typ float aby funkcja działała poprawnie*/
    }                                                                                    /*zmieniamy typ obrazu_pgm lub szarosci*/
  } 
}
void konturowanie(int obraz_pgm[][MAX],int wymx,int wymy, int szarosci)
{
  int i,j;
  for(i=0;i<wymy;i++)
    {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
        if(i==wymy-1 && j==wymx-1)
        {
          obraz_pgm[i][j]=abs(obraz_pgm[0][j]-obraz_pgm[i][j])+abs(obraz_pgm[i][0]-obraz_pgm[i][j]);
        }
        else if(i==wymy-1)
        {
          obraz_pgm[i][j]=abs(obraz_pgm[0][j]-obraz_pgm[i][j])+abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]);
        }
        else if(j==wymx-1)
        {
          obraz_pgm[i][j]=abs(obraz_pgm[i+1][j]-obraz_pgm[i][j])+abs(obraz_pgm[i][0]-obraz_pgm[i][j]);
        }
        else
        {
        obraz_pgm[i][j]=abs(obraz_pgm[i+1][j]-obraz_pgm[i][j])+abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]);
        }
      }
    } 
}
void histogram(int obraz_pgm[][MAX],int wymx,int wymy, int szarosci)
{
  int i,j;
  int wartosc_MIN, wartosc_MAX;                                               /*dodajemy dwie zmienne wartosc_MIN oraz wartosc_MAX, odpowiadają one najciemniejszemu i najjaśniejszemu pikselowi obrazu*/
  wartosc_MAX=0;                                                              
  wartosc_MIN=szarosci;                                                                        
  for(i=0;i<wymy;i++)                                                         /*szukanie najjaśniejszego punktu*/
  {
    for(j=0;j<wymx;j++)
    {
      if(obraz_pgm[i][j]>wartosc_MAX)                                        
      {
        wartosc_MAX=obraz_pgm[i][j];
      }
      else
      {
      }
    }
  }
  for(i=0;i<wymy;i++)                                                       /*szukanie najciemniejszego punktu*/
  {
    for(j=0;j<wymx;j++)
    {
      if(obraz_pgm[i][j]<wartosc_MIN)
      {
        wartosc_MIN=obraz_pgm[i][j];
      }
      else
      {
      }
    }
  }  
  for(i=0;i<wymy;i++)                                                       /*rozciąganie histogramu wg wzoru*/
  {
    for(j=0;j<wymx;j++)
    {
      obraz_pgm[i][j]=(obraz_pgm[i][j]-wartosc_MIN)*MAX/(wartosc_MAX-wartosc_MIN);    
    }
  }  
}

int main() {
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni;
  float gamma1, procent;                                                  /*definiujemy zmienne, które dodaliśmy*/
  int wybor;
  int odczytano = 0;
  FILE *plik;
  /*
  pliki,  które powinny być zapisane na komputerze,  aby odczyt był możliwy to:
  Lena.pgm
  lena2.pgm
  piesel.jpg
  są dołączone w repozytorium
  */
  char nazwa[] = "Lena.pgm";
  char nazwaN[] = "Lena_negatyw_PC.pgm";
  char nazwaP20[] = "Lena_prog20_PC.pgm";
  char nazwaP40[] = "Lena_prog40_PC.pgm";
  char nazwaG1[] = "Lena_gamma1_PC.pgm";
  char nazwaG3[] = "Lena_gamma3_PC.pgm";
  char nazwaK[] = "Lena_kontur_PC.pgm";
  char nazwaH[] = "Lena_histogram_PC.pgm";
  char wymiar[] = "Lena2.pgm";
  char piesel[] = "piesel.jpg";

  /*wyswietlenie oryginalnego zdjecia dla porownania*/
  plik=fopen(nazwa,"r");
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  wyswietl(nazwa);

  /*negatyw*/
  plik=fopen(nazwa,"r");
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  negatyw(obraz, wymx,wymy, odcieni);
  plik=fopen(nazwaN, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaN);

  /*progowanie gdy procent równy 20*/
  plik=fopen(nazwa,"r");  
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  procent = 20;
  progowanie(procent, obraz, wymx,wymy, odcieni);
  plik=fopen(nazwaP20, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaP20);

  /*progowanie gdy procent równy 40*/
  plik=fopen(nazwa,"r");  
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  procent = 40;
  progowanie(procent, obraz, wymx,wymy, odcieni);
  plik=fopen(nazwaP40, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaP40);

  /*korekcja gamma gdy gamma1 równa 1*/
  plik=fopen(nazwa,"r");  
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  gamma1=1;
  korekcja_gamma(gamma1, obraz, wymx, wymy, odcieni);
  plik=fopen(nazwaG1, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaG1);

  /*korekcja gamma gdy gamma1 równa 3*/
  plik=fopen(nazwa,"r");  
  if (plik != NULL) {      
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  gamma1=3;
  korekcja_gamma(gamma1, obraz, wymx, wymy, odcieni);
  plik=fopen(nazwaG3, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaG3);

  /*konturowanie*/
  plik=fopen(nazwa,"r");  
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  konturowanie(obraz, wymx,wymy, odcieni);
  plik=fopen(nazwaK, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaK);

  /*histogram*/
  plik=fopen(nazwa,"r");  
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  histogram(obraz, wymx,wymy, odcieni);
  plik=fopen(nazwaH, "w");                                       
  zapisz(plik, obraz, wymx, wymy, odcieni);
  fclose(plik);
  wyswietl(nazwaH);

  /*plik jpg*/
  plik=fopen(piesel,"r");
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  wyswietl(piesel);

  /*zły wymiar*/
  plik=fopen(wymiar,"r");
  if (plik != NULL) {       
  odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  }
  fclose(plik);
  wyswietl(wymiar);

  return 0;
}
