#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max_char 100
#define InscriptieDefault '#'
#define InscriptieLocomotiva '0'
#define nrCaractereMoveLeft 9
#define nrCaractereMoveRight 10
#define nrCaractereWrite 6
#define nrCaractereClearCell 10
#define nrCaractereClearAll 9
#define nrCaractereInsertLeft 12
#define nrCaractereInsertRight 13
#define nrCaractereSearch 7
#define nrCaractereSearchLeft 12
#define nrCaractereSearchRight 13
#define strCheck 0
#define nrCaractereExecute 7
#define nrCaractereShowCurrent 12
#define nrCaractereShow 4
#define nrCaractereSwitch 6
#define zero 0
#define unu 1

// implimentarea trenului sub forma de lista circulara dublu inlantuita
typedef struct Vagon {
    char inscriptie;
    struct Vagon *ant, *urm;
} Vagon;

typedef struct Tren {
    Vagon *locomotiva; // santinela
    Vagon *mecanic;
} Tren;

// implimentarea cozii pentru stocarea operatiilor
typedef struct celulaOperatie{
  char nume[max_char];
  struct celulaOperatie *urm;
} celulaOperatie, *TLista;

typedef struct coadaOperatii{ 
  celulaOperatie *inc, *sf;
} coadaOperatii;

typedef struct {
    int caractereGasite;
    bool sirGasit;
} Search_struct;

Tren initializareTren();
coadaOperatii* InitQ ();
void addCoadaOperatii( coadaOperatii *coada, char *nume);
void EXECUTE(Tren *tren, coadaOperatii *coada, FILE *TemaOut);
void MOVE_LEFT(Tren *tren);
void MOVE_RIGHT(Tren *tren);
void WRITE(Tren *tren, char inscriptie);
void CLEAR_CELL(Tren *tren);
void CLEAR_ALL(Tren *tren);
int INSERT_LEFT(Tren *tren, char inscriptie);
void INSERT_RIGHT(Tren *tren, char inscriptie);
void SHOW(Tren *tren, FILE *TemaOut);
Search_struct *SEARCH(Tren *tren, char *sirCautat);
Search_struct *SEARCH_LEFT(Tren *tren, char *sirCautat);
Search_struct *SEARCH_RIGHT(Tren *tren, char *sirCautat);
void SHOW_CURRENT(Tren *tren, FILE *TemaOut);
void SWITCH(coadaOperatii *coada);
void eliberareCoada(coadaOperatii *operatii);
void eliberareTrenulet(Tren *trenulet);

