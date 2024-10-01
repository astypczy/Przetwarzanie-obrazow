#ifndef OBSLUGA_H
#define OBSLUGA_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>                                                           
#include"struktura.h"

#define MAX 512       
#define DL_LINII 1024      

int czytaj(FILE *plik_we,Obraz *Obraz);
int zapisz(FILE *plik_wy,Obraz *Obraz);
void wyswietl(char *n_pliku);
#endif


