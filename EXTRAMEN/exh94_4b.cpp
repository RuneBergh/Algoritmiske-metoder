//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EXH94_4B.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     desember 1994, oppgave 4b.

//     Laget av Frode Haug, HIG, h›sten 1994.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003



//  Ved uttesting av ulike tilfeller m† f›lgende gj›res.
//     - editere filen 'GATER.DTA'.
//     - endre start- og sluttkryss (linjene 63 og 64).
//     - endre aktuell h›yde for kj›ret›yet/transporten (linje 96).


#include <iostream>          //  INCLUDE:
#include <fstream>
using namespace std;


			     //  CONST:
const int UNSEEN = 0;
const int SEEN   = 1;
			     //  STRUCT:
struct kryss  {
  char navn[80];             //  Gatekryssets navn.
  int ant_gater;             //  Antall utg†ende gater fra krysset (1-6 stk.)
  struct kryss* gate[7];     //  Referanse til andre kryss, dvs.gatene/kantene
			     //    til disse. Vi bruker indeksene 1-6.
  float         mh[7];       //  Maksimum h›yde for gatene ut fra krysset.
  int merke;                 //  Om krysset er (UN)SEEN til n†.

  kryss()  {  merke = UNSEEN;  }    //  Constructor.
};

			     //  GLOBALE VARIABLE:
kryss *gatenett, *start, *slutt;

			     //  FUNKSJONER:
			     //  Leser inn (fra fil) og oppretter
			     //    datastrukturen.
void les_fra_fil()  {
   ifstream innfil("GATER.DTA");
   int i, j, ant_kryss, nr, kryss_nr;

   innfil >> ant_kryss;      //  Leser antall kryss/noder.
   kryss** A = new kryss*[ant_kryss+1]; // A er en hjelpe-array av pekere til
					//   noder. Brukes til opprettelse
					//   av datastrukturen.
   for (i = 1;  i <= ant_kryss;  i++)   // Initierer arrayen med "tomme" kryss
      A[i] = new kryss();

   for (i = 1;  i <= ant_kryss;  i++)  { //  Fyller alle kryssene med data
       innfil >> nr;                     //    fra filen.
       innfil >> A[nr]->navn;            //  Kryssets navn.
       innfil >> A[nr]->ant_gater;       //  Antall gater ut fra krysset.
       for (j = 1;  j <= A[nr]->ant_gater;  j++)  {    //  Leser alle gatene:
	 innfil >> A[nr]->mh[j];         //  H›yden i gaten.
	 innfil >> kryss_nr;             //  Hvilket kryss gaten g†r til.
	 A[nr]->gate[j] = A[kryss_nr];   //  Oppretter link til krysset.
       }
   }
   start = A[3];             //  SETTER OPP GLOBALE "START" og "SLUTT".
   slutt = A[4];
   gatenett = A[1];                      //  Hekter grafen til 'gatenett'.
   for (i = 1;  i <= ant_kryss;  i++)    //  L›sriver kryssene fra 'A'.
       A[i] = NULL;
   delete [] A;                           //  Sletter hjelpe-arrayen.
}


			     //  Eksamensoppgaven:
bool muligvei(struct kryss* fra, struct kryss* til, float h)  {
  int t;
  bool ferdig = false;

  fra->merke = SEEN;           //  N† er 'fra' bes›kt (for † hindre cykler).
  if (fra != til)  {           //  Ikke n†dd fram.
     for (t = 1;  t <= fra->ant_gater;  t++)  {  //  For alle naboene:
						 //  Mulig † bes›ke naboen:
	 if (fra->gate[t]->merke == UNSEEN  &&  h <= fra->mh[t])
	    ferdig = muligvei(fra->gate[t], til, h); //  Bes›ker nabokrysset.
	 if (ferdig) break;    //  N†dd fram, dvs. ferdig. G†r ut av l›kke
     }                         //    og n›ster bakover i rekursjonen.
  } else ferdig = true;        //  N†dd fram til aktuelt kryss.

  if (ferdig) cout << fra->navn << "  ";   //  Skriver navnet p† vei tilbake.

  fra->merke = UNSEEN;  // 'Fra' er ferdig behandlet (i denne omgang) og
			//    andre kan bes›ke den senere (via andre gater).
  return ferdig;        //  Returnerer om ferdig (true) eller ei (false).
}


int main ()  {              //  HOVEDPROGRAM:
  float hoyde = 3.5;                   //  Aktuell h›yde for kj›ret›y.

  les_fra_fil();                       //  Oppretter datastrukturen.
  bool mulig = muligvei(start, slutt, hoyde);   //  Finner mulig vei ?
  if (!mulig) cout << "Ikke mulig † finne en kj›rbar vei fra "
		   << start->navn << " til " << slutt->navn
		   << " med h›yden " << hoyde << '.';
  cout << "\n\n";
  return 0;
}

