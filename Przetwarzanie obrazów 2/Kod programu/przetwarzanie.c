#include"przetwarzanie.h"

void negatyw(Obraz *Obraz)                      
{
  int i,j;

  for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      Obraz->obraz_pgm[i][j]=Obraz->szarosci-Obraz->obraz_pgm[i][j];                                         /*pętla wykonująca warunek negatywu podany w pdf w operacjach przetwarzania obrazów*/
    }
  }
}
void negatyw_PPM(Obraz *Obraz, char kolor)
{
  int i,j,k;
  if(kolor=='r')              /*uwzględnienie koloru*/
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  }
  if((k==0)|(k==1)|(k==2))   /*operacja na kanale odpowiadającym wybranemu kolorowi*/
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        Obraz->obraz_ppm[i][j][k]=Obraz->szarosci-Obraz->obraz_ppm[i][j][k];                        /*pętla wykonująca warunek negatywu podany w pdf w operacjach przetwarzania obrazów*/
      }
    }  
  }
  else
  {
    for(k=0; k<3; k++)                                              /*operacja na każdym kanale*/
    {
      for(i=0;i<Obraz->wymy;i++)
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          Obraz->obraz_ppm[i][j][k]=Obraz->szarosci-Obraz->obraz_ppm[i][j][k];                 /*pętla wykonująca warunek negatywu podany w pdf w operacjach przetwarzania obrazów*/
        }
      }  
    }
  }
}
void progowanie(float proc_p, Obraz *Obraz)     
{
  int i,j;
  int prog;                                                                             /*wprowadzamy dwie zmienne prog i proc_p, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=Obraz->szarosci*proc_p/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      if(Obraz->obraz_pgm[i][j]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
      {
        Obraz->obraz_pgm[i][j]=0;
      }
      else
      {
        Obraz->obraz_pgm[i][j]=Obraz->szarosci;
      }
    }
  }
}
void progowanie_PPM(float proc_p, Obraz *Obraz, char kolor)     
{
  int i,j,k;
  int prog; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  }                                                                            /*wprowadzamy dwie zmienne prog i proc_p, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=Obraz->szarosci*proc_p/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  if((k==0)|(k==1)|(k==2))                /*jeden kanał*/
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        if(Obraz->obraz_ppm[i][j][k]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
        {
          Obraz->obraz_ppm[i][j][k]=0;
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=Obraz->szarosci;
        }
      }
    }
  }
  else
  {
    for(k=0; k<3; k++)      /*każdy kanał*/
    {
      for(i=0;i<Obraz->wymy;i++)
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          if(Obraz->obraz_ppm[i][j][k]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
          {
            Obraz->obraz_ppm[i][j][k]=0;
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=Obraz->szarosci;
          }
        }
      }
    }
  }
  
}
void korekcja_gamma(float gamma1, Obraz *Obraz)  
{
  int i,j;                                                                               /*dodajemy zmienną gamma1, oznacza ona wartość gammy podaną przez użytkownika*/
  for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      Obraz->obraz_pgm[i][j]=pow((float)Obraz->obraz_pgm[i][j]/Obraz->szarosci,1/gamma1)*Obraz->szarosci;            /*obliczamy korekcję wg wzoru, musimy przypisać jednej zmiennej typ float aby funkcja działała poprawnie*/
    }                                                                                    /*zmieniamy typ obrazu_pgm lub szarosci*/
  } 
}
void korekcja_gamma_PPM(float gamma1, Obraz *Obraz, char kolor)  
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  }                                                                                /*dodajemy zmienną gamma1, oznacza ona wartość gammy podaną przez użytkownika*/
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        Obraz->obraz_ppm[i][j][k]=pow((float)Obraz->obraz_ppm[i][j][k]/Obraz->szarosci,1/gamma1)*Obraz->szarosci;            /*obliczamy korekcję wg wzoru, musimy przypisać jednej zmiennej typ float aby funkcja działała poprawnie*/
      }                                                                                    /*zmieniamy typ obrazu_pgm lub szarosci*/
    } 
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          Obraz->obraz_ppm[i][j][k]=pow((float)Obraz->obraz_ppm[i][j][k]/Obraz->szarosci,1/gamma1)*Obraz->szarosci;            /*obliczamy korekcję wg wzoru, musimy przypisać jednej zmiennej typ float aby funkcja działała poprawnie*/
        }                                                                                    /*zmieniamy typ obrazu_pgm lub szarosci*/
      } 
    }
  }
}
void konturowanie(Obraz *Obraz)
{
  int i,j;
  for(i=0;i<Obraz->wymy;i++)
    {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<Obraz->wymx;j++)                                                         /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
        if(i==Obraz->wymy-1 && j==Obraz->wymx-1)
        {
          Obraz->obraz_pgm[i][j]=abs(Obraz->obraz_pgm[0][j]-Obraz->obraz_pgm[i][j])+abs(Obraz->obraz_pgm[i][0]-Obraz->obraz_pgm[i][j]);
        }
        else if(i==Obraz->wymy-1)
        {
          Obraz->obraz_pgm[i][j]=abs(Obraz->obraz_pgm[0][j]-Obraz->obraz_pgm[i][j])+abs(Obraz->obraz_pgm[i][j+1]-Obraz->obraz_pgm[i][j]);
        }
        else if(j==Obraz->wymx-1)
        {
          Obraz->obraz_pgm[i][j]=abs(Obraz->obraz_pgm[i+1][j]-Obraz->obraz_pgm[i][j])+abs(Obraz->obraz_pgm[i][0]-Obraz->obraz_pgm[i][j]);
        }
        else
        {
        Obraz->obraz_pgm[i][j]=abs(Obraz->obraz_pgm[i+1][j]-Obraz->obraz_pgm[i][j])+abs(Obraz->obraz_pgm[i][j+1]-Obraz->obraz_pgm[i][j]);
        }
      }
    } 
}
void konturowanie_PPM(Obraz *Obraz, char kolor)
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  if((k==0)|(k==1)|(k==2))
  { 
    for(i=0;i<Obraz->wymy;i++)
    {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
        if(i==Obraz->wymy-1 && j==Obraz->wymx-1)
        {
          Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[0][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][0][k]-Obraz->obraz_ppm[i][j][k]);
        }
        else if(i==Obraz->wymy-1)
        {
          Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[0][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][j+1][k]-Obraz->obraz_ppm[i][j][k]);
        }
        else if(j==Obraz->wymx-1)
        {
          Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[i+1][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][0][k]-Obraz->obraz_ppm[i][j][k]);
        }
        else
        {
        Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[i+1][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][j+1][k]-Obraz->obraz_ppm[i][j][k]);
        }
      }
    }
  } 
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
        for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
        {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
          if(i==Obraz->wymy-1 && j==Obraz->wymx-1)
          {
            Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[0][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][0][k]-Obraz->obraz_ppm[i][j][k]);
          }
          else if(i==Obraz->wymy-1)
          {
            Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[0][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][j+1][k]-Obraz->obraz_ppm[i][j][k]);
          }
          else if(j==Obraz->wymx-1)
          {
            Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[i+1][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][0][k]-Obraz->obraz_ppm[i][j][k]);
          }
          else
          {
          Obraz->obraz_ppm[i][j][k]=abs(Obraz->obraz_ppm[i+1][j][k]-Obraz->obraz_ppm[i][j][k])+abs(Obraz->obraz_ppm[i][j+1][k]-Obraz->obraz_ppm[i][j][k]);
          }
        }
      }
    }
  }
}
void histogram(Obraz *Obraz)
{
  int i,j;
  int wartosc_MIN, wartosc_MAX;                                               /*dodajemy dwie zmienne wartosc_MIN oraz wartosc_MAX, odpowiadają one najciemniejszemu i najjaśniejszemu pikselowi obrazu*/
  wartosc_MAX=0;                                                              
  wartosc_MIN=Obraz->szarosci;                                                                        
  for(i=0;i<Obraz->wymy;i++)                                                         /*szukanie najjaśniejszego punktu*/
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      if(Obraz->obraz_pgm[i][j]>wartosc_MAX)                                        
      {
        wartosc_MAX=Obraz->obraz_pgm[i][j];
      }
      else
      {
      }
    }
  }
  for(i=0;i<Obraz->wymy;i++)                                                       /*szukanie najciemniejszego punktu*/
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      if(Obraz->obraz_pgm[i][j]<wartosc_MIN)
      {
        wartosc_MIN=Obraz->obraz_pgm[i][j];
      }
      else
      {
      }
    }
  }  
  for(i=0;i<Obraz->wymy;i++)                                                       /*rozciąganie histogramu wg wzoru*/
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j]-wartosc_MIN)*Obraz->szarosci/(wartosc_MAX-wartosc_MIN);    
    }
  }  
}
void histogram_PPM(Obraz *Obraz, char kolor)
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  }  
  int wartosc_MIN, wartosc_MAX;                                               /*dodajemy dwie zmienne wartosc_MIN oraz wartosc_MAX, odpowiadają one najciemniejszemu i najjaśniejszemu pikselowi obrazu*/
  wartosc_MAX=0;                                                              
  wartosc_MIN=Obraz->szarosci;
  if((k==0)|(k==1)|(k==2))
  {                                                                        
    for(i=0;i<Obraz->wymy;i++)                                                         /*szukanie najjaśniejszego punktu*/
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        if(Obraz->obraz_ppm[i][j][k]>wartosc_MAX)                                        
        {
          wartosc_MAX=Obraz->obraz_ppm[i][j][k];
        }
        else
        {
        }
      }
    }
    for(i=0;i<Obraz->wymy;i++)                                                       /*szukanie najciemniejszego punktu*/
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        if(Obraz->obraz_ppm[i][j][k]<wartosc_MIN)
        {
          wartosc_MIN=Obraz->obraz_ppm[i][j][k];
        }
        else
        {
        }
      }
    }  
    for(i=0;i<Obraz->wymy;i++)                                                       /*rozciąganie histogramu wg wzoru*/
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j][k]-wartosc_MIN)*Obraz->szarosci/(wartosc_MAX-wartosc_MIN);    
      }
    } 
  } 
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)                                                         /*szukanie najjaśniejszego punktu*/
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          if(Obraz->obraz_ppm[i][j][k]>wartosc_MAX)                                        
          {
            wartosc_MAX=Obraz->obraz_ppm[i][j][k];
          }
          else
          {
          }
        }
      }
      for(i=0;i<Obraz->wymy;i++)                                                       /*szukanie najciemniejszego punktu*/
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          if(Obraz->obraz_ppm[i][j][k]<wartosc_MIN)
          {
            wartosc_MIN=Obraz->obraz_ppm[i][j][k];
          }
          else
          {
          }
        }
      }  
      for(i=0;i<Obraz->wymy;i++)                                                       /*rozciąganie histogramu wg wzoru*/
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j][k]-wartosc_MIN)*Obraz->szarosci/(wartosc_MAX-wartosc_MIN);    
        }
      }       
    }
  }
}
void progowanie_czerni(float proc_pc, Obraz *Obraz)     
{
  int i,j;
  int prog;                                                                             /*wprowadzamy dwie zmienne prog i proc_pc, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=Obraz->szarosci*proc_pc/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      if(Obraz->obraz_pgm[i][j]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
      {
        Obraz->obraz_pgm[i][j]=0;
      }
      else
      {
        Obraz->obraz_pgm[i][j]=Obraz->obraz_pgm[i][j];
      }
    }
  }
}
void progowanie_czerni_PPM(float proc_pc, Obraz *Obraz, char kolor)     
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  int prog;                                                                             /*wprowadzamy dwie zmienne prog i proc_pc, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=Obraz->szarosci*proc_pc/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        if(Obraz->obraz_ppm[i][j][k]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
        {
          Obraz->obraz_ppm[i][j][k]=0;
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=Obraz->obraz_ppm[i][j][k];
        }
      }
    }
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          if(Obraz->obraz_ppm[i][j][k]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
          {
            Obraz->obraz_ppm[i][j][k]=0;
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=Obraz->obraz_ppm[i][j][k];
          }
        }
      }      
    }
  }  
}
void progowanie_bieli(float proc_pb, Obraz *Obraz)     
{
  int i,j;
  int prog;                                                                             /*wprowadzamy dwie zmienne prog i proc_pb, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=Obraz->szarosci*proc_pb/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      if(Obraz->obraz_pgm[i][j]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
      {
        Obraz->obraz_pgm[i][j]=Obraz->obraz_pgm[i][j];
      }
      else
      {
        Obraz->obraz_pgm[i][j]=Obraz->szarosci;
      }
    }
  }
}
void progowanie_bieli_PPM(float proc_pb, Obraz *Obraz, char kolor)     
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  int prog;                                                                             /*wprowadzamy dwie zmienne prog i proc_pb, 1. oznacza próg, który obliczamy wg wzoru*/
  prog=Obraz->szarosci*proc_pb/100;                                                             /*druga oznaca procent podany przez użytkownika, musimy podaną wartość podzielić przez 100, aby otrzymać odpowiedni próg*/
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        if(Obraz->obraz_ppm[i][j][k]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
        {
          Obraz->obraz_ppm[i][j][k]=Obraz->obraz_ppm[i][j][k];
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=Obraz->szarosci;
        }
      }
    }
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          if(Obraz->obraz_ppm[i][j][k]<=prog)                                                          /*wykonywanie progowania wg wzoru*/
          {
            Obraz->obraz_ppm[i][j][k]=Obraz->obraz_ppm[i][j][k];
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=Obraz->szarosci;
          }
        }
      }      
    }
  }
}
void zamiana_poziomow(float proc_czern, float proc_biel, Obraz *Obraz)     
{
  int i,j;
  float czern;
  float biel;
  czern=Obraz->szarosci*proc_czern/100;                  /*obliczanie poziomu czerni*/
  biel=Obraz->szarosci*proc_biel/100;                     /*obliczanie poziomu bieli*/
    for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      if(Obraz->obraz_pgm[i][j]<=czern)                                                          
      {
        Obraz->obraz_pgm[i][j]=0;
      }
      else if(Obraz->obraz_pgm[i][j]>=biel)
      {
        Obraz->obraz_pgm[i][j]=Obraz->szarosci;
      }
      else if(czern<Obraz->obraz_pgm[i][j] && Obraz->obraz_pgm[i][j]<biel)            /*rozpatrzenie dwóch przypadków*/
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j]-czern)*Obraz->szarosci/abs(biel-czern);
      }
      else if(Obraz->obraz_pgm[i][j]>biel && czern>Obraz->obraz_pgm[i][j])
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j]-czern)*Obraz->szarosci/abs(biel-czern);
      }
    }
  }
}
void zamiana_poziomow_PPM(float proc_czern, float proc_biel, Obraz *Obraz, char kolor)     
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  float czern;
  float biel;
  czern=Obraz->szarosci*proc_czern/100;       /*obliczanie poziomu czerni*/
  biel=Obraz->szarosci*proc_biel/100;         /*obliczanie poziomu bieli*/
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        if(Obraz->obraz_ppm[i][j][k]<=czern)                                                          
        {
          Obraz->obraz_ppm[i][j][k]=0;
        }
        else if(Obraz->obraz_ppm[i][j][k]>=biel)
        {
          Obraz->obraz_ppm[i][j][k]=Obraz->szarosci;
        }
        else if(czern<Obraz->obraz_ppm[i][j][k] && Obraz->obraz_ppm[i][j][k]<biel) /*rozpatrzenie dwóch przypadków*/
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j][k]-czern)*Obraz->szarosci/abs(biel-czern);
        }
        else if(Obraz->obraz_ppm[i][j][k]>biel && czern>Obraz->obraz_ppm[i][j][k])
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j][k]-czern)*Obraz->szarosci/abs(biel-czern);
        }
      }
    }
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {
        for(j=0;j<Obraz->wymx;j++)
        {
          if(Obraz->obraz_ppm[i][j][k]<=czern)                                                          
          {
            Obraz->obraz_ppm[i][j][k]=0;
          }
          else if(Obraz->obraz_ppm[i][j][k]>=biel)
          {
            Obraz->obraz_ppm[i][j][k]=Obraz->szarosci;
          }
          else if(czern<Obraz->obraz_ppm[i][j][k] && Obraz->obraz_ppm[i][j][k]<biel)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j][k]-czern)*Obraz->szarosci/abs(biel-czern);
          }
          else if(Obraz->obraz_ppm[i][j][k]>biel && czern>Obraz->obraz_ppm[i][j][k])
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j][k]-czern)*Obraz->szarosci/abs(biel-czern);
          }
        }
      }      
    }
  }
}
void roz_pionowe1(Obraz *Obraz)                      
{
  int i,j;
  for(i=0;i<Obraz->wymy;i++)
  {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
    for(j=0;j<Obraz->wymx;j++)                                                         /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
    {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
      if(i==0 )
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[Obraz->wymy-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i+1][j])/3;
      }
      else if(i==Obraz->wymy-1)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[0][j])/3;
      }
      else
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i+1][j])/3;
      }
    }
  } 
}
void roz_pionowe1_PPM(Obraz *Obraz, char kolor)                      
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  }
  if((k==0)|(k==1)|(k==2))
  { 
    for(i=0;i<Obraz->wymy;i++)
    {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
        if(i==0 )
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[Obraz->wymy-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k])/3;
        }
        else if(i==Obraz->wymy-1)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[0][j][k])/3;
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k])/3;
        }
      }
    }
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
        for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
        {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
          if(i==0 )
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[Obraz->wymy-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k])/3;
          }
          else if(i==Obraz->wymy-1)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[0][j][k])/3;
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k])/3;
          }
        }
      }      
    }
  }
}
void roz_poziome1(Obraz *Obraz)                      
{
  int i,j;
  for(i=0;i<Obraz->wymy;i++)
  {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
    for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
    {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
      if(j==0)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][Obraz->wymx-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][j+1])/3;
      }
      else if(j==Obraz->wymx-1)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][0])/3;
      }
      else
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][j+1])/3;
      }
    }
  } 
}
void roz_poziome1_PPM(Obraz *Obraz, char kolor)                      
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
        if(j==0)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][Obraz->wymx-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k])/3;
        }
        else if(j==Obraz->wymx-1)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][0][k])/3;
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k])/3;
        }
      }
    } 
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
        for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
        {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
          if(j==0)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][Obraz->wymx-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k])/3;
          }
          else if(j==Obraz->wymx-1)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][0][k])/3;
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k])/3;
          }
        }
      }       
    }
  } 
}
void roz_pionowe2(Obraz *Obraz)                      
{
  int i,j;
  for(i=0;i<Obraz->wymy;i++)
  {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
    for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
    {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
      if(i==0 )
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[Obraz->wymy-2][j]+Obraz->obraz_pgm[Obraz->wymy-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i+1][j]+Obraz->obraz_pgm[i+2][j])/5;
      }
      else if(i==1)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[Obraz->wymy-1][j]+Obraz->obraz_pgm[i-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i+1][j]+Obraz->obraz_pgm[i+2][j])/5;
      }
      else if(i==Obraz->wymy-2)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i-2][j]+Obraz->obraz_pgm[i-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i+1][j]+Obraz->obraz_pgm[0][j])/5;
      }
      else if(i==Obraz->wymy-1)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i-2][j]+Obraz->obraz_pgm[i-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[0][j]+Obraz->obraz_pgm[1][j])/5;
      }
      else
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i-2][j]+Obraz->obraz_pgm[i-1][j]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i+1][j]+Obraz->obraz_pgm[i+2][j])/5;
      }
    }
  } 
}
void roz_pionowe2_PPM(Obraz *Obraz, char kolor)                      
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
        if(i==0 )
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[Obraz->wymy-2][j][k]+Obraz->obraz_ppm[Obraz->wymy-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[i+2][j][k])/5;
        }
        else if(i==1)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[Obraz->wymy-1][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[i+2][j][k])/5;
        }
        else if(i==Obraz->wymy-2)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-2][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[0][j][k])/5;
        }
        else if(i==Obraz->wymy-1)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-2][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[0][j][k]+Obraz->obraz_ppm[1][j][k])/5;
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-2][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[i+2][j][k])/5;
        }
      }
    }
  }
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
        for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
        {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
          if(i==0 )
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[Obraz->wymy-2][j][k]+Obraz->obraz_ppm[Obraz->wymy-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[i+2][j][k])/5;
          }
          else if(i==1)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[Obraz->wymy-1][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[i+2][j][k])/5;
          }
          else if(i==Obraz->wymy-2)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-2][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[0][j][k])/5;
          }
          else if(i==Obraz->wymy-1)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-2][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[0][j][k]+Obraz->obraz_ppm[1][j][k])/5;
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i-2][j][k]+Obraz->obraz_ppm[i-1][j][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i+1][j][k]+Obraz->obraz_ppm[i+2][j][k])/5;
          }
        }
      }      
    }
  }
   
}
void roz_poziome2(Obraz *Obraz)                      
{
  int i,j;
  for(i=0;i<Obraz->wymy;i++)
  {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
    for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
    {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
      if(j==0 )
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][Obraz->wymx-2]+Obraz->obraz_pgm[i][Obraz->wymx-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][j+1]+Obraz->obraz_pgm[i][j+2])/5;
      }
      else if(j==1)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][Obraz->wymx-1]+Obraz->obraz_pgm[i][j-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][j+1]+Obraz->obraz_pgm[i][j+2])/5;
      }
      else if(j==Obraz->wymx-2)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j-2]+Obraz->obraz_pgm[i][j-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][j+1]+Obraz->obraz_pgm[i][0])/5;
      }
      else if(j==Obraz->wymx-1)
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j-2]+Obraz->obraz_pgm[i][j-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][0]+Obraz->obraz_pgm[i][1])/5;
      }
      else
      {
        Obraz->obraz_pgm[i][j]=(Obraz->obraz_pgm[i][j-2]+Obraz->obraz_pgm[i][j-1]+Obraz->obraz_pgm[i][j]+Obraz->obraz_pgm[i][j+1]+Obraz->obraz_pgm[i][j+2])/5;
      }
    }
  } 
}
void roz_poziome2_PPM(Obraz *Obraz, char kolor)                      
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  if((k==0)|(k==1)|(k==2))
  {
    for(i=0;i<Obraz->wymy;i++)
    {                                                                                    /*wykonujemy rozmywanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
      for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
      {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych lub ostatnich wierszy i kolumn*/
        if(j==0 )
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][Obraz->wymx-2][k]+Obraz->obraz_ppm[i][Obraz->wymx-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][j+2][k])/5;
        }
        else if(j==1)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][Obraz->wymx-1][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][j+2][k])/5;
        }
        else if(j==Obraz->wymx-2)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-2][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][0][k])/5;
        }
        else if(j==Obraz->wymx-1)
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-2][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][0][k]+Obraz->obraz_ppm[i][1][k])/5;
        }
        else
        {
          Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-2][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][j+2][k])/5;
        }
      }
    }
  } 
  else
  {
    for(k=0; k<3; k++)
    {
      for(i=0;i<Obraz->wymy;i++)
      {                                                                                    /*wykonujemy konturowanie wg wzoru, zauważamy, że nie może być spełnione przez wszystkie wiersze i kolumny*/
        for(j=0;j<Obraz->wymx;j++)                                                                /*ponieważ w pewnym momencie będziemy brali wartości spoza tablicy*/
        {                                                                                  /*dla takich przypadków bierzemy wartości z pierwszych wierszy i kolumn*/
          if(j==0 )
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][Obraz->wymx-2][k]+Obraz->obraz_ppm[i][Obraz->wymx-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][j+2][k])/5;
          }
          else if(j==1)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][Obraz->wymx-1][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][j+2][k])/5;
          }
          else if(j==Obraz->wymx-2)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-2][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][0][k])/5;
          }
          else if(j==Obraz->wymx-1)
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-2][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][0][k]+Obraz->obraz_ppm[i][1][k])/5;
          }
          else
          {
            Obraz->obraz_ppm[i][j][k]=(Obraz->obraz_ppm[i][j-2][k]+Obraz->obraz_ppm[i][j-1][k]+Obraz->obraz_ppm[i][j][k]+Obraz->obraz_ppm[i][j+1][k]+Obraz->obraz_ppm[i][j+2][k])/5;
          }
        }
      }      
    }
  } 
}
void konwersja_do_szarosci(Obraz *Obraz)
{
  int i,j,k;

  Obraz->obraz_pgm=malloc(Obraz->wymy*sizeof(int*));          /*alokacja pamięci dla nowo powstałego obrazu pgm*/
  for(i=0;i<Obraz->wymy;i++)
  {
    Obraz->obraz_pgm[i]=malloc(Obraz->wymx*sizeof(int));
    Obraz->magiczna_liczba='2';
  }
  for(i=0; i<Obraz->wymy;i++)
  {
    for(j=0; j<Obraz->wymx; j++)
    {
      Obraz->obraz_pgm[i][j]=(Obraz->obraz_ppm[i][j][0]+Obraz->obraz_ppm[i][j][1]+Obraz->obraz_ppm[i][j][2])/3; /*wartość piksela pgm jest średnią arytmetyczną kanałów tego piksela w PPM*/
    }
  }
  for(i=0;i<Obraz->wymy;i++)
  {
    for(j=0;j<Obraz->wymx;j++)
    {
      free(Obraz->obraz_ppm[i][j]);    /*zwalnianie pamięci niepotrzebnej obrazu PPM*/
    }
  }
  for(i=0;i<Obraz->wymy;i++)
  {
    free(Obraz->obraz_ppm[i]);
  }
  free(Obraz->obraz_ppm);
}
void zmiana_koloru(Obraz *Obraz, char kolor)     
{
  int i,j,k; 
  if(kolor=='r')
  {
    k=0;
  }
  else if(kolor=='g')
  {
    k=1;
  }
  else if(kolor=='b')
  {
    k=2;
  } 
  if(k==0)
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        Obraz->obraz_ppm[i][j][1]=0;  /*aby obraz był czerwony pozostałe kanały są zerowane*/
        Obraz->obraz_ppm[i][j][2]=0;
      }
    }
  }
  else if(k==1)
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        Obraz->obraz_ppm[i][j][0]=0;   /*aby obraz był zielony pozostałe kanały są zerowane*/
        Obraz->obraz_ppm[i][j][2]=0;
      }
    }
  }
  else if(k==2)
  {
    for(i=0;i<Obraz->wymy;i++)
    {
      for(j=0;j<Obraz->wymx;j++)
      {
        Obraz->obraz_ppm[i][j][0]=0;  /*aby obraz był niebieski pozostałe kanały są zerowane*/
        Obraz->obraz_ppm[i][j][1]=0;
      }
    }
  }
}