//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H10_4.CPP

//     L›sningsforslag til eksamen i "Algoritmiske metoder",
//     21.desember 2010, oppgave nr.4.

//     Laget av Frode Haug, HiG, desember 2010.


#include <iostream>
using namespace std;

const int N = 1000;             //  Setter N til ›nsket verdi.

int main()   {
  int i, j, sum,                //  2x l›kkevariable og totalsummen hittil.
      n = N/2;                  //  M - holder † g† halveis (+1).

  for (i = 1;  i <= n;  i++)  {      //  G†r til halveis:
      sum = i;   j = i;              //  Initierer sum og j.
                                     //  Ikke passert N i totalsum, samt at
      while (sum < N  &&  j <= n)    //     ikke kommet forbi halveis:
         sum += (++j);               //  Oppdaterer totalsum med neste tall.
	  
      if (sum == N)                  //  Tallrekken gir EKSAKT N:
         cout << '\n' << N << " = summen av tallene fra " 
              << i << " til " << j << '\n';
  }
  cout << "\n\n";
  return 0;
}
