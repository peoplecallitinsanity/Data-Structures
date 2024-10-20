#include "train.h"

int main()
{
    Tren trenulet = initializareTren();
    coadaOperatii *coada = InitQ();

    FILE *TemaIn = fopen("tema1.in", "r");
    if (!TemaIn) {
        return 1;
    }
    FILE *TemaOut = fopen("tema1.out", "w");
    if (!TemaOut) {
        fclose(TemaIn);
        return 1;
    }
    int nrOperatii;
    fscanf(TemaIn, "%d\n", &nrOperatii);
    char linie[max_char];
    for (int i = zero; i < nrOperatii; i++) {
        if (fgets(linie, sizeof(linie), TemaIn)) {
            linie[strcspn(linie, "\n")] = strCheck;
            if (strncmp(linie, "EXECUTE", nrCaractereExecute) == strCheck) {
                EXECUTE(&trenulet, coada, TemaOut );
            } else if (strncmp(linie, "SHOW_CURRENT", nrCaractereShowCurrent)
                == strCheck) {
                SHOW_CURRENT(&trenulet, TemaOut);
            } else if (strncmp(linie, "SHOW", nrCaractereShow) == strCheck) {
                SHOW(&trenulet, TemaOut);
            } else if (strncmp(linie, "SWITCH", nrCaractereSwitch) ==
                strCheck) {
                SWITCH(coada);
            } else {
                addCoadaOperatii(coada, linie);
            }
        }
    }
    // inchidem fisierele tema1.in si tema1.out
    fclose(TemaIn);
    fclose(TemaOut);
    // eliberarea memoriei 
    eliberareCoada(coada);
    eliberareTrenulet(&trenulet);
    return 0;
}
