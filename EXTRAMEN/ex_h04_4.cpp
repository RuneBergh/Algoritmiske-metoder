//  Fil:  FRODEH \ ALG_MET \ EXTRAMEN \EX_H04_4.CPP

//     L›sningsforslag til eksamen i
//     "Algoritmiske metoder", oppgave nr.4, 3.desember 2004.

//     Laget av Frode Haug, HiG, november 2004.


/*
  Pseudokode/prosatekst:

  - Dette dreier seg kort og godt om en graf, der nodene er
    skuespillernes navn, og at det er kanter mellom dem som
    har spilt i samme film.

  - For † bygge opp en relevant datastruktur kan vi bare bruke
    nabolister eller nabomatrise. Hver enkelt ny skuespillers
    navn (p† filen) m† bare tilsvare en entydig og fortl›pende
    indeks i arrayen.

  - Det † finne "minimums filmgraden" mellom to skuespillere
    er rett og slett † finne korteste vei mellom dem!

  - Til dette kan vi bruke tre ulike algoritmer fra l‘reboka:
        1) Bredde-F›rst-S›k (kap.29, s.431 (og 424))
        2) Korteste sti (kap.31, s.455 med "priority" = "val[k]+t->w")
        3) Alle korteste stier (kap.32, s.477)

  - Nr.2 er den koden som m† minst tilpasses i denne forbindelse.
    Den er jo skapt for akkurat dette problemet!
    Om man overhodet ikke endrer noe p† nr.3 s† finner den svaret for
    ALLE nodene, og det er jo litt mer enn det vi trenger † vite .....

  - Nr.1 vil nok generelt v‘re mest effektiv, da det ofte ikke
    er s† mange kantene man trenger † g†, f›r man finner en relasjon
    mellom skuespiller X og Y ("minimums filmgraden"). Derfor vil et
    bredde-f›rst-s›k v‘re mest egnet, istedet for at man mer tilfeldig
    "roter seg" langt av sted i grafen (nr.2 og 3), og finner svaret sent,
    kan hende som den siste naboen man bes›ker ut fra skuespiller X!
    (Nr.3 finner ALLE korteste stier, MYE mer enn vi i utgangspunktet er
    interessert i, derfor vil den selvsagt ta lengre tid enn n›dvendig.)

*/
