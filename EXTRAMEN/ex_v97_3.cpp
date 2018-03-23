//  Fil:  FRODEH \ ALG_METV \ EXTRAMEN \EX_V97_3.CPP

//     L›sningsforslag til eksamen i "Videreg†ende algoritmiske metoder",
//     3.mars 1997, oppgave 3.

//     Laget av Frode Haug, HIG,  mars 1997.
//     Litt endret/modifisert av FrodeH, HiG, h›sten 2003


#include  <iostream>
using namespace std;

const int N = 8;                      // Brettets st›rrelse

int dronninger_paa_kolonne_rad[N+1];  // Indeksen angir kolonne. Tallet i
				      //   "skuffen" nr.'i' angir hvilken
				      //   linje det evnt. st†r en dronning p†.
int minimum_kombinasjon[N+1];         //  Beste minimumskombinasjon hittil.
int min_ant = N+1;                    //  Min.antall dronninger hittil.
int ruter_dekket[N+1][N+1];           //  Brettet med hvor mange dronninger
				      //    som dekker de enkelte ruter.
int ant_ruter_dekket;                 //  Totalt antall ruter p† brettet
				      //    som for ›yeblikket er dekket.

						      int total_n;
                                                      int ant1, ant2;
		 void skriv(char* tekst, int l, int k)  {
		   int i, j;
		   cout << "\n\nMin_ant: " << min_ant
							<< "\nn: " << total_n
			<< "\nLin: " << l << "\tKol: " << k << "\n" << tekst
			<< "\n\t#ruter_dekket: " << ant_ruter_dekket;
		   for (i = 1;  i <= N;  i++)  {
		       cout << "\n\t";
		       for (j = 1;  j <= N;  j++)
			   cout << ruter_dekket[i][j] << ' ';
		   }
		   char ch;  cin >> ch;
		 }

                                     //  Ut fra om pr›ver † plassere en
				     //    dronning i rute[lin][kol], s†
				     //    registreres hvilke ruter denne
				     //    vil dekke opp p† brettet.
				     //    Teller antallet opp eller ned,
				     //    alt ettersom "delta"s verdi.
void registrer_ruter_dekket(int lin, int kol, int delta)  {
   int i, j, m, n;
//			    skriv("FR:", lin, kol);
   for (i = 1;  i <= N;  i++)  {    //  Setter alle p† KOLONNEN som dekket,
	  n = ruter_dekket[i][kol] += delta;  //  ogs† der dronningen plasseres:
	  if (delta == 1   &&  n == 1)  ant_ruter_dekket++; // F›rste som dekker
	  if (delta == -1  &&  n == 0)  ant_ruter_dekket--; // Ingen dekker mer.
       }
   for (j = 1;  j <= N;  j++)      //  Setter alle p† LINJEN som dekket:
       if (j != kol)  {
	  n = ruter_dekket[lin][j] += delta;         // Teller antallet opp/ned.
	  if (delta == 1   &&  n == 1)  ant_ruter_dekket++; // F›rste som dekker
	  if (delta == -1  &&  n == 0)  ant_ruter_dekket--; // Ingen dekker mer.
   }

   for (m = 1, j = kol-1;  j >= 1;  j--, m++)  {   // Diagonalene OPP og NED
       if (lin-m >= 1)  {                          //   til VENSTRE:
	  n = ruter_dekket[lin-m][j] += delta;       // Teller antallet opp/ned.
	  if (delta == 1   &&  n == 1)  ant_ruter_dekket++; // F›rste som dekker
	  if (delta == -1  &&  n == 0)  ant_ruter_dekket--; // Ingen dekker mer.
       }
       if (lin+m <= N)  {                            // Dersom inne p† brettet:
	  n = ruter_dekket[lin+m][j] += delta;       // Teller antallet opp/ned.
	  if (delta == 1   &&  n == 1)  ant_ruter_dekket++; // F›rste som dekker
	  if (delta == -1  &&  n == 0)  ant_ruter_dekket--; // Ingen dekker mer.
       }
   }
//			       skriv("INNI - VESTRE:", lin, kol);
   for (m = 1, j = kol+1;  j <= N;  j++, m++)  {   // Diagonalene OPP og NED
       if (lin-m >= 1)  {                          //   til HYRE:
	  n = ruter_dekket[lin-m][j] += delta;       // Teller antallet opp/ned.
	  if (delta == 1   &&  n == 1)  ant_ruter_dekket++; // F›rste som dekker
	  if (delta == -1  &&  n == 0)  ant_ruter_dekket--; // Ingen dekker mer.
       }
       if (lin+m <= N)  {                            // Dersom inne p† brettet:
	  n = ruter_dekket[lin+m][j] += delta;       // Teller antallet opp/ned.
	  if (delta == 1   &&  n == 1)  ant_ruter_dekket++; // F›rste som dekker
	  if (delta == -1  &&  n == 0)  ant_ruter_dekket--; // Ingen dekker mer.
       }
   }
//			       skriv("INNI - HYRE  /  ETTER:", lin, kol);
}

                                       //  Plasserer dronning nr.'n' p† ALLE
				       //     tenkelige plasser, startende
				       //     ›verst p† kolonne nr.'kolonne'.
void min_ant_dronninger(int kolonne, int n)  {
  int i, j, k;
						 total_n = n;
						 ant1++;
  for (j = kolonne;  j <= N;  j++)     //  G†r gjennom alle aktuelle kolonner:
      for (i = 1;  i <= N;  i++)  {    //  G†r gjennom alle linjer/rader:
						 ant2++;
	  if (n >= min_ant-1)  goto ut;   // Avskj‘ring, umulig † sette rekord.
	  registrer_ruter_dekket(i, j, 1);     //  Registrerer ruter dekket.
	  dronninger_paa_kolonne_rad[j] = i;   //  Hvor settes dronningen.

//						 skriv("INNI:", i, j);
	  if (ant_ruter_dekket == N*N)  {      //  HELE brettet er dekket:
				   //  Un›dvendig med: "if (n < min_ant)" !!
		for (k = 1;  k <= N;  k++)     //  Kopierer best hittil:
		    minimum_kombinasjon[k] =  dronninger_paa_kolonne_rad[k];
		min_ant = n;                   //  Min.antall dronninger.
	  } else
	     min_ant_dronninger(j+1, n+1);     //  Plasserer NESTE dronning.

	  registrer_ruter_dekket(i, j, -1);   //  Stiller tilbake det
	  dronninger_paa_kolonne_rad[j] = 0;  //   dekket/plassert ovenfor.
      }
  ut:     ;   //  NB: Label M etterf›lges av (tom) setning/statement.
}


int main()  {
  min_ant_dronninger(1, 1);
  if (min_ant < N+1)  {
     cout << "\n\nEN kombinasjon:   ";
     for (int j = 1;  j <= N;  j++)
	 cout <<  minimum_kombinasjon[j] << "  ";
     cout << "\n\nMinimum antall dronninger:  " << min_ant;
				   cout << "\nAnt rekursive kall:  " << ant1;
				   cout << "\nAnt for-loopinger:   " << ant2;
  } else
     cout << "Ingen l›sning funnet.";
  cout << "\n\n";
  return 0;
}
