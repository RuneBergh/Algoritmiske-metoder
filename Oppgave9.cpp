#include <iostream>
using namespace std;



const int MAX =8 ;
 int boardsize;


int board[MAX+1][MAX+1];
int ant=0;



void displayboard ()
{
char ch;
  cout << "\n\n\nLsning nr." << ++ant << ":\n";


    for(int i=1; i<=boardsize; i++)
        {

           for (int j=1;j<=boardsize;j++)
             {
                board[i][j]? cout << "1  ":cout<< "0  ";

             }
                 cout << endl;

         }

    cout << "\t\t\tSkriv ett tegn .....";   cin >> ch;


}

bool checkboard(int linje, int kolonne)
{
  int i;                                 

  for (i = 1;  i < kolonne;  i++)           //  Sjekker om noen annen brikke:
      if (board[linje][i] == 1)  return false;  //    - p� samme linje:

  for (i = kolonne-1;  i >= 1;  i--)  {     //    - p� en av diagonalene:
      if (linje - (kolonne-i) >= 1)         //  Dersom inne p� brettet:
	     if (board[linje-(kolonne-i)][i] == 1)  //  Opptatt p� diagonal
	        return false;                       //    OPP til venstre.
      if (linje + (kolonne-i) <= boardsize)         //  Dersom inne p� brettet:
	     if (board[linje+(kolonne-i)][i] == 1)  //  Opptatt p� diagonal
	        return false;                       //    NED til venstre.
  }
  return true;                              //  Alt OK.

}

void permqueen(int j)
{
    int i;
        if(j == boardsize+1)
        {
          displayboard();
        }
        else 
        {
            for (i=1;i<=boardsize;i++)
            {
                if (j == 1  ||  checkboard(i, j)) 
                {
                    board[i][j]=1;
                    permqueen(j+1);
                    board[i][j]=0;
                }
            }
        }

}



int main ()
{
 do  {                            // Leser spillebrettets st�rrelse:
    cout << "Spillets strrelse (1-" << MAX << "):  ";
    cin >> boardsize;
  } while (boardsize < 1  || boardsize > MAX);

permqueen(1);



    return 0;
}