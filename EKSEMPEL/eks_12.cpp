//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_12.CPP


//  Eksemplet viser hvordan man kan finne korteste vei
//  (dvs. f‘rrest antall kanter) mellom to noder i en graf.


#include <iostream>          //  cout

using namespace std;


const int MAXNODER = 26;    //  CONST:
const int UNSEEN    =  0;
const int SEEN      =  1;
			     //  GLOBALE VARIABLE:
int a[MAXNODER][MAXNODER];  //     Nabo-matrisen for 5x5 graf der alle
			                //       er nabo med ALLE sine n‘rmeste.
int val[MAXNODER];          //     Bes›kt node allerede eller ei.


void initAdjacent()  {      //  Initierer 'a' med alle nodenes naboer.
  for (int i = 1;  i < MAXNODER;  i++)  a[i][i] = 1;
  a[1][2]=a[1][6]=a[1][7]=1;
  a[2][1]=a[2][3]=a[2][7]=a[2][6]=a[2][8]=1;
  a[3][2]=a[3][4]=a[3][8]=a[3][7]=a[3][9]=1;
  a[4][3]=a[4][5]=a[4][9]=a[4][8]=a[4][10]=1;
  a[5][4]=a[5][10]=a[5][9]=1;
  a[6][7]=a[6][1]=a[6][11]=a[6][2]=a[6][12]=1;
  a[7][6]=a[7][8]=a[7][2]=a[7][12]=a[7][1]=a[7][3]=a[7][11]=a[7][13]=1;
  a[8][7]=a[8][9]=a[8][3]=a[8][13]=a[8][2]=a[8][4]=a[8][12]=a[8][14]=1;
  a[9][8]=a[9][10]=a[9][4]=a[9][14]=a[9][3]=a[9][5]=a[9][13]=a[9][15]=1;
  a[10][9]=a[10][5]=a[10][15]=a[10][4]=a[10][14]=1;
  a[11][12]=a[11][6]=a[11][16]=a[11][7]=a[11][17]=1;
  a[12][11]=a[12][13]=a[12][7]=a[12][17]=a[12][6]=a[12][8]=a[12][16]=a[12][18]=1;
  a[13][12]=a[13][14]=a[13][8]=a[13][18]=a[13][7]=a[13][9]=a[13][17]=a[13][19]=1;
  a[14][13]=a[14][15]=a[14][9]=a[14][19]=a[14][8]=a[14][10]=a[14][18]=a[14][20]=1;
  a[15][14]=a[15][10]=a[15][20]=a[15][9]=a[15][19]=1;
  a[16][17]=a[16][11]=a[16][21]=a[16][12]=a[16][22]=1;
  a[17][16]=a[17][18]=a[17][12]=a[17][22]=a[17][11]=a[17][13]=a[17][21]=a[17][23]=1;
  a[18][17]=a[18][19]=a[18][13]=a[18][23]=a[18][12]=a[18][14]=a[18][22]=a[18][24]=1;
  a[19][18]=a[19][20]=a[19][14]=a[19][24]=a[19][13]=a[19][15]=a[19][23]=a[19][25]=1;
  a[20][19]=a[20][15]=a[20][25]=a[20][14]=a[20][24]=1;
  a[21][22]=a[21][16]=a[21][17]=1;
  a[22][21]=a[22][23]=a[22][17]=a[22][16]=a[22][18]=1;
  a[23][22]=a[23][24]=a[23][18]=a[23][17]=a[23][19]=1;
  a[24][23]=a[24][25]=a[24][19]=a[24][18]=a[24][20]=1;
  a[25][24]=a[25][20]=a[25][19]=1;
}

			     //  Aktuell node er 'fra', og man er p† leting
			     //  etter 'til'-noden. N†v‘rende steg er
			     //  nr.'steg', og minimum antall kanter funnet
			     //  til n† er 'minS'.
void visit(int fra, int til, int steg, int & minS)  {
  int t;
  val[fra] = SEEN;           //  N† er 'fra' bes›kt (for † hindre cykler).

  if (fra != til  &&  steg < minS-1)  {   //  Ikke n†dd fram, og fortsatt
					                      //    mulighet for † finne ny
					                      //    korteste vei.
     for (t = 1;  t < MAXNODER;  t++)     //  Bes›ker (om mulig) naboene:
	 if (a[fra][t] != 0  &&  val[t] == UNSEEN)
	    visit(t, til, steg+1, minS);

  } else if (fra == til  &&  steg < minS)  minS = steg;  // Ny korteste:

  val[fra] = UNSEEN;         // 'Fra' er ferdig behandlet (i denne omgang)
}                            //    og andre kan bes›ke den senere (via
			                 //    andre (og kanskje kortere) kanter inn).


int main()  {
  int minSteg = 32000;
  int tilNode, fraNode;

  initAdjacent();

  do  {
    cout << "\n\nGrafen har " << MAXNODER-1 << " noder. "
	     << "Finn minimum antall kanter\n\tfra: ";    cin >> fraNode;
    cout << "\ttil: ";                                cin >> tilNode;
  }  while (fraNode < 1  ||  fraNode >= MAXNODER  ||
	    tilNode < 1  ||  tilNode >= MAXNODER);

  visit(fraNode, tilNode, 0, minSteg);

  cout << "\n\nMinimum antall steg/kanter fra node nr." << fraNode
       << " til node nr." << tilNode << " er:  " << minSteg << "\n\n\n";
  return 0;
}
