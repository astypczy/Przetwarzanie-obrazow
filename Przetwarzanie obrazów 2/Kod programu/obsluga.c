#include"obsluga.h"
#include"struktura.h"
int czytaj(FILE *plik_we,Obraz *Obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j,k;
  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }
  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2' && buf[1]!='3') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    fprintf(stderr,"Blad: To nie jest plik PPM\n");
    return(0);
  }
  else
  {
    Obraz->magiczna_liczba=buf[1];
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
  if (fscanf(plik_we,"%d %d %d",&Obraz->wymx,&Obraz->wymy,&Obraz->szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  if(Obraz->magiczna_liczba=='2')
  {
    Obraz->obraz_pgm=malloc(Obraz->wymy*sizeof(int*));
    for(i=0; i<Obraz->wymy; i++)
    {
      Obraz->obraz_pgm[i]=malloc(Obraz->wymx*sizeof(int));
    }
    for (i=0;i<Obraz->wymy;i++)
    {
      for (j=0;j<Obraz->wymx;j++)
      {
        if (fscanf(plik_we,"%d",&(Obraz->obraz_pgm[i][j]))!=1)
        {
          fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
      }
    }
  }
  else if(Obraz->magiczna_liczba=='3')
  {
    Obraz->obraz_ppm=malloc(Obraz->wymy*sizeof(int**));
    for(i=0; i<Obraz->wymy; i++)
    {
      Obraz->obraz_ppm[i]=malloc(Obraz->wymx*sizeof(int*));
       for(j=0; j<Obraz->wymx; j++)
       {
         Obraz->obraz_ppm[i][j]=malloc(3*sizeof(int));
       }
    }
    for (i=0;i<Obraz->wymy;i++)
    {
      for (j=0;j<Obraz->wymx;j++)
      {
        for(k=0; k<3; k++)
        {
          if (fscanf(plik_we,"%d",&(Obraz->obraz_ppm[i][j][k]))!=1)
          {
            fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
            return(0);
          }
        }
      }
    }
  }
    return Obraz->wymx * Obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int zapisz(FILE *plik_wy,Obraz *Obraz)
{
  int i, j,k;
  if(Obraz->magiczna_liczba=='2')
  {
    fprintf(plik_wy,"P2\n");                                                              /*wpisujemy magiczne P2*/
    fprintf(plik_wy,"%d %d\n%d \n", Obraz->wymx, Obraz->wymy, Obraz->szarosci);                                /*wpisujemy wymiary wierszy, kolumn oraz maksymalną szarość*/
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        fprintf(plik_wy,"%d ", Obraz->obraz_pgm[i][j]);                                          /*wpisujemy wartości tablic, spacja jest bardzo ważna, inaczej otrzymamy jedną długą liczbę*/
      }
      fprintf(plik_wy,"\n");                                                              /*po wypisaniu całego wiersza przechodzimy do nowego wiersza dla lepszej czytelności*/
    }
  }
  else if(Obraz->magiczna_liczba=='3')
  {
    fprintf(plik_wy,"P3\n");                                                              /*wpisujemy magiczne P2*/
    fprintf(plik_wy,"%d %d\n%d \n", Obraz->wymx, Obraz->wymy, Obraz->szarosci);                                /*wpisujemy wymiary wierszy, kolumn oraz maksymalną szarość*/
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        for(k=0; k<3; k++)
        {
          fprintf(plik_wy,"%d ", Obraz->obraz_ppm[i][j][k]);                                          /*wpisujemy wartości tablic, spacja jest bardzo ważna, inaczej otrzymamy jedną długą liczbę*/
        }
      }
      fprintf(plik_wy,"\n");                                                              /*po wypisaniu całego wiersza przechodzimy do nowego wiersza dla lepszej czytelności*/
    }
  }
}

void wyswietl(char *n_pliku) 
{
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}


