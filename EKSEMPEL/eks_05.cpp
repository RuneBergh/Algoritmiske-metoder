//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_05.CPP


/*  Denne fil inneholder prim‘rt de seks funksjonene: 
    gen1, gen2, gen3, gen4, gen5 og gen6.
    Totalt utgj›r (og viser) disse hvordan man stegvis kan endre en og samme
    kode, slik at man tilslutt f†r en forholdsvis effektiv og kompakt kode
    for † genererer alle permutasjoner fra 1 til N. Dvs. for † f† en full
    forst†else av utviklingen, s† BR man lese/studere funksjonene i den
    rekkef›lge de forekommer i denne filen (1. steg/utgave  til
    6. steg/utgave).

    gen1 til gen4 genererer stadig nye og h›yere tall. DUPILKATE sifre
    KAN forekomme. gen4 bruker en test (avskj‘ring) slik at vi bare f†r
    skrevet ut de tallene som er en permutasjon av sifrene 1 til N.

    gen5 og gen6 genererer KUN de tallene som er rene permutasjoner av
    sifrene 1 til N.

    NB!  ALLE funksjonene i denne filen genererer stadig nye tall,
	 INGEN av dem stokker bare om p† en allerede eksisterende
	 array med kun ulike sifre. Kode for dette siste tilfellet
	 er † finne i filen EKS_06.CPP.


    gen1 til gen3's output:
      111  112  113  121  122  123  131  132  133
      211  212  213  221  222  223  231  232  233
      311  312  313  321  322  323  331  332  333

    gen4 til gen6's output:
      123  132  213  231  312  321
*/


#include <iostream>

using namespace std;

const int N = 3;                       //  Antall elementer i arrayen

int p[N+1];                            //  Bruker "skuff" nr.1 til N.


void display(int a[])  {               //  Skriver ut innholdet i array 'a'.
  for (int i = 1;  i <= N;  i++)
      cout << a[i];
 cout << "  ";
}



// ***********************   1. STEG/UTGAVE:   ***************************

void gen1();                           //  Deklarasjoner/prototyper:
void gen2();
void gen3();

void gen1()  {                         //  Setter 1, 2 og 3 inn i p[1].
  for (int siff = 1;  siff <= 3;  siff++)  {
    p[1] = siff;
    gen2();             cout << '\n';  //  Ber om at ogs† m† gj›res for p[2].
  }
}

void gen2()  {                         //  Setter 1, 2 og 3 inn i p[2].
  for (int siff = 1;  siff <= 3;  siff++)  {
    p[2] = siff;
    gen3();                            //  Ber om at ogs† m† gj›res for p[3].
  }
}

void gen3()  {                         //  Setter 1, 2 og 3 inn i p[3].
  for (int siff = 1;  siff <= 3;  siff++)  {
    p[3] = siff;
    display(p);                        //  Array er fylt: skriver innholdet.
  }
}



// ***********************   2. STEG/UTGAVE:   ***************************

			     //  Koden i de ulike funksjonene i 1.utgave
			     //  er MEGET lik hverandre. Skriver derfor
			     //  EN (rekursiv) funksjon som kaller seg selv
			     //  dersom 'i' er mindre enn 3, og som skriver
			     //  arrayens innhold dersom 'i' == 3.
void gen2(int i)  {
  for (int siff = 1;  siff <= 3;  siff++)  {
    p[i] = siff;
    if (i < 3)  {
       gen2(i+1);        if (siff == 3) cout << '\n';
    }
    else
       display(p);
  }
}



// ***********************   3. STEG/UTGAVE:   ***************************

			     //  Koden i 2.utgave virker KUN n†r arrayen
			     //  har lengde lik 3. Bytter derfor ut '3' med
			     //  'N', og f†r dermed funksjonen:
void gen3(int i)  {
  for (int siff = 1;  siff <= N;  siff++)  {
    p[i] = siff;
    if (i < N)  {
       gen3(i+1);        if (siff == N) cout << '\n';
    } else
       display(p);
  }
}



// ***********************   4. STEG/UTGAVE:   ***************************

			     //  Hittil har vi f†tt ALLE tallene inneholdene
			     //  sifrene 1, 2 og 3 fra 111 til 333 (tilsammen
			     //  27 stk). Vi vil n† s›rge for at vi KUN f†r
			     //  skrevet ut de tallene (6 stk) som er en
			     //  permutasjon av sifrene 1, 2 og 3. Dette
			     //  gj›r vi ved † avskj‘re utskriften, slik
			     //  at KUN permutasjoner blir skrevet ut.
			     //  ENESTE forandring av denne 4.utgaven ift.
			     //  3.utgaven er bruken av og kallet til
			     //  funksjonen 'ektePermutasjon' i else-grenen.


			     //  Sjekker at 'a' virkelig inneholder en
			     //  permutasjon, dvs. at ingen elementer er like.
bool ektePermutasjon(int a[])  {
  bool brukt[N+1];
  int i;
  for (i = 1;  i <= N;  i++)  brukt[i] = false;     //  Nuller hele hjelpearray.
  for (i = 1;  i <= N;  i++)         //  G†r gjennom hele 'a':
      if (!brukt[a[i]])              //  Sifferet i a[i] er IKKE brukt:
         brukt[a[i]] = true;         //  Setter at N er det brukt.
      else                           //  Sifferet ER brukt:
         return false;
  return true;                       //  Alt gikk OK, dvs. permutasjon.
}


void gen4(int i)  {
  for (int siff = 1;  siff <= N;  siff++)  {
    p[i] = siff;
    if (i < N)  {
       gen4(i+1);
    } else
       if (ektePermutasjon(p))
	  display(p);
  }
}



// ***********************   5. STEG/UTGAVE:   ***************************

			     //  4.utgaven foretar f›rst en avskj‘ring idet
			     //  vi skal foreta utskriften. Dvs. vi f†r
			     //  fortsatt genererert alle tallene med 111 til
			     //  333, men vi skriver kun ut permutasjonene.
			     //  Her i 5.utgaven foretar vi en tidligere
			     //  avskj‘ring slik at vi KUN genererer de N!
			     //  tallene som er permutasjoner. Til dette
			     //  bruker vi en hjelpe-array ('brukt') som
bool brukt[N+1]; //  forteller oss hvilke sifre som allerede er brukt.

void gen5(int i)  {
  for (int siff = 1;  siff <= N;  siff++)
      if (!brukt[siff])  {   //  Sifferet er IKKE brukt:
         brukt[siff] = true; //  Setter at N er det brukt.
         p[i] = siff;
         if (i < N)  {
            gen5(i+1);
         } else
            display(p);
         brukt[siff] = false;    //  Frigir at N er det IKKE i bruk lengre.
      }
}



// ***********************   6. STEG/UTGAVE:   ***************************

			     //  6.utgaven er bare en liten finpussing og
			     //  omskriving av den 5.utgaven, slik at
			     //  vi f†r en egen rekursjons-terminerende
			     //  if-setning. Dermed blir ikke denne liggende
			     //  "dypt" inne i en l›kke som igjen inneholder
			     //   en if-else-setning.
void gen6(int i)  {

  if (i == N+1)              //  En ny permutasjon er ferdig:
     display(p);
  else  {
     for (int siff = 1;  siff <= N;  siff++)  {
	 if (!brukt[siff])  {
	    brukt[siff] = true;
	    p[i] = siff;
	    gen6(i+1);
	    brukt[siff] = false;
	 }
     }
  }
}

// ***********************   7. STEG/UTGAVE    ****************************

//  Dette steget:
//    - er et TANKEMESSIG steg mot ny l‘ring, modning og forst†else.
//    - forekommer oppe i ditt eget hode.
//    - gj›r at steg 1 til 6 er intuitivt evident
//      (dvs. umiddelbart, selvinnlysende klart).
//    - medf›rer at ALT ER BARE GREIT !!



// ***********************    HOVEDPROGRAM:    ***************************

int main() {
  int i;
  char ch;

  cout << "Bruker 'gen1', 'gen2' og 'gen3':\n";
  gen1();

  cin >> ch;   cout << "\nBruker 'gen2':\n";
  gen2(1);

  cin >> ch;   cout << "Bruker 'gen3':\n";
  gen3(1);

  cin >> ch;   cout << "Bruker 'gen4':\n";
  gen4(1);

  cin >> ch;   cout << "\n\nBruker 'gen5':\n";
  for (i = 1;  i <= N;  i++)  brukt[i] = false;       // Resetter hjelparray.
  gen5(1);

  cin >> ch;   cout << "\n\nBruker 'gen6':\n";
  for (i = 1;  i <= N;  i++)  brukt[i] = false;       // Resetter hjelparray.
  gen6(1);
  
  cout << "\n\n";
  return 0;
}
