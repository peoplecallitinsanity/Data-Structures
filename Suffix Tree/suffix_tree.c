/* PULBERE Vlada - 312CB */
#include "tema2.h"


Nod *creeazaNod() {
    // creaza un nod nou pentru copac
    Nod *nodNou = (Nod *)malloc(sizeof(Nod));
    for (int i = zero; i < litere_max; i++) {
        // initializam nodurile cu NULL
        nodNou->copii[i] = NULL;
    }
    return nodNou;
}

int numarul_caracterului(char c) {
    // calculam numarul ASCII al caracterului
    // daca caracterul este $ - nr este 0 ($ < orice alt caracter)
    if (c == '$') return 0;
    if (c >= 'a' && c <= 'z') return c - 'a' + unu;
    return -1;  // pentru orice alt caracter returnam -1
}

void adauga_sufix(Nod *radacina, const char *sufix) {
    Nod *curent = radacina;
    for (int i = zero; sufix[i] != term; i++) {
        // parcurgem pana la sfarsitul sirului
        int index = numarul_caracterului(sufix[i]);
        // ignoram caracterele invalide
        if (index < zero || index >= litere_max) continue;
        if (curent->copii[index] == NULL) {
            // daca nu exista nod la index, cream altul
            curent->copii[index] = creeazaNod();
        }
        // mutam pointerul la urmatorul copil
        curent = curent->copii[index];
    }
}


void add_coada(Coada *c, Nod *nod) {
    // functia adauga un nod in coada
    NodCoada *nodNou = malloc(sizeof(NodCoada));
    nodNou->nod = nod;
    // setam urm la NULL
    nodNou->urm = NULL;
    if (c->sfarsit == NULL) {
        // la prima inserare, nodul va fi inceputul si sfarsitul
        c->inceput = c->sfarsit = nodNou;
    } else {
        // adauagam nodul la sfarsitul cozii
        c->sfarsit->urm = nodNou;
        c->sfarsit = nodNou;
    }
}

Nod *pop_coada(Coada *c) {
    // scoatem un nod din coada, si il returnam
    if (c->inceput == NULL) return NULL;
    // pastram nodul intr-o variabila
    Nod *nod = c->inceput->nod;
    NodCoada *aux = c->inceput;
    // restabilim legaturile
    c->inceput = c->inceput->urm;
    // daca scoatem ultimul element din coada
    if (c->inceput == NULL) c->sfarsit = NULL;
    // eliberam nodul
    free(aux);
    return nod;
}


void print_tree(Nod *radacina, FILE *iesire) {
    // parcurgere in latime si printare arbore de sufixe 
    if (radacina == NULL) return;
    Coada c;
    // setam capetele cozii
    (&c)->inceput = (&c)->sfarsit = NULL;
    // adaugam nodul radacina in coada
    add_coada(&c, radacina);
    // parcurgem atat timp cat avem elemente in coada
    while ((&c)->inceput) {
        int nivel = zero;
        // calculam numarul de noduri la nivelul curent
        for (NodCoada *aux = c.inceput; aux != NULL; aux = aux->urm) nivel++;
        // parcurgem fiecare nod de la nivelul curent
        for (int i = zero; i < nivel; i++) {
            // extragem primul nod
            Nod *curent = pop_coada(&c);
            if (curent == NULL) continue;
            // parcurgem caracterele 
            for (int j = zero; j < litere_max; j++) {
                // daca exista nod copil la pizitia j
                if (curent->copii[j] != NULL) {
                    // scriem caracterul corespunzatorul codului
                    if (j == zero) {
                        fprintf(iesire, "%c ", '$');
                    } else {
                        fprintf(iesire, "%c ", 'a' + j - unu);
                    }
                add_coada(&c, curent->copii[j]);
                }
            }
        }
        // daca mai sunt elemente, adaugam o linie noua
        if ((&c)->inceput) {
            fprintf(iesire, "\n");
        }
    }
}
void free_tree(Nod *radacina) {
    // functia elibereaza memoria ocupata de arbore
    if (radacina == NULL) return;
    for (int i = zero; i < litere_max; i++) {
        if (radacina->copii[i] != NULL) {
            free_tree(radacina->copii[i]);
        }
    }
    free(radacina);
}

bool verificaSufix(Nod *radacina, const char *sufix) {
    // functia verifica daca exista un anumit sufix in arbore
    Nod *curent = radacina;
    // parcurgem sirul pana la \0
    for (int i = zero; sufix[i] != term; i++) {
        // stabilim indexul/numarului caracterului curent
        int index = numarul_caracterului(sufix[i]);
        // daca nu gasim
        if (curent->copii[index] == NULL) {
            return false; 
        }
        // trecem la urmatorul caracter
        curent = curent->copii[index];
    }
    return curent->copii[zero] != NULL;
}