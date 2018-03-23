//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H05_4B.CPP

//     Løsningsforslag til Sudoku.
//     Basert på eksamen i "Algoritmiske metoder", 8.desember 2005, oppg.nr.4,
//     men løst på en annen måte (uavhengig av oppgavens vedlegg).

//     Laget av Thomas Mellemseter, 12HBPUA, HiG, oktober 2013.


              //  INCLUDE:
#include <iostream>
//  #include <Windows.h>
using namespace std;

              //  CONST:
const int MAX = 9;                //  MAX Board 9x9.
const int TIME = 1000;            //  Millisecond display time.

              //  DECLARATION OF FUNCTIONS:
void display();                   //  Show grid.
bool finnLosning(int x, int y);   //  Find every solution.
bool visit(int x, int y, char v); //  Try to place a number.
bool lov(int x, int y, char v);   //  Checks if the number is legal.
void update(int & x, int & y);    //  Updates next to visit.

              //  GLOBALE:
char grid[MAX][MAX] = {{'_','_','7','1','5','_','_','9','4'},
                       {'_','_','_','_','_','_','_','7','_'},
                       {'9','_','6','_','_','3','_','_','_'},
                       {'3','1','_','6','_','_','_','_','_'},
                       {'_','_','4','_','8','_','3','_','_'},
                       {'_','_','_','_','_','7','_','1','8'},
                       {'_','_','_','8','_','_','7','_','5'},
                       {'_','5','_','_','_','_','_','_','_'},
                       {'6','8','_','_','7','9','4','_','_'},
                      };
/*  Eller:
char grid[MAX][MAX] = {{'_','6','2','_','_','_','_','_','_'},
                       {'_','_','_','_','_','4','_','_','_'},
                       {'_','_','_','_','_','9','1','_','7'},
                       {'_','_','8','_','3','_','2','_','_'},
                       {'_','_','_','7','_','_','_','_','6'},
                       {'2','5','_','_','4','_','_','9','_'},
                       {'8','_','_','_','_','_','_','_','3'},
                       {'_','9','_','_','6','_','4','_','_'},
                       {'3','7','_','5','_','_','_','_','_'},
                      };
*/
              //  MAIN:
int main() {
  finnLosning(0,0);     //  Start at position top-left in grid.
  cout << "\n\n";
  return 0;
}

              //  DEFENITION OF FUNCTIONS:
void display() {        //  Display grid.
  for (int i = 0;  i < MAX;  i++) {
    if (i  &&  !(i % 3)) cout << '\n';
    for (int j = 0;  j<MAX;  j++) {
      if (j  &&  !(j % 3)) cout << ' ';
      cout << grid[i][j];
    }
    cout << '\n';
  }
}


void update(int & x, int & y) {   //  Updates next box to visit.
  while (grid[x][y] != '_')             //  Skip numbered boxes:
    if (++y >= MAX)                     //    Move one row down
      {   y %= MAX; ++x;  }             //    if y gets too big.
}


bool finnLosning(int x, int y) {        //  Find every solution:
  int xt = x, yt = y;                   //  Temp/help varaiables
  char q;                               //  Stop to show a solution.

  if (x < MAX  &&  y < MAX) {           //  Keep trying until at the end of grid:
    for (int i = 1;  i <= 9;  i++) {    //  Trying every number:
      if (visit(x,y,char(i + '0'))) {   //  Number allowed:
//                  display();        //  Sleep(TIME);
//                  system("CLS");
        update(xt,yt);                  //  Find next position to visit:
        if (!finnLosning(xt,yt))        //  A number is not allowed:
          grid[xt][yt] = '_';           //    replace as empty.
      }
    }
  } else {
    display();                          //    Show grid.
    cout << "\n\t\tFant losning"; cin >> q;
    return true;
  }
  return false;                         //  No numbers allowed.
}


bool visit(int x, int y, char v) {
  if (lov(x,y,v)) {                     //  Give box a legal
    grid[x][y] = v;                     //  number.
    return true;
  }
  return false;                         //  Number not allowed.
}


bool lov(int x, int y, char v) {
  int i, j, k;              //  Loop checking: row/column and 3x3 box.
  int jt = x, kt = y;       //  Temp variables

  for (i = 0;  i < MAX;  i++) //  Its row and column:
    if ((i != y  &&  grid[x][i] == v)  ||  (i != x  &&  grid[i][y] == v))
      return false;

  jt -= (x % 3);            //  Find top-left cordinates of 3x3 box:
  kt -= (y % 3);

  for (j = jt;  j < jt+3;  j++)   //  Checing 3x3 box:
    for (k = kt;  k < kt+3;  k++)
      if (grid[j][k] == v)    
        return false;

  return true;              //  'v' is allowed.
}
