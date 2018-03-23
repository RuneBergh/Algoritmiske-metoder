//  Fil:  FRODEH \ ALG_MET \ EKSEMPEL \ EKS_01.CPP

//  Eksemplene viser enkel bruk av rekursjon.


#include <iostream>
using namespace std;

const int MAXCALL = 5;


void display1(int n)  {               //  Enkel rekursjon (iterajon).
  cout << n << ' ';
  if (n < MAXCALL)  display1(n+1);
}


void display2a(int n)  {               //  2x display og tilslutt rekursjon
  cout << n << ' ';                    //     (iterasjon).
  cout << n+100 << ' ';
  if (n < MAXCALL)  display2a(n+1);
}


void display2b(int n)  {               //  2x display med rekursjon MELLOM.
  cout << n << ' ';                    //    Legg merke til forskjellen p†
  if (n < MAXCALL)  display2b(n+1);    //    output i forhold til '2a' !
  cout << n+100 << ' ';
}


void display3(int n)  {                //  Leser tegn og skriver baklengs
  if (n <= 10)  {                      //    ut igjen.
     char ch;
     cin >> ch;
     display3(n+1);
     cout << ch << ' ';
  } else
    cout << "\n\n";
}


void display4(int n)  {               //  Rekursjon UTEN stoppbetingelse
  cout << n << ' ';                    //    ("br›nn").
  display4(n+1);
}


int main()  {
  char cc;
  cout << "\nDISPLAY og deretter REKURSJON: ";
  display1(1);      cin >> cc;
  cout << "\nDISPLAY, DISPLAY og deretter REKURSJON: ";
  display2a(1);     cin >> cc;
  cout << "\nDISPLAY, REKURSJON og deretter DISPLAY: ";
  display2b(1);     cin >> cc;
  cout << "\nLese tegn og skrive dem baklengs ut igjen:   ";
  display3(1);      cin >> cc;
  cout << "\nREKURSJON uten stoppbetingelse: ";
  display4(1);
  return 0;
}
