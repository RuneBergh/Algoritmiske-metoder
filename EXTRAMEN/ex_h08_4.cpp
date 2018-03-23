//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H08_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     19.desember 2008, oppgave nr.4.

//     Laget av Frode Haug, HiG, desember 2008.


#include <iostream>
using namespace std;

const int DELTAGERE  =    50;  //  Antall deltagere (p† konferansen).
const int BUDSJETT   = 50000;  //  Budsjettet for ALLE deltagerne.
const int HOTELL     =     4;  //  Antall hoteller.
const int UKER       =     6;  //  Antall uker.

int pris[HOTELL+1];            //  Totalprisen for oppholdet p† hotell nr.i.
                  //  (For EN deltager, HELE oppholdet. Samme pris ALLE uker.)
int ledig[HOTELL+1][UKER+1];   //  Antall ledige enmanns-rom p† de ulike
                               //    hotellene, de ulike aktuelle ukene.

void initier()  {
  pris[1] = 900;   
      ledig[1][1] =  60;   ledig[1][2] =  48;   ledig[1][3] =  52; 
      ledig[1][4] =  18;   ledig[1][5] =  72;   ledig[1][6] =  62;
  pris[2] = 800;
      ledig[2][1] =  60;   ledig[2][2] =  48;   ledig[2][3] =  52;
      ledig[2][4] =  18;   ledig[2][5] =  72;   ledig[2][6] =  62;
  pris[3] = 750;
      ledig[3][1] =  60;   ledig[3][2] =  48;   ledig[3][3] =  52;
      ledig[3][4] =  18;   ledig[3][5] =  72;   ledig[3][6] =  62;
  pris[4] = 700;
      ledig[4][1] =  60;   ledig[4][2] =  48;   ledig[4][3] =  52;
      ledig[4][4] =  18;   ledig[4][5] =  72;   ledig[4][6] =  62;
}


int main()   {
  int i, j,                    //  L›kkevariabler.
      min = BUDSJETT + 1,      //  Evt. min.pris for opphold,
      hotell, uke;             //     p† 'hotell' i 'uke'.

  initier();

  for (i = 1;  i <= HOTELL;  i++)              //  For hvert hotell:
      if (DELTAGERE * pris[i]  <  min)         //  Totalpris er best hittil:
         for (j = 1;  j <= UKER;  j++)         //  For alle ukene:
             if (ledig[i][j]  >=  DELTAGERE) { //  Plass p† hotellet:
                min = DELTAGERE * pris[i];     //  Oppdaterer status-variable:
                hotell = i;  uke = j;
                break;
             }
  if (min <= BUDSJETT)                          //  Aktuelt og billigst hotell:
     cout << "\nHotell: "  << hotell
          << "\ti uke nr." << uke << "\tTotalpris: "  << min << "\n\n";
  else                                             //  Ingen hotell billige nok
     cout << "\nIngen sted † bo (forel›pig).\n\n"; //    og/eller ledige.
  return 0;
}
