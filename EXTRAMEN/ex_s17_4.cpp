//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_S17_4.CPP

//  Løsningforslag til kontinuasjonseksamen i Alg.met, august 2017, oppgave nr.4.
//  Laget av Frode Haug, NTNU


//  Program som "kapper"/deler et tall A i to deler: B og C.
//  Summen av tallene B og C og deretter kvadrert er tallet A.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>             //  cout
#include <cstring>              //  strlen
#include <cstdlib>              //  atoi,  _itoa
#include <iomanip>              //  setw
using namespace std;

const int MAX = 1000000;        //  Sjekke opp til dette tallet.
                                //  (Øk til 10 mill for å se hastighets-
                                //    forskjellen på Alt.1 og Alt.2.)

int main() {
    int i, j, del1, del2;           //  Løkkevariable og talldel 1 og 2.

                                    // ALTERNATIV 1 (raskest):
    cout << "\n\nUtregnet ved bruk av '/' og '%':\n";
    int div;                                //  Divisor.
    for (i = 10; i < MAX; i++) {            //  Går gjennom ALLE tallene:
        div = 10;                           //  10 er start for '/' og '%'.
        while (div <= i) {                  //  Så lenge sifre igjen ved '/':
            del1 = i / div;                 //  Henter fremre tall/del.
            del2 = i % div;                 //  Henter bakre tall/del.
            if ((del1 + del2) * (del1 + del2) == i)  //  Rett sum av kvadrater?
                cout << setw(10) << i << "  =  ( " << setw(3) << del1
                     << " + " << setw(3) << del2 << " ) ** 2\n";
            div *= 10;                      //  En tierpotens høyere.
        }
    }

                                    // ALTERNATIV 2 (litt mindre effektiv):
    cout << "\n\nUtregnet ved bruk av subtekst og tallkonvertering:\n";
    char tall[10], tallDel[10];          //  HELE tallet og fremre tall/del.
    int len;                             //  Antall sifre i tallet.
    for (i = 10; i < MAX; i++) {         //  Går gjennom ALLE tallene:
        _itoa(i, tall, 10);              //  Konverterer tall til tekst.
        len = strlen(tall);              //  Lagrer tekstens lengde.
        for (j = 1; j < len; j++) {      //  Gjennomgår NESTEN hele teksten:
            strncpy(tallDel, tall, j);   //  Tekstkopierer fremre del/tall.
            tallDel[j] = '\0';           //  Må legge manuelt til '\0'(!)
            del1 = atoi(tallDel);        //  Fremre del omgjøres til tall.
            del2 = atoi(tall + j);       //  Bakre del omgjøres til tall. 
            if ((del1 + del2) * (del1 + del2) == i)  //  Rett sum av kvadrater?
                cout << setw(10) << i << "  =  ( " << setw(3) << del1
                     << " + " << setw(3) << del2 << " ) ** 2\n";
        }
    }

    cout << "\n\n";
    return 0;
}
