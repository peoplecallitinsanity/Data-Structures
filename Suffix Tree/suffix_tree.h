/* PULBERE Vlada - 312CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define litere_max 27
#define zero 0
#define unu 1
#define max_cuvant 150
#define term '\0'


typedef struct Nod {
    struct Nod *copii[litere_max];
} Nod;


typedef struct NodCoada {
    Nod *nod;
    struct NodCoada *urm;
} NodCoada;

typedef struct {
    NodCoada *inceput;
    NodCoada *sfarsit;
} Coada;

Nod *creeazaNod();
int numarul_caracterului(char c);
void adauga_sufix(Nod *radacina, const char *sufix);
void add_coada(Coada *c, Nod *nod) ;
Nod *pop_coada(Coada *c) ;
void print_tree(Nod *radacina, FILE *iesire);
void free_tree(Nod *radacina);
bool verificaSufix(Nod *radacina, const char *sufix);
