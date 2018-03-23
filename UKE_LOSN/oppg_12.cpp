//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_12.CPP

//   L›sningsforslag til oppgave nr.12  i  Algoritmiske metoder.


#include <iostream>          //  cout
#include <cstdlib>           //  exit

using namespace std;


const int N = 33;            //  32 land (indeks 1-32).

int felles[N][N];            //  Land i og j er naboer:  felles[i][j] == 1.
int farge[N];                //  Angir land nr.i's farge.
			                 //  Da begge er globale, s† blir alle
			                 //    elementene automatisk satt til '0'.

void initierFelles();        //  Definisjon av funksjon.


void fargelegg(int i)  {     //  Fargelegg land nr.'i'.
  if (i < N)  {              //  Alle landene er enn† ikke fargelagt:
     int f, j;               //  'f' er farge-teller.
			                 //  'j' er potensielt naboland til 'i'.
     int brukt[5];           //  Holder orden p† hvilke farger (1-4) som
			                 //    allerede er brukt av naboland.
     for (f = 1;  f <= 4;  f++)   brukt[f] = 0;   //  Initierer denne til '0'.
     for (j = 1;  j < i;   j++)   //  G†r gjennom alle potensielle naboland
	 if (felles[i][j])  brukt[farge[j]] = 1;  //  og setter at fargene
						                      //  deres allerede er brukt.
     for (f = 1;  f <= 4;  f++)   //  G†r gjennom de fargene som finnes:
	 if (!brukt[f])  {            //  Dersom ikke brukt allerede:
	  farge[i] = f;               //  Setter at n† bruker land nr.'i' denne.
	  fargelegg(i + 1);           //  Ber neste land pr›ve † fargelegge seg.
	  farge[i] = 0;               //  "Blanker ut" landets farge igjen.
     }
  } else {                        //  Alle landene er ferdig fargelagt:
      cout << "\n\nETT forslag:\n";      //  Skriver landenes farger:
      for (int i = 1;  i < N; i++)  {
	      if (i % 2)  cout << '\n';
	         cout << "\tLand nr." << i << " har farge nr." << farge[i];
	  }
	  cout << "\n\n";
      exit(0);
  }
}


// ************************   HOVEDPROGRAM:   ****************************

int main()  {
  initierFelles();          //  Setter opp naboland-matrisen.

  fargelegg(1);              //  Fargelegg landene, start med nr.1.

  cout << "\n\nIngen fargelegging funnet !!"       // Om l›sning blir funnet,
       << "\nFeil i felles-grense-tabellen ?\n\n"; //   s† kommer man ALDRI
                                                   //   hit (pga. "exit(0)").
  return 0;
}

			     //  Setter opp naboland-matrisen, der elementet
			     //    (i,j) og (j,i) settes til 1 om landene
void initierFelles()  {     //    i og j er naboer (jfr. Europakart).
 felles[2][3]   =  felles[3][2]   = 1;     //  Land nr.1  er:  Island
 felles[2][4]   =  felles[4][2]   = 1;     //  Land nr.2  er:  Norge
 felles[2][5]   =  felles[5][2]   = 1;
 felles[3][4]   =  felles[4][3]   = 1;     //  Land nr.3  er:  Sverige
 felles[3][11]  =  felles[11][3]  = 1;
 felles[4][5]   =  felles[5][4]   = 1;     //  Land nr.4  er:  Finland
 felles[5][6]   =  felles[6][5]   = 1;     //  Land nr.5  er:  Sovjetunionen
 felles[5][7]   =  felles[7][5]   = 1;     //       Har IKKE inndelt Sovjet !
 felles[5][8]   =  felles[8][5]   = 1;
 felles[5][9]   =  felles[9][5]   = 1;
 felles[5][23]  =  felles[23][5]  = 1;
 felles[5][24]  =  felles[24][5]  = 1;
 felles[5][25]  =  felles[25][5]  = 1;
 felles[6][7]   =  felles[7][6]   = 1;     //  Land nr.6  er:  Estland
 felles[7][8]   =  felles[8][7]   = 1;     //  Land nr.7  er:  Latvia
 felles[8][9]   =  felles[9][8]   = 1;     //  Land nr.8  er:  Litauen
 felles[9][10]  =  felles[10][9]  = 1;     //  Land nr.9  er:  Polen
 felles[9][22]  =  felles[22][9]  = 1;
 felles[9][23]  =  felles[23][9]  = 1;
 felles[10][11] =  felles[11][10] = 1;     //  Land nr.10 er:  Tyskland
 felles[10][16] =  felles[16][10] = 1;
 felles[10][17] =  felles[17][10] = 1;
 felles[10][18] =  felles[18][10] = 1;
 felles[10][19] =  felles[19][10] = 1;
 felles[10][20] =  felles[20][10] = 1;
 felles[10][22] =  felles[22][10] = 1;
 felles[12][13] =  felles[13][12] = 1;     //  Land nr.11 er:  Danmark
 felles[12][16] =  felles[16][12] = 1;     //  Land nr.12 er:  Storbritannia
		                      			   //  Land nr.13 er:  Irland
 felles[14][15] =  felles[15][14] = 1;     //  Land nr.14 er:  Portugal
 felles[15][16] =  felles[16][15] = 1;     //  Land nr.15 er:  Spania
 felles[16][17] =  felles[17][16] = 1;     //  Land nr.16 er:  Frankrike
 felles[16][19] =  felles[19][16] = 1;
 felles[16][21] =  felles[21][16] = 1;
 felles[17][18] =  felles[18][17] = 1;     //  Land nr.17 er:  Belgia
 felles[19][20] =  felles[20][19] = 1;     //  Land nr.18 er:  Nederland
 felles[19][21] =  felles[21][19] = 1;     //  Land nr.19 er:  Sveits
 felles[20][21] =  felles[21][20] = 1;     //  Land nr.20 er:  sterrike
 felles[20][22] =  felles[22][20] = 1;
 felles[20][23] =  felles[23][20] = 1;
 felles[20][24] =  felles[24][20] = 1;
 felles[20][26] =  felles[26][20] = 1;
 felles[21][26] =  felles[26][21] = 1;     //  Land nr.21 er:  Italia
 felles[22][23] =  felles[23][22] = 1;     //  Land nr.22 er:  Tsjekkia
 felles[23][24] =  felles[24][23] = 1;     //  Land nr.23 er:  Slovakia
 felles[24][25] =  felles[25][24] = 1;     //  Land nr.24 er:  Ungarn
 felles[24][27] =  felles[27][24] = 1;
 felles[25][27] =  felles[27][25] = 1;     //  Land nr.25 er:  Romania
 felles[25][28] =  felles[28][25] = 1;
 felles[26][27] =  felles[27][26] = 1;     //  Land nr.26 er:  Slovenia
 felles[27][28] =  felles[28][27] = 1;     //  Land nr.27 er:  Serbo-Kroatia
 felles[27][29] =  felles[29][27] = 1;
 felles[27][30] =  felles[30][27] = 1;
 felles[28][30] =  felles[30][28] = 1;     //  Land nr.28 er:  Bulgaria
 felles[28][31] =  felles[31][28] = 1;
 felles[28][32] =  felles[32][28] = 1;
 felles[29][30] =  felles[30][29] = 1;     //  Land nr.29 er:  Albania
 felles[29][31] =  felles[31][29] = 1;
 felles[30][31] =  felles[31][30] = 1;     //  Land nr.30 er:  Makedonia
 felles[31][32] =  felles[32][31] = 1;     //  Land nr.31 er:  Hellas
}                                          //  Land nr.32 er:  Tyrkia
