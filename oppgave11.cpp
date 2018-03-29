#include <iostream>
using namespace std;



const int MAX =8 ;
 int boardsize;
 int flyttNR=0;
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
  cout << "\t\t\tSkriv ett tegn .....";   cin >> ch;
}



bool notvisited(int i,int j)
{
    if (i>=1 && j>=1 && j<=boardsize && i<=boardsize)
        return false;
    if (!board[i][j]){
        return false;
     }

     return true;
}

void permhorse(int linje, int kolonne)
{

        if(flyttNR==((boardsize*boardsize)-1))              //fylt opp brettet, skriv ut løsning
         display();
         
         for (int j=1;j<=boardsize;j++ )
             if(notvisited(linje,kolonne))
              board[linje][kolonne]=flyttNR++;

              permhorse(linje++,kolonne++);
              
             
    


}






int main ()
{

    int linje, kolonne;
 do  {                            // Leser spillebrettets st�rrelse:
    cout << "Spillets strrelse (1-" << MAX << "):  ";
    cin >> boardsize;
    cout << "linje: "; cin >> linje; cout << "Kolonne="; cin >> kolonne;
     
  }while (boardsize < 1  || boardsize > MAX);
permhorse(linje, kolonne);
    return 0;
}
