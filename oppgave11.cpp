#include <iostream>
using namespace std;



const int MAX =8 ;
 int boardsize;
 int ant=0;
 


int board[MAX+1][MAX+1];

void display()  {            //  Skriver ut brettets innhold.
  int i, j;
  char ch;

  cout << "\n\n\nløsningNR." << ++ant << ":\n\t";

  for (i = 1;  i <= boardsize;  i++)  {
      for (j = 1;  j <= boardsize;  j++)
	  cout << board[i][j] << "  ";
      cout << "\n\t";
  }
  cout << "\t\t\tSkriv ett tegn .....";   //cin >> ch;
}


void permhorse(int i, int j,int nr)
{
    if (i>=1 && j>=1 && j<=boardsize && i<=boardsize && board[i][j] == 0)
    {
        board[i][j]=nr;
       if(nr==boardsize*boardsize)
       {                                //fylt opp brettet, skriv ut løsning
         display();
       } else{
            permhorse(i+2,j-1,nr+1);
            permhorse(i+2,j+1,nr+1);
            permhorse(i-2,j-1,nr+1);
            permhorse(i-2,j+1,nr+1);
            permhorse(i+1,j-2,nr+1);
            permhorse(i+1,j+2,nr+1);
            permhorse(i-1,j-2,nr+1);
            permhorse(i-1,j+2,nr+1);
        }
               board[i][j] = 0;      //  Frigir ruten igjen. Her er cluet for å få mer enn en løsning

    }

}

int main ()
{

    int linje, kolonne;
 do  {                            // Leser spillebrettets st�rrelse:
    cout << "Spillets strrelse (1-" << MAX << "):  ";
    cin >> boardsize;
    cout << "linje: "; cin >> linje; cout << "Kolonne="; cin >> kolonne;
     
  }while (boardsize < 1  || boardsize > MAX);
permhorse(linje, kolonne,1);
    return 0;
}
