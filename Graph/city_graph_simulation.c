#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_char 100
#define terminator '\0'
#define zero 0
#define unu 1
#define doi 2

typedef struct nodLista {
    char destinatie[max_char];
    float *costuri; // pointer catre lista de gradul de uzura a tronsoanelor
    int numar_costuri; // numar tronsoane
    struct nodLista *urmator;
} nodLista;

typedef struct ListaAdiacenta {
    char sursa[max_char];
    nodLista *L; // vector adresa lista adiacenta
} ListaAdiacenta;
// structura grafului
typedef struct Graf {
    int numarVarfuri;
    ListaAdiacenta *lista;
    struct Muchie *muchii;
    int numarRute;
} Graf;

typedef struct Muchie {
    char sursa[max_char];
    char destinatie[max_char];
    float *costuri; // lista gradelor de uzura
    int numar_costuri; // numarul tronsoane
} Muchie;

// functia creaza un nou nod pentru lista de adiacenta
nodLista* nou_nodLista(char* destinatie, float* costuri, int numar_costuri) {
    nodLista* nouNod = malloc(sizeof(*nouNod));
    strcpy(nouNod->destinatie, destinatie);
    nouNod->costuri = malloc(numar_costuri * sizeof(nouNod->costuri));
    for (int i = zero; i < numar_costuri; i++) {
        nouNod->costuri[i] = costuri[i];
    }
    nouNod->numar_costuri = numar_costuri;
    nouNod->urmator = NULL;
    return nouNod;
}

// Funcție pentru a crea un graf cu un număr dat de vârfuri
Graf* creeazaGraf(int numarVarfuri) {
    Graf* graf = (Graf*)malloc(sizeof(Graf));
    graf->numarVarfuri = numarVarfuri;
    graf->numarRute = zero;
    // alocam memorie  pentru lista de adiacenta si muchii
    graf->lista = (ListaAdiacenta*)malloc(numarVarfuri * sizeof(ListaAdiacenta));
    graf->muchii = (Muchie*)malloc(numarVarfuri * sizeof(Muchie)); 
    for (int i = zero; i < numarVarfuri; ++i) {
        // pentru fiecare varf initializam lista si sursa
        graf->lista[i].L = NULL;
        graf->lista[i].sursa[zero] = terminator; 
    }

    return graf;
}

// funcita adauga o muchie in graf neorientat
void adaugaMuchie(Graf* graf, char* sursa, char* destinatie, float* costuri, int numar_costuri) {
    // pentru nodul sursa
    int i = zero, j = zero;
    for (i = zero; i < graf->numarVarfuri; i++) {
        // daca deja exista orasul sursa in lista, nu-l mai adaugam
        if (strcmp(graf->lista[i].sursa, sursa) == zero || graf->lista[i].L == NULL) {
            break;
        }
    }
    // daca nu exista, adaugam o noua valoare
    if (graf->lista[i].L == NULL) {
        strcpy(graf->lista[i].sursa, sursa);
    }

    // alocam memorie pentru un nou nod si il adaugam la lista de adiacenta la nodului(orasului) sursa
    nodLista* nouNod = nou_nodLista(destinatie, costuri, numar_costuri);
    nouNod->urmator = graf->lista[i].L;
    // actualizam capatul listei de adiacenta
    graf->lista[i].L = nouNod;

    // pentru nodul destinatie
    for (j = zero; j < graf->numarVarfuri; j++) {
        // daca deja exista nodul (orasul) in lista, nu-l mai adaugam
        if (strcmp(graf->lista[j].sursa, destinatie) == zero || graf->lista[j].L == NULL) {
            break;
        }
    }
    // daca nu exista, il adaugam si incrementam nr de noduri (orase)
    if (graf->lista[j].L == NULL) {
        strcpy(graf->lista[j].sursa, destinatie);
    }

    // alocam memorie pentru un nou nod si il adaugam la lista de adiacenta a orasului destinație
    nodLista* nouNodDest = nou_nodLista(sursa, costuri, numar_costuri);
    nouNodDest->urmator = graf->lista[j].L;
    // actualizam capatul listei
    graf->lista[j].L = nouNodDest;

    // adaugam in graf si muchia pentru a mentine ordinea
    Muchie* muchie = &graf->muchii[graf->numarRute++];
    strcpy(muchie->sursa, sursa);
    strcpy(muchie->destinatie, destinatie);
    // alocam memorie pentru lista gradelor de uzura
    muchie->costuri = (float*)malloc(numar_costuri * sizeof(float));
    for (i = zero; i < numar_costuri; i++) {
        // initializam costurile cu fiecare grad de uzura dat
        muchie->costuri[i] = costuri[i];
    }
    muchie->numar_costuri = numar_costuri;
}
float gasesteGradUzuraMaxVecin(Graf* graf, int muchieIndex, int costIndex) {
    float maxGrad = zero;

    // pentru vecinii de pe aceeasi muchie (rută)
    if (costIndex > zero && graf->muchii[muchieIndex].costuri[costIndex - unu] > maxGrad) {
        // daca gradul pentru care cautam nu se afla in capatul stang
        // maxGrad pentru vecinul stang este:
        maxGrad = graf->muchii[muchieIndex].costuri[costIndex - unu];
    }
    if (costIndex < graf->muchii[muchieIndex].numar_costuri - unu &&
        graf->muchii[muchieIndex].costuri[costIndex + unu] > maxGrad) {
        // daca gradul pentru care cautam nu este in capatul drept si 
        // gasim o valoare mai mare a gradului pentru vecinul drept
        maxGrad = graf->muchii[muchieIndex].costuri[costIndex + unu];
    }

    // daca trebuie sa cautam pentru unul dintre capetele listei gradele
    if (costIndex == zero || costIndex == graf->muchii[muchieIndex].numar_costuri - unu) {
        // iteram prin muchiile grafului
        for (int k = zero; k < graf->numarRute; k++) {
            // muchia curenta
            if (k == muchieIndex) continue; 
            // daca numele orasului destinatie de iteratie ==  numele sursei
            if (strcmp(graf->muchii[muchieIndex].sursa, graf->muchii[k].destinatie) == zero ) {
                // vecin din stanga, adica cautam pentru index == 0
                if (costIndex == zero && graf->muchii[k].costuri[graf->muchii[k].numar_costuri - unu] > maxGrad) {
                    // si daca gasim o val maxima noua ca ultima valoare din lista de iteratie
                    maxGrad = graf->muchii[k].costuri[graf->muchii[k].numar_costuri - unu];
                }
            }
            // daca numele orasului de iteratie sursa == cu numele orasului sursa
            if (strcmp(graf->muchii[muchieIndex].sursa, graf->muchii[k].sursa) == zero ) {
                // vecinul din stanga
                // valoarea maxima va fi prima valoare din lista gasita, daca e mai mare
                if (costIndex == zero && graf->muchii[k].costuri[zero] > maxGrad) {
                    maxGrad = graf->muchii[k].costuri[zero];
                }
            }
            // daca numele orasului sursa de iteratie ==  numele orasului destinatie
            if (strcmp(graf->muchii[muchieIndex].destinatie, graf->muchii[k].sursa) == zero) {
                // vecin din dreapta, daca e ultima valoare din lista gradelor de uzura
                // daca ultima valoare a gradului de uzura din muchia gasita e mai mare decat maxGrad
                if (costIndex == graf->muchii[muchieIndex].numar_costuri - unu && graf->muchii[k].costuri[zero] > maxGrad) {
                    // actualizam maxGrad
                    maxGrad = graf->muchii[k].costuri[zero];
                }
            }
            // daca numele orasului destinatie == numele orasului destinatie din iterare
            if (strcmp(graf->muchii[muchieIndex].destinatie, graf->muchii[k].destinatie) == zero) {
                // daca cautam vecin de dreapta, si daca gsim o noua valoare maxima
                if (costIndex == graf->muchii[muchieIndex].numar_costuri - unu && graf->muchii[k].costuri[graf->muchii[k].numar_costuri - unu] > maxGrad) {
                    // actualizam maxGrad cu ultima valoare din muchia in care iteram
                    maxGrad = graf->muchii[k].costuri[graf->muchii[k].numar_costuri - unu];
                }
            }
        }
    }
    return maxGrad;
}

void actualizareGradeUzura(Graf* graf, int ani) {
    for (int a = zero; a < ani; a++) {
        // intai stabilim noile valori pentru grade de uzura
        float **noiValori = malloc(graf->numarRute * sizeof(*noiValori));
        int **Zero_Initial = malloc(graf->numarRute * sizeof(*Zero_Initial));
        // pentru fiecare muchie
        for (int i = zero; i < graf->numarRute; i++) {
            // alocam memorie pentru fiecare element din liste
            noiValori[i] = malloc(graf->muchii[i].numar_costuri * sizeof(noiValori));
            Zero_Initial[i] = malloc(graf->muchii[i].numar_costuri * sizeof(Zero_Initial));
            for (int j = zero; j < graf->muchii[i].numar_costuri; j++) {
                // marcam pentru fiecare index, daca era zero initial sau nu
                Zero_Initial[i][j] = (graf->muchii[i].costuri[j] == zero) ? unu : zero;
                // daca un cost este zero
                if (graf->muchii[i].costuri[j] == zero) {
                    // gasim valoarea maxima a gradului de uzura dintre vecini
                    float maxGrad = gasesteGradUzuraMaxVecin(graf, i, j);
                    // actualizam valoarea maxima
                    if (maxGrad > zero) {
                        noiValori[i][j] = maxGrad / doi;
                    } else {
                        noiValori[i][j] = zero;
                    }
                } else { // daca costul nu era zero, salvam costul initial
                    noiValori[i][j] = graf->muchii[i].costuri[j];
                }
            }
        }

        // aplicam noile costuri pentru valorile de zero
        for (int i = zero; i < graf->numarRute; i++) {
            for (int j = zero; j < graf->muchii[i].numar_costuri; j++) {
                graf->muchii[i].costuri[j] = noiValori[i][j];
            }
            free(noiValori[i]);
        }
        free(noiValori);

        // dublam costurile excluzand cele care erau zero initial
        for (int i = zero; i < graf->numarRute; i++) {
            for (int j = zero; j < graf->muchii[i].numar_costuri; j++) {
                if (!Zero_Initial[i][j] && graf->muchii[i].costuri[j] != zero) {
                    graf->muchii[i].costuri[j] *= doi;
                    if (graf->muchii[i].costuri[j] > max_char) {
                        // val max e zero
                        graf->muchii[i].costuri[j] = max_char;
                    }
                }
            }
            // eliberam memoria pentru lista
            free(Zero_Initial[i]);
        }
        free(Zero_Initial);
    }
}



// afisarea grafului folosind liste de adiacenta
void afiseazaGraf(Graf* graf, FILE *out) {
    for (int i = zero; i < graf->numarRute; ++i) {
        Muchie* muchie = &graf->muchii[i];
        fprintf(out, "%s %s %d ", muchie->sursa, muchie->destinatie, muchie->numar_costuri);
        for (int j = zero; j < muchie->numar_costuri; j++) {
            fprintf(out, "%.2f ", muchie->costuri[j]);
        }
        fprintf(out, "\n");
    }
}
// functie pentru a determina index a rutelor ce pot fi pastrate
int* extrageRuteDePastrat(Graf* graf,  float Limita, int* numarRutePastrate) {
    int* ruteDePastrat = malloc(graf->numarRute * sizeof(* ruteDePastrat));
    *numarRutePastrate = zero;

    for (int i = zero; i < graf->numarRute; i++) {
        float sumGradeUzura = zero;
        for (int j = zero; j < graf->muchii[i].numar_costuri; j++) {
            // calculam suma
            sumGradeUzura += graf->muchii[i].costuri[j];
        }
        // calculam media
        float mediaCosturi = sumGradeUzura / graf->muchii[i].numar_costuri;
        // media e mai mica decat limita data
        if (mediaCosturi < Limita) {
            ruteDePastrat[(*numarRutePastrate)++] = i;
        }
    }
    return ruteDePastrat;
}
// functie ce elibereaza graful neorientat
void elibereazaGraf(Graf* graf) {
    for (int i = zero; i < graf->numarVarfuri; i++) {
        nodLista* L = graf->lista[i].L;
        while (L) {
            nodLista* temp = L;
            L = L->urmator;
            free(temp->costuri);
            free(temp);
        }
    }
    for (int i = zero; i < graf->numarRute; i++) {
        free(graf->muchii[i].costuri);
    }
    free(graf->muchii);
    free(graf->lista);
    free(graf);
}
int main(int argc, char* argv[]) {
    
    if (argc < doi) {
        return unu;
    }
    // deschidem fisierele
    FILE *in = fopen("tema3.in", "r");
    FILE *out = fopen("tema3.out", "w");
 
    int cerinta = atoi(argv[unu]);
    if (cerinta == unu) {
        // tratam cerinta 1
        int numarRute, ani, gradMax;
        fscanf(in, "%d %d %d", &numarRute, &ani, &gradMax);

        Graf* graf = creeazaGraf(numarRute * doi);

        char sursa[max_char], destinatie[max_char];
        int numar_costuri;
        for (int i = zero; i < numarRute; i++) {
            // numele oraselor sursa si destinatie
            fscanf(in, "%s %s", sursa, destinatie);
            // numarul de grade de uzura pentru fiecare ruta
            fscanf(in, "%d", &numar_costuri);
            float costuri[numar_costuri];
            for (int j = zero; j < numar_costuri; j++) {
                // citim gradele de uzura
                fscanf(in, "%f", &costuri[j]);
            }
            // adaugam muchie in graf
            adaugaMuchie(graf, sursa, destinatie, costuri, numar_costuri);
        }
        // actualizam valorile gradelor de uzura  dupa nu de ani dat
        actualizareGradeUzura(graf, ani);
        int numarRutePastrate;
        int* ruteDePastrat = extrageRuteDePastrat(graf, gradMax, &numarRutePastrate);

        afiseazaGraf(graf, out);
        for (int i = zero; i < numarRutePastrate; i++) {
            // afisam indicii incepand numararea cu 1
            fprintf(out, "%d ", ruteDePastrat[i] + unu);
        }
        // eliberam lista rutelor
        free(ruteDePastrat);
        // eliberam graful
        elibereazaGraf(graf);
    }
    // inchidem fisierele
    fclose(in);
    fclose(out);
    return zero;
}
