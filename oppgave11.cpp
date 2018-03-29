#include <iostream>
using namespace std;



const int MAX =8 ;
 int boardsize;
 int flyttNR=1;
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



bool validmove(int i,int j)
{
    if (i<1 || j<1 || j>boardsize || i>boardsize)
        return false;

    if(board[i][j]==0 )
        return true;

return false;

}

void permhorse(int i, int j)
{
  cout << "i= "<<i << "j= "<< j;
       if(flyttNR==((boardsize*boardsize)+1))              //fylt opp brettet, skriv ut løsning
         display();
    for (int t=1;t<=(boardsize*boardsize);t++)
    { 
         if(validmove(i,j))
         {
            board[i][j]=flyttNR++;
            permhorse(i,j);
         }

        if(validmove(i+2,j-1))
         {
            permhorse(i+2,j-1);
         }

         if(validmove(i+2,j+1))
         {
            permhorse(i+2,j+1);
         }

         if(validmove(i-2,j-1))
         {
            permhorse(i-2,j-1);
         }

          if(validmove(i-2,j+1))
         {
            permhorse(i-2,j+1);
         }

          if(validmove(i-1,j-2))
         {
            permhorse(i-1,j-2);
         }

         if(validmove(i+1,j-2))
         {
            permhorse(i+1,j-2);
         }  

          if(validmove(i+1,j+2))
         {
            permhorse(i+1,j+2);
         }

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
permhorse(linje, kolonne);
    return 0;
}
