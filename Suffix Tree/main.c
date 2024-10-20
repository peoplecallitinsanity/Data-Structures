/* PULBERE Vlada - 312CB */
#include "tema2.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }
    char *comanda = argv[1];

    Nod *radacina = creeazaNod();
    
    // executarea primei comenzi
    if (strcmp(comanda, "-c1") == zero) {
        char *nume_fisier_intrare = argv[2];
        char *nume_fisier_iesire = argv[3];
        // deschidem fisierele
        FILE *intrare = fopen(nume_fisier_intrare, "r");
        FILE *iesire = fopen(nume_fisier_iesire, "w");
        int N;
        fscanf(intrare, "%d ", &N);
        char cuvant[max_cuvant];
        // parcurgem pana la nr de cuvinte
        for (int i = zero; i < N; i++) {
            fscanf(intrare, "%s", cuvant);
            // adaugam $ la sfarsit
            strcat(cuvant, "$");
            // parcurgem pana la \0 cuvintele
            for (int i = zero; cuvant[i] != term; i++) {
                adauga_sufix(radacina, cuvant + i);
            }
        }
        print_tree(radacina, iesire);
        // inchidem fisierele
        fclose(intrare);
        fclose(iesire);
    } else if (strcmp(comanda, "-c3") == zero) {
        // executam comanda 3
        char *nume_fisier_intrare = argv[2];
        char *nume_fisier_iesire = argv[3];
        // deschidem fisierele
        FILE *intrare = fopen(nume_fisier_intrare, "r");
        FILE *iesire = fopen(nume_fisier_iesire, "w");
        int N, M;
        // salvam numarul de cuvinte si de sufixe
        fscanf(intrare, "%d ", &N);
        fscanf(intrare, "%d ", &M);
        char cuvant[max_cuvant];
    
        for (int i = zero; i < N; i++) {
            fscanf(intrare, "%s", cuvant);
            strcat(cuvant, "$");
            for (int i = zero; cuvant[i] != term; i++) {
                adauga_sufix(radacina, cuvant + i);
            }
        }

        for (int j = zero; j < M; j++) {
            fscanf(intrare, "%s", cuvant);
            // verificam daca exista exista sufixul
            if (verificaSufix(radacina, cuvant)) {
                fprintf(iesire, "%d\n", unu);
            } else {
                fprintf(iesire, "%d\n", zero);
            }    
        }
        fclose(intrare);
        fclose(iesire);
    }
    

    free_tree(radacina);
    return 0;
}
