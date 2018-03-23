//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_J97_3.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder (I)",
//     24.februar 1997, oppgave 3.

//     Laget av Frode Haug, HIG,  februar 1997.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include <iostream>
using namespace std;


const int ANT_ELEM = 6;       //  Antall elementer i listen.

struct element  {             //  Listens elementer.
  int id;
  element* next;
};


void lag_liste();
void skriv_liste(element* rot);
void skriv_baklengs(element* liste);
void slett_bakfra(element* & liste);
element* kopier_liste(element* liste);
void snu_liste(element* & hode, element* liste, element* forrige);


element* start, * kopi;       //  Pekere til to ulike lister.


int main()  {
  lag_liste();
  cout << "\n\nOrginal liste:      ";   skriv_liste(start);
  cout << "\n\nSkrevet baklengs:   ";   skriv_baklengs(start);
  cout << "\n\nKopierer:           ";   kopi = kopier_liste(start);    skriv_liste(kopi);
  cout << "\n\nInverterer/snur:    ";   snu_liste(start, start, NULL); skriv_liste(start);
				 cout << "\n\nSkrevet baklengs:   ";   skriv_baklengs(start);
  cout << "\n\nSletter bakfra 1:   ";	slett_bakfra(start);           skriv_liste(start);
  cout << "\n\nSletter bakfra 2:   ";	slett_bakfra(kopi);            skriv_liste(kopi);
  cout << "\n\n";
  return 0;
}

void lag_liste()  {           //  Bygger opp en liste med "ANT_ELEM" elementer.
  element* temp;
  start = NULL;
  for (int i = ANT_ELEM; i >= 1;  i--)  {
     temp = new element;   temp->id = i;
     temp->next = start;  start = temp;
  }
}


void skriv_liste(element* rot) {    // Skriver liste ut vanlig:
  element* pek = rot;
  while (pek != NULL)  {
     cout << pek->id << "  ";
     pek = pek->next;
  }
}


void skriv_baklengs(element* liste)  {   // Skriver liste REKURSIVT baklengs:
  if (liste != NULL)  {                  //  Ikke kommet til listens ende:
     skriv_baklengs(liste->next);        //  Skriv neste element.
     cout << liste->id << "  ";          //  Skriv en selv.
  }
}


void slett_bakfra(element* & liste)  {   // Sletter liste REKURSIVT bakfra:
  if (liste != NULL)  {                  //  Ikke kommet til listens ende:
     slett_bakfra(liste->next);          //  Sletter neste element.
     delete liste;  liste = NULL;        //  Sletter en selv.
  }                                      //    Den som refererer til en
}                                        //     ("forrige"->next) blir
					 //     nullstilt.


element* kopier_liste(element* liste)  {   //  Kopierer liste REKURSIVT:
   if (liste != NULL)  {                   //  Ikke kommet til listens ende:
      element* temp = new element;         //  Lager nytt element.
      temp->id = liste->id;                //  Kopierer ID'en.
      temp->next = kopier_liste(liste->next);   //  Kopiens "next" peker til
						//   kopi av resten av lista.
      return temp;                         //  Returnerer kopien.
   } else return NULL;                     //  Slutt, derfor returnerer NULL.
}

				  //  Snur/inverterer liste rekursivt:
void snu_liste(element* & rot, element* liste, element* forrige)  {
  if (liste != NULL)  {                    //  Ikke kommet til listens ende:
     snu_liste(rot, liste->next, liste);   //  Neste skal peke til en selv.
     if (liste->next == NULL)  rot = liste;  // Siste element, derfor ny
					     //   liste-start.
     liste->next = forrige;                // Snur pekeren.
  }
}
