#ifndef PRZETWARZANIE_H
#define PRZETWARZANIE_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>  
#include"struktura.h"                                                        
#define MAX 512       
#define DL_LINII 1024      
void negatyw(Obraz *Obraz);
void negatyw_PPM(Obraz *Obraz, char kolor);
void progowanie(float proc_p, Obraz *Obraz);
void progowanie_PPM(float proc_p, Obraz *Obraz, char kolor);
void korekcja_gamma(float gamma1, Obraz *Obraz);
void korekcja_gamma_PPM(float gamma1, Obraz *Obraz, char kolor);
void konturowanie(Obraz *Obraz);
void konturowanie_PPM(Obraz *Obraz, char kolor);
void histogram(Obraz *Obraz);
void histogram_PPM(Obraz *Obraz, char kolor);
void progowanie_czerni(float proc_pc, Obraz *Obraz);
void progowanie_czerni_PPM(float proc_pc, Obraz *Obraz, char kolor);
void progowanie_bieli(float proc_pb, Obraz *Obraz);
void progowanie_bieli_PPM(float proc_pb, Obraz *Obraz, char kolor);
void zamiana_poziomow(float proc_czern, float proc_biel, Obraz *Obraz);
void zamiana_poziomow_PPM(float proc_czern, float proc_biel, Obraz *Obraz, char kolor);
void roz_pionowe1(Obraz *Obraz);
void roz_pionowe1_PPM(Obraz *Obraz, char kolor);
void roz_poziome1(Obraz *Obraz);
void roz_poziome1_PPM(Obraz *Obraz, char kolor);
void roz_pionowe2(Obraz *Obraz);
void roz_pionowe2_PPM(Obraz *Obraz, char kolor);
void roz_poziome2(Obraz *Obraz);
void roz_poziome2_PPM(Obraz *Obraz, char kolor);
void konwersja_do_szarosci(Obraz *Obraz);
void zmiana_koloru(Obraz *Obraz, char kolor);
#endif
