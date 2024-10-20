
#include "train.h"

//Initializam trenuletul cu conditiile initiale
Tren initializareTren()
{
    Tren trenulet;
    trenulet.locomotiva = NULL;
    trenulet.mecanic = NULL;
    Vagon *locomotiva = malloc(sizeof(*locomotiva));
    Vagon *vagon = malloc(sizeof(*vagon));
    // Verificam alocarea
    if (!locomotiva || !vagon) {
        // Eliberam memoria alocata anterior in caz de eroare la alocare
        free(locomotiva);
        free(vagon);
        return trenulet;
    }
    // initializam campurile structurilor
    trenulet.mecanic = vagon;
    trenulet.locomotiva = locomotiva;
    vagon->inscriptie = InscriptieDefault;
    // legaturile pentru lista circulara
    locomotiva->urm = vagon;
    locomotiva->ant = vagon;
    locomotiva->inscriptie = InscriptieLocomotiva;
    // legaturile dintre vagon si locomotiva
    vagon->ant = locomotiva;
    vagon->urm = locomotiva;

    return trenulet;
}

// Initializam coada
coadaOperatii *InitQ()
{   
    // alocam o structura de tip coadaOperatii
    coadaOperatii *coada = malloc(sizeof(*coada));
    if (!coada) {
        return NULL;
    }
    coada->sf = coada->inc = NULL;
    return coada;
}

void addCoadaOperatii(coadaOperatii *coada, char *nume)
{
    /* alocam o celula de tip celulaOperatie in care
    retinem operatiile date */
    celulaOperatie *operatie = malloc(sizeof(*operatie));
    if (!operatie) {
        return;
    }
    // copiem numele operatiei in campul nume
    strcpy(operatie->nume, nume);
    // setam sfarsitull operatiei/cozii
    operatie->urm = NULL;
    if (coada->sf) { // daca coada nu este goala
        coada->sf->urm = operatie; // adaugam operatia la sfarsit
        coada->sf = operatie;
    } else { // daca coada este goala
        coada->inc = coada->sf = operatie;
    }
}

// Executarea operatiilor
void EXECUTE(Tren *tren, coadaOperatii *coada, FILE *TemaOut)
{   
    /* aceasta functie apeleaza operatiile in dependenta de inputul din
    fisier, recunoscand numele functiei date ca input.
    */
    if (!coada->inc) {
        return; // daca nu avem operatii in coada, iesim
    }
    
    celulaOperatie *operatie = coada->inc;
     // sarim peste operatia care urmeaza a fi executata
    coada->inc = operatie->urm;
     // daca coada a devenit goala, setam sfarsitul si coada-NULL
    if (!coada->inc) {
        coada->sf = NULL;
        coada = NULL;
    }
    // apelam functia necesara prin gasirea secventei de caractere date
    if (strncmp(operatie->nume, "MOVE_LEFT", nrCaractereMoveLeft) == strCheck) {
        MOVE_LEFT(tren);
    } else if (strncmp(operatie->nume, "MOVE_RIGHT", nrCaractereMoveRight)
        == strCheck) {
        MOVE_RIGHT(tren);
    } else if (strncmp(operatie->nume, "WRITE ", nrCaractereWrite)
        == strCheck) {
        char inscriptie_noua = operatie->nume[nrCaractereWrite];
        WRITE(tren, inscriptie_noua);
    } else if (strncmp(operatie->nume, "CLEAR_CELL", nrCaractereClearCell)
        == strCheck) {
        CLEAR_CELL(tren);
    } else if (strncmp(operatie->nume, "CLEAR_ALL", nrCaractereClearAll)
        == strCheck) {
        CLEAR_ALL(tren);
    } else if (strncmp(operatie->nume, "INSERT_LEFT ", nrCaractereInsertLeft)
        == strCheck) {
        char inscriptie_noua = operatie->nume[nrCaractereInsertLeft];
        if (INSERT_LEFT(tren, inscriptie_noua)) fprintf(TemaOut, "ERROR\n");
    } else if (strncmp(operatie->nume, "INSERT_RIGHT ", nrCaractereInsertRight)
        == strCheck) {
        char inscriptie_noua = operatie->nume[nrCaractereInsertRight];
        INSERT_RIGHT(tren, inscriptie_noua);
    } else if (strncmp(operatie->nume, "SEARCH ", nrCaractereSearch)
        == strCheck) {
        char *sirCautat = operatie->nume + nrCaractereSearch;
        Search_struct *search = SEARCH(tren, sirCautat);
        if (!search->sirGasit) fprintf(TemaOut, "ERROR\n");
        free(search);
    } else if (strncmp(operatie->nume, "SEARCH_LEFT ", nrCaractereSearchLeft)
        == strCheck) {
        char *sirCautat = operatie->nume + nrCaractereSearchLeft;
        Search_struct *search = SEARCH_LEFT(tren, sirCautat);
        if (!search->sirGasit) fprintf(TemaOut, "ERROR\n");
        free(search);
    } else if (strncmp(operatie->nume, "SEARCH_RIGHT ", nrCaractereSearchRight)
        == strCheck) {
        char *sirCautat = operatie->nume + nrCaractereSearchRight;
        Search_struct *search = SEARCH_RIGHT(tren, sirCautat);
        if (!search->sirGasit) fprintf(TemaOut, "ERROR\n");
        free(search);
    } else {
        return;
    }
    free(operatie);
}

// Operatii de tip UPDATE
void MOVE_LEFT(Tren *tren)
{
    // daca in stanga mecanicului se afla locomotiva
    if (tren->mecanic->ant == tren->locomotiva) {
        // mutam mecanicul in ultimul vagon
        tren->mecanic = tren->locomotiva->ant;
    } else {
        // daca nu - mutam mecanicul in vagonul anterioara
        tren->mecanic = tren->mecanic->ant;
    }
}

void MOVE_RIGHT(Tren *tren)
{
    if (tren->mecanic->urm == tren->locomotiva) { //daca e in ultimul vagon
        // alocam memorie pentru un vagon nou
        Vagon *new_vagon = malloc(sizeof(*new_vagon));
        if (!new_vagon) {
            return;
        }
        // initializam vagonul
        new_vagon->inscriptie = InscriptieDefault;
        Vagon *anterior = tren->locomotiva->ant;
        // campul ant al noului vagon pointeaza catre vagonul anterior
        new_vagon->ant = anterior;
        new_vagon->urm = tren->locomotiva;
        // campul urm a ultimului vagon din tren va pointa catre noul vagon
        tren->locomotiva->ant->urm = new_vagon;
        tren->locomotiva->ant = new_vagon;
        tren->mecanic = new_vagon; //mutam mecanicul in noul vagon
    } else {
        // daca nu suntem in ultimul vagon mutam mecanicul in urmatorul
        tren->mecanic = tren->mecanic->urm;
    }
}

void WRITE(Tren *tren, char inscriptie)
{
    // aceasta functie adauga caracterul dat in campul inscriptie al unui vagon
    tren->mecanic->inscriptie = inscriptie;
}

void CLEAR_CELL(Tren *tren)
{
    // daca exista un singur vagon revenim la starea initiala
    // (schimbam inscriptia)
    if (tren->mecanic->ant == tren->locomotiva &&
        tren->mecanic->urm == tren->locomotiva) {
        WRITE(tren, InscriptieDefault);

    } else { //daca sunt mai mult de un vagon in tren
        // eliberam vagon in care se afla mecanicul
        Vagon *vagon_free = tren->mecanic;
        vagon_free->ant->urm = vagon_free->urm;
        vagon_free->urm->ant = vagon_free->ant;
        //daca eliminam primul vagon, dar nu e singurul
        if (vagon_free->ant == tren->locomotiva) {
            tren->locomotiva->urm = vagon_free->urm;
        }
        // mutare in vagonul din stanga (ultimul)
        MOVE_LEFT(tren);
        free(vagon_free);
    }
}

void CLEAR_ALL(Tren *tren)
{   
    // incepem cu vagonul nr 2
    Vagon *vagon = tren->locomotiva->urm->urm;
    while (vagon != tren->locomotiva) {
        // eliberam toate vagoanele pana ajungem la locomotiva
        Vagon *vagon_free = vagon;
        vagon = vagon->urm;
        free(vagon_free);
    }
    
    Vagon *primulVagon = tren->locomotiva->urm;
    // setam sfarsitul trenului (primul vagon) sa pointeze catre locomotiva
    tren->locomotiva->urm->urm = tren->locomotiva;
    // setam mecanicul in primul vagon
    tren->mecanic = primulVagon;
    // resetam inscriptia
    WRITE(tren, InscriptieDefault);
}

int INSERT_LEFT(Tren *tren, char inscriptie)
{
    // daca mecanicul e in vagonul 1
    if (tren->mecanic == tren->locomotiva->urm) {
        // returnam 1 pentru a putea printa ERROR in fisier
        return 1;
    }
    // daca nu e in primul vagon, alocam memorie pentru un vagon
    Vagon *new_vagon = malloc(sizeof(*new_vagon));
    if (!new_vagon) return 0;
    // stabilim legaturile cu vagonul in fata caruia inseram
    new_vagon->urm = tren->mecanic;
    new_vagon->ant = tren->mecanic->ant;
    tren->mecanic->ant->urm = new_vagon;
    tren->mecanic->ant = new_vagon;
    // mutam mecanicul in noul vagon inserat
    MOVE_LEFT(tren);
    // setam inscriptia noului vagon
    WRITE(tren, inscriptie);
    return 0;
}

void INSERT_RIGHT(Tren *tren, char inscriptie)
{   
    // putem mereu insera in dreapta, deci alocam memorie pentru vagon
    Vagon *new_vagon = malloc(sizeof(*new_vagon));
    if (!new_vagon) return;
    // daca inseram la sfarsitul trenului, actualizam legatura cu locomotiva
    if (tren->mecanic == tren->locomotiva->ant) {
        new_vagon->urm = tren->locomotiva;
        tren->locomotiva->ant = new_vagon;
    } else {
        // daca nu inseram la sfarsit, stabilim legatura cu urmatorul vagon
        new_vagon->urm = tren->mecanic->urm;
    }
    // stabilim legaturile pentru a mentine lista circulara dublu inlantuita
    new_vagon->ant = tren->mecanic;
    tren->mecanic->urm = new_vagon;
    // mutam mecanicul in noul vagon
    MOVE_RIGHT(tren);
    WRITE(tren, inscriptie);
}

void SHOW(Tren *tren, FILE *TemaOut)
{   
    /* aceasta functie printeaza inscriptiile din vagoanele unui tren
    si marcheaza pozitia mecanicului cu ajutorul |inscriptie|
    */
    Vagon *vagon = tren->locomotiva->urm;
    // parcurgem trenul pana ajungem la locomotiva
    while (vagon != tren->locomotiva) {
        if (vagon == tren->mecanic) {
            // daca mecanicul se afla in vagonul dat, il marcam
            fprintf(TemaOut, "|%c|", vagon->inscriptie);
        } else {
            fprintf(TemaOut, "%c", vagon->inscriptie);
        }
        vagon = vagon->urm;
    }
    fprintf(TemaOut, "\n");
}

// Operatii de tip SEARCH
Search_struct *SEARCH(Tren *tren, char *sirCautat)
{
    // inlocuim caracterul de "carriage return" cu '\0'
    int lenSir = strcspn(sirCautat, "\r");
    sirCautat[lenSir] = '\0';
    if (lenSir == zero) return NULL; // daca avem un sir gol
    Vagon *primulVagon = tren->mecanic;
    Vagon *verifica;
    // initializam o structura pentru a pastra rezultatele
    Search_struct *rezultat = malloc(sizeof(*rezultat));
    if (!rezultat) return NULL;
    rezultat->caractereGasite = zero;
    rezultat->sirGasit = false;
    int iteratie = unu;
    // atat timp cand nu am gasit sirul si nu am ajuns inapoi la mecanic
    // sau suntem la prima iteratie (vagonul in care este mecanicul)
    while ((primulVagon != tren->mecanic && !rezultat->sirGasit) || iteratie == unu) {
        iteratie++;
        // daca gasim prima inscriptie potrivita
        if (primulVagon->inscriptie == sirCautat[zero]) {
            rezultat->caractereGasite = unu;
            // daca urmatorul vagon este locomotiva, trecem la primul vagon
            if (primulVagon->urm == tren->locomotiva)
                verifica = primulVagon->urm->urm;
            // daca nu, verificam vagonul urmator
            else verifica = primulVagon->urm;
            // daca gasim urmatoarele caractere
            while ( rezultat->caractereGasite < lenSir && verifica != tren->mecanic &&
                verifica->inscriptie == sirCautat[rezultat->caractereGasite]) {
                // incrimentam nr de caractere gasite
                rezultat->caractereGasite++;
                // trecem la urmatorul vagon
                verifica = verifica->urm;
            }
            if (rezultat->caractereGasite == lenSir) { // daca gasim secventa
                // mutam mecanicul in primul vagon
                tren->mecanic = primulVagon;
                // setam campul sirGasit adevarat
                rezultat->sirGasit = true;
                break;
            }
        }
        // daca nu am gasit primul caracter, trecem la urmatorul vagon
        primulVagon = primulVagon->urm;
    }
    // returnam structura rezultat
    return rezultat;
}



Search_struct *SEARCH_LEFT(Tren *tren, char *sirCautat)
{
    // inlocuim caracterul de "carriage return" cu '\0'
    int lenSir = strcspn(sirCautat, "\r");
    sirCautat[lenSir] = '\0';
    if (lenSir == zero) return NULL; // daca avem un sir gol
    Vagon *primulVagon = tren->mecanic;
    Vagon *verifica;
    // initializam o structura pentru a pastra rezultatele
    Search_struct *rezultat = malloc(sizeof(*rezultat));
    if (!rezultat) return NULL;
    rezultat->caractereGasite = zero;
    rezultat->sirGasit = false;
    // atat timp cat nu am ajuns la locomotiva si nu am gasit sirul cautat
    while (primulVagon != tren->locomotiva && !rezultat->sirGasit) {
        //daca gasim primul caracter
        if (primulVagon->inscriptie == sirCautat[zero]) {
            rezultat->caractereGasite = unu;
            //verificam vagoanele anterioare
            verifica = primulVagon->ant;
            while (rezultat->caractereGasite < lenSir && verifica != tren->mecanic &&
                verifica->inscriptie == sirCautat[rezultat->caractereGasite]) {
                // daca gasim caracterele necesare, incrimentam nr de caractere gasite
                rezultat->caractereGasite++;
                // trecem la vagonul anterior, spre stanga
                verifica = verifica->ant;
            }
            if (rezultat->caractereGasite == lenSir) { // daca gasim secventa cautata
                tren->mecanic = verifica->urm;
                // mutam mecanicul in casuta urmatoare a vagonului curr
                rezultat->sirGasit = true;
                break;
            }
        }
        // parcurgem in stanga daca nu am gasit primul caracter
        primulVagon = primulVagon->ant;
    }
    // returnam structura
    return rezultat;
}

Search_struct *SEARCH_RIGHT(Tren *tren, char *sirCautat)
{
    int lenSir = strcspn(sirCautat, "\r");
    sirCautat[lenSir] = '\0';
    if (lenSir == zero) return NULL; // daca avem un sir gol
    Vagon *primulVagon = tren->mecanic;
    Vagon *verifica;
    // declaram o structura in care vom tine rezultatele
    Search_struct *rezultat = malloc(sizeof(*rezultat));
    if (!rezultat) return NULL;
    rezultat->caractereGasite = zero;
    rezultat->sirGasit = false;
    // atat timp cat nu am ajuns la locomotiva si nu am gasit sirul cautat
    while ((primulVagon != tren->locomotiva && !rezultat->sirGasit)) {
        // daca gasim primul caracter din sir
        if (primulVagon->inscriptie == sirCautat[zero]) {
            rezultat->caractereGasite = unu;
            verifica = primulVagon->urm;
            // verificam potrivirea restului de caractere 
            while (rezultat->caractereGasite < lenSir && verifica != tren->locomotiva &&
                verifica->inscriptie == sirCautat[rezultat->caractereGasite]) {
                // daca gasim alt caracter, incrimentam nr de caractere gasite
                rezultat->caractereGasite++;
                // trecem la urmatorul vagon
                verifica = verifica->urm;
            }
            // daca am gasit secventa
            if (rezultat->caractereGasite == lenSir) {
                // mutam mecanicul in vagonul anterior (ultimul caracter gasit)
                tren->mecanic = verifica->ant;
                rezultat->sirGasit = true;
                break;
            }
        }
        // daca nu gasim primul caracter, trecem la urmatorul vagon
        primulVagon = primulVagon->urm;
    }
    // returnam structura
    return rezultat;
}


void SHOW_CURRENT(Tren *tren, FILE *TemaOut)
{
    /* aceasta functie printeaza valoare din campul inscriptie
    din vagonul in care se afla mecanicul
    */
    fprintf(TemaOut, "%c\n", tren->mecanic->inscriptie);
}

void SWITCH(coadaOperatii *coada)
{   
    /* aceasta functie inverseaza coada de operatii  */
    if (!coada->inc || coada->inc == coada->sf || !coada->sf) {
        return; // nu inversam daca in coada este una sau nici o operatie
    }

    celulaOperatie *ant = NULL;
    celulaOperatie *operatie = coada->inc;
    celulaOperatie *urm = NULL;
    
    coada->sf = coada->inc; // sfarsitul va fi vechiul inceput

    while (operatie) {
        urm = operatie->urm; // pastram operatia urmatoare
        operatie->urm = ant; // inversam legaturile
        ant = operatie; // mutam ant inainte
        operatie = urm;
    }

    coada->inc = ant; // inceputul cozii va fi sfarsitul cozii initiale
}

void eliberareTrenulet(Tren *trenulet)
{
    // aceasta functie elibereaza structurile alocate anterior 
    // care au fost folosite pentru contruirea trenului
    if (!trenulet) {
        return;
    }
    // incepem cu primul vagon dupa locomotiva
    Vagon *vagon = trenulet->locomotiva->urm;
    while (vagon != trenulet->locomotiva) {
        Vagon *eliberat = vagon;
        vagon = vagon->urm;
        free(eliberat);
    }
    // dupa ce am eliberat toate vagoanele, eliberam locomotiva
    free(trenulet->locomotiva);
    trenulet->locomotiva = NULL;
    trenulet->mecanic = NULL;
}

void eliberareCoada(coadaOperatii *operatii)
{
    /* aceasta functie elibereaza coada de operatii
    */
    if (!operatii) {
        return;
    }
    // incepem cu prima operatie din coada
    celulaOperatie *operatie = operatii->inc;
    while (operatie) {
        // cat timp exista o operatie in coada parcurgem coada
        celulaOperatie *eliberat = operatie;
        operatie = operatie->urm;
        // eliberam operatia anterioara
        free(eliberat);
    }
    // distrugem si coada de operatii
    free(operatii);
}


