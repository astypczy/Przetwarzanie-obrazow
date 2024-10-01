#ifndef STRUKTURA_H
#define STRUKTURA_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define MAX 512       
struct Obraz
{
  char magiczna_liczba;
  int ***obraz_ppm;
  int **obraz_pgm;
  int wymx;
  int wymy;
  int szarosci;
};
typedef struct Obraz Obraz;

#endif
