//   Fil:  FRODEH \ ALG_MET \ LAB_LOSN \ OPPG_06.CPP

//  ***************************************************************
//  ***************************************************************
//  ***                                                         ***
//  ***  NB:  Deler av koden virker KUN under/p† BORLAND 4.5 !  ***
//  ***                                                         ***
//  ***************************************************************
//  ***************************************************************


//  L›sningsforslag til oppgave nr.6  i  Algoritmiske metoder.


//  #include <graphics.h>                  //  Diverse grafikk
#include <iostream>

using namespace std;



//  Filen inneholder to ulike l›sningsforslag til Hanoi's t†rn.
//  Den f›rste skriver bare stegene som trengs for † l›se oppgaven.
//  Den andre tegner pinnene og deres innhold underveis.



// ***********************  EN l›sning/versjon:   ************************

void flytt1(int n, char fra, char via, char til)  {
  if (n == 1)                      // Nytt trekk kan foretas:
     cout << fra << " => " << til << "    ";
  else  {
      flytt1(n-1, fra, til, via);  // N-1 stk: Fra "fra" til "via" via "til".
      flytt1(1, fra, via, til);    // Den siste: fra "fra" til "til" via "via"
      flytt1(n-1, via, fra, til);  // N-1 fra det ›verste rekursive kallet:
  }                                //   Fra "via" via "fra" til "til".
}



// *********************  En ANNEN l›sning/versjon:  *********************

int *a, *b, *c;                        //  De tre "pinnene" og deres ringer.
int na,  nb,  nc;                      //  Antall skiver p† hver av pinnene.

void tegnPinner()  {                   //  Tegner "bordflate" og tre pinner.
/*  setcolor(BLACK);                   //  Blanker skjermen.
  clearviewport();
  setcolor(WHITE);                     //  Tegner med hvitt.
  setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
  line(0, 450, 639, 450);              //  Tegner "bordplaten".
  setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
  rectangle(150, 450, 170, 150);       //  Tegner de tre pinnene.
  rectangle(310, 450, 330, 150);
  rectangle(470, 450, 490, 150);
  outtextxy(158,470, "A");             //  Skriver tekst under hver pinne.
  outtextxy(318,470, "B");
  outtextxy(478,470, "C");  */
}

						  //  Tegner ringene p†
void tegnPinne(int n, int arr[], int narr)  {    //    pinne nr.'n'.
/*  int i, nn;
  setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
  for (i = 1;  i <= narr;  i++)  {     //  G†r gjennom alle ringene:
      nn = arr[i];                     //  Henter ringst›rrelsen.
      setcolor(nn);
      rectangle(((n*160)-10) - nn*15, 450 - (i*30),    // Tegner ringen:
		((n*160)+10) + nn*15, 477 - (i*30));
  }  */
}

void utskrift()  {
  char ch;
  tegnPinner();                       //  Tegner tre pinner og
  tegnPinne(1, a, na);                //    alle ringene p† hver av dem.
  tegnPinne(2, b, nb);
  tegnPinne(3, c, nc);
//  cin >> ch;                           //  Venter p† et tegn.
}

				       //  Temmelig identisk til "flytt1",
				       //    bare at h†ndterer tre pinner
				       //    og antallet p† hver av dem.
void flytt2(int ant, int fra[], int & nfra,
		     int via[], int & nvia,
		     int til[], int & ntil)  {
  if (ant == 1)  {                     //
     til[++ntil] = fra[nfra--];        //  Flytter ring.
     utskrift();                       //  Tegner pinnene og ringene.
  } else  {
     flytt2(ant-1, fra, nfra, til, ntil, via, nvia);
     flytt2(1, fra, nfra, via, nvia, til, ntil);
     flytt2(ant-1, via, nvia, fra, nfra, til, ntil);
  }
}


void hanoi(int n)  {                   //  Antall ringer = 'n'.
				       //  Lager tre arrayer med plass
				       //    p† indeks 1-N.
  a = new int[n+1];    b = new int[n+1];    c = new int[n+1];

  for (int i = 1;  i <= n;  i++)       //  Fyller pinne A med mindre
      a[i] = n - i + 1;                //    ringer oppover.
  na = n;                              //  Setter antallet p† pinne A.

  utskrift();                          //  Tegner pinnene initielt.

  flytt2(n, a, na, b, nb, c, nc);      //  L›ser oppgaven med hanoi's t†rn.

  delete [] a;  delete [] b;  delete [] c;   //  Sletter pinnene.
}


// **********************   HOVEDPROGRAM:   *******************************

int main()  {
  int antSkiver;
  char ch;

  cout << "\nAntall skiver:  ";        //  Leser antall skiver/ringer.
  cin >> antSkiver;

  flytt1(antSkiver, 'A', 'B', 'C');  cin >> ch;    //  L›ser med 1.metode.

//	     int driver = DETECT;      //  Initierer grafikken:
//	     int mode;
//	     char path[] = "\\borlandc\\bgi";
//	     initgraph(&driver, &mode, path);
  hanoi(antSkiver);                                //  L›ser med 2.metode.
//	     closegraph();
  cout << "\n\n";
  return 0;
}
