/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2020 KCiR  */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/

#include "przetwarzanie.h"
#include "obsluga.h"
#define W_OK 0                /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1 /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY -2
#define B_BRAKWARTOSCI -3
#define B_BRAKPLIKU -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct
{
  FILE *plik_we, *plik_wy;                                                                                                                                                                       /* uchwyty do pliku wej. i wyj. */
  int negatyw, progowanie, korekcja_gamma, histogram, progowanie_czerni, progowanie_bieli, zamiana_poziomow, roz_pionowe1, roz_poziome1, roz_pionowe2, roz_poziome2, konturowanie, zmiana_koloru, wyswietl; /* opcje */
  int w_progu;                                                                                                                                                                                   /* wartosc progu dla opcji progowanie */
  int w_progu_c;
  int w_progu_b;
  char w_kolor;
  float w_czerni;
  float w_bieli;
  float w_gamma;
  char *nazwa_pliku_we, *nazwa_pliku_wy;
} t_opcje;

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(t_opcje *wybor)
{
  wybor->plik_we = NULL;
  wybor->plik_wy = NULL;
  wybor->negatyw = 0;
  wybor->konturowanie = 0;
  wybor->progowanie = 0;
  wybor->wyswietl = 0;
  wybor->korekcja_gamma = 0;
  wybor->histogram = 0;
  wybor->progowanie_czerni = 0;
  wybor->progowanie_bieli = 0;
  wybor->zamiana_poziomow = 0;
  wybor->roz_pionowe1 = 0;
  wybor->roz_poziome1 = 0;
  wybor->roz_pionowe2 = 0;
  wybor->roz_poziome2 = 0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola dla opcji, ktore  */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne            */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor)
{
  int i, prog;
  int gamma1;
  float bialy, czarny;
  char kolor;

  wyzeruj_opcje(wybor);
  wybor->plik_wy = stdout; /* na wypadek gdy nie podano opcji "-o" */
  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-') /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1])
    {
    case 'i':
    { /* opcja z nazwa pliku wejsciowego */
      if (++i < argc)
      { /* wczytujemy kolejny argument jako nazwe pliku */
        wybor->nazwa_pliku_we = argv[i];
        if (strcmp(wybor->nazwa_pliku_we, "-") == 0) /* gdy nazwa jest "-"        */
          wybor->plik_we = stdin;             /* ustwiamy wejscie na stdin */
        else                                  /* otwieramy wskazany plik   */
          wybor->plik_we = fopen(wybor->nazwa_pliku_we, "r");
      }
      else
        return B_BRAKNAZWY; /* blad: brak nazwy pliku */
      break;
    }
    case 'o':
    { /* opcja z nazwa pliku wyjsciowego */
      if (++i < argc)
      { /* wczytujemy kolejny argument jako nazwe pliku */
        wybor->nazwa_pliku_wy = argv[i];
        if (strcmp(wybor->nazwa_pliku_wy, "-") == 0) /* gdy nazwa jest "-"         */
          wybor->plik_wy = stdout;            /* ustwiamy wyjscie na stdout */
        else                                  /* otwieramy wskazany plik    */
          wybor->plik_wy = fopen(wybor->nazwa_pliku_wy, "w");
      }
      else
        return B_BRAKNAZWY; /* blad: brak nazwy pliku */
      break;
    }
    case 'm':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako kolor */
        if (sscanf(argv[i], "%c", &kolor) == 1)
        {
          wybor->w_kolor = kolor;
        }
        else
        {
          return B_BRAKWARTOSCI;
        } /* blad: niepoprawna wartosc koloru */
      }
      else
      {
        return B_BRAKWARTOSCI;
      } /* blad: brak wartosci koloru */
      break;
    }
    case 'p':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu */
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          if (prog >= 0 && prog <= 100)
          {
            wybor->progowanie = 1;
            wybor->w_progu = prog;
          }
          else
          {
            printf("Błędny procent!!!");
          }
        }
        else
        {
          return B_BRAKWARTOSCI;
        } /* blad: niepoprawna wartosc progu */
      }
      else
      {
        return B_BRAKWARTOSCI;
      } /* blad: brak wartosci progu */
      break;
    }
    case 'c':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu czaerni*/
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          if (prog >= 0 && prog <= 100)
          {
            wybor->progowanie_czerni = 1;
            wybor->w_progu_c = prog;
          }
          else
          {
            printf("Błędny procent!!!\n");
          }
        }
        else
        {
          return B_BRAKWARTOSCI;
        } /* blad: niepoprawna wartosc progu czerni*/
      }
      else
      {
        return B_BRAKWARTOSCI;
      } /* blad: brak wartosci progu czerni*/
      break;
    }
    case 'b':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu bieli*/
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          if (prog >= 0 && prog <= 100)
          {
            wybor->progowanie_bieli = 1;
            wybor->w_progu_b = prog;
          }
          else
          {
            printf("Błędny procent!!!\n");
          }
        }
        else
        {
          return B_BRAKWARTOSCI;
        } /* blad: niepoprawna wartosc progu bieli */
      }
      else
      {
        return B_BRAKWARTOSCI;
      } /* blad: brak wartosci progu bieli */
      break;
    }
    case 'g':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc gammy */
        if (sscanf(argv[i], "%d", &gamma1) == 1)
        {
          if (gamma1 > 0)
          {
            wybor->korekcja_gamma = 1;
            wybor->w_gamma = gamma1;
          }
          else
          {
            printf("Błędna gamma!!!");
          }
        }
        else
        {
          return B_BRAKWARTOSCI;
        } /* blad: niepoprawna wartosc gammy */
      }
      else
      {
        return B_BRAKWARTOSCI;
      } /* blad: brak wartosci gammy */
      break;
    }
    case 'z':
    { /*wykonujemy zamiane poziomow*/
      if (++i < argc)
      { /* wczytujemy argument jako wartosc czerni */
        if (sscanf(argv[i], "%f ", &czarny) == 1)
        {
          if (czarny >= 0 && czarny <= 100)
          {
            if (++i < argc)
            { /* wczytujemy argument jako wartosc bieli */
              if (sscanf(argv[i], "%f ", &bialy) == 1)
              {
                if (bialy >= 0 && bialy <= 100)
                {
                  wybor->zamiana_poziomow = 1;
                  wybor->w_czerni = czarny;
                  wybor->w_bieli = bialy;
                }
                else
                {
                  printf("Błędny procent bieli!!!\n");
                }
              }
              else
              {
                return B_BRAKWARTOSCI;
              } /* blad: niepoprawna wartosc bieli */
            }
          }
          else
          {
            printf("Błędny procent czerni!!!\n");
          }
        }
        else
        {
          return B_BRAKWARTOSCI;
        } /* blad: niepoprawna wartosc czerni */
      }
      else
      {
        return B_BRAKWARTOSCI;
      } /* blad: brak wartosci progu */
      break;
    }
    case 'n':
    { /* mamy wykonac negatyw */
      wybor->negatyw = 1;
      break;
    }
    case 'x':
    { /* mamy wykonac rozmywanie poziome o r=1 */
      wybor->roz_poziome1 = 1;
      break;
    }
    case 'X':
    { /* mamy wykonac rozmywanie poziome o r=2 */
      wybor->roz_poziome2 = 1;
      break;
    }
    case 'y':
    { /* mamy wykonac rozmywanie pionowe o r=1 */
      wybor->roz_pionowe1 = 1;
      break;
    }
    case 'Y':
    { /* mamy wykonac rozmywanie pionowe o r=2 */
      wybor->roz_pionowe2 = 1;
      break;
    }
    case 'h':
    { /* mamy wykonac histogram */
      wybor->histogram = 1;
      break;
    }
    case 'k':
    { /* mamy wykonac konturowanie */
      wybor->konturowanie = 1;
      break;
    }
    case 'K':
    { /* mamy zmienic kolor */
      wybor->zmiana_koloru = 1;
      break;
    }
    case 'd':
    { /* mamy wyswietlic obraz */
      wybor->wyswietl = 1;
      break;
    }
    default: /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  }   /* koniec for */

  if (wybor->plik_we != NULL) /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else
    return B_BRAKPLIKU; /* blad:  nie otwarto pliku wejsciowego  */
}

/*******************************************************/
/* Testowe wywołanie funkcji przetwarzaj_opcje         */
/* PRE:                                                */
/*      brak                                           */
/* POST:                                               */
/*      brak                                           */
/*******************************************************/

int main(int argc, char **argv)
{
  t_opcje opcje;
  int kod_bledu;
  Obraz Obraz;
  kod_bledu = przetwarzaj_opcje(argc, argv, &opcje);
  if (kod_bledu)
  {
    printf("Blad nr %d\n", kod_bledu);
  }
  else
  {
    czytaj(opcje.plik_we, &Obraz);
    fclose(opcje.plik_we);
    if (opcje.w_kolor == 's')
    {
      konwersja_do_szarosci(&Obraz);
    }
    if (opcje.zmiana_koloru == 1)
    {
      zmiana_koloru(&Obraz, opcje.w_kolor);
    }
    if (opcje.negatyw == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        negatyw(&Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        negatyw_PPM(&Obraz, opcje.w_kolor);
      }
    }
    if (opcje.progowanie == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        progowanie(opcje.w_progu, &Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        progowanie_PPM(opcje.w_progu, &Obraz, opcje.w_kolor);
      }
    }
    if (opcje.progowanie_czerni == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        progowanie_czerni(opcje.w_progu_c, &Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        progowanie_czerni_PPM(opcje.w_progu_c, &Obraz, opcje.w_kolor);
      }
    }
    if (opcje.progowanie_bieli == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        progowanie_bieli(opcje.w_progu_b, &Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        progowanie_bieli_PPM(opcje.w_progu_b, &Obraz, opcje.w_kolor);
      }
    }
    if (opcje.korekcja_gamma == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        korekcja_gamma(opcje.w_gamma, &Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        korekcja_gamma_PPM(opcje.w_gamma, &Obraz, opcje.w_kolor);
      }
    }
    if (opcje.zamiana_poziomow == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        zamiana_poziomow(opcje.w_czerni, opcje.w_bieli, &Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        zamiana_poziomow_PPM(opcje.w_czerni, opcje.w_bieli, &Obraz, opcje.w_kolor);
      }
    }
    if (opcje.konturowanie == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        konturowanie(&Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        konturowanie_PPM(&Obraz, opcje.w_kolor);
      }
    }
    if (opcje.roz_pionowe1 == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        roz_pionowe1(&Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        roz_pionowe1_PPM(&Obraz, opcje.w_kolor);
      }
    }
    if (opcje.roz_pionowe2 == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        roz_pionowe2(&Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        roz_pionowe2_PPM(&Obraz, opcje.w_kolor);
      }
    }
    if (opcje.roz_poziome1 == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        roz_poziome1(&Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        roz_poziome1_PPM(&Obraz, opcje.w_kolor);
      }
    }
    if (opcje.roz_poziome2 == 1)
    {
      if (Obraz.magiczna_liczba == '2')
      {
        roz_poziome2(&Obraz);
      }
      else if (Obraz.magiczna_liczba == '3')
      {
        roz_poziome2_PPM(&Obraz, opcje.w_kolor);
      }
    }
    zapisz(opcje.plik_wy,&Obraz);
    fclose(opcje.plik_wy);
    if(opcje.wyswietl == 1)
    {
      wyswietl(opcje.nazwa_pliku_wy);
    }
    printf("Opcje poprawne\n");
  }
  return kod_bledu;
}

