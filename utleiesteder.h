

#ifndef __UTLEIESTEDER_H
#define __UTLEIESTEDER_H


#include <map>
#include <string>

#include "kunde.h"
#include "sted.h"



/**
 * @class Utleiesteder
 * @brief en klasse med alle stedene
 */
class Utleiesteder  {
  private:
    int sisteNr = 0;            //fortløpende økende automatisk nummerering av alle nye gjenstander
    std::map <std::string, Sted*> stedNavn;    // map med alle unikt navnede Sted’er (navn er forkortelser/koder, f.eks. «Sted1», «B7», «AKV»)


  public:
    void nyUtleiested();
    void skrivAlleSted();
    void skrivNavnPaaSted();
    void nyGjenstandSted();
    void seOmStedFinsOgLaaner(Kunde* kundePeker);
    void seOmStedFinsOgLeverer(Kunde* kundePeker);
    void lesFraFil();
    void skrivTilFil();
    void handling(char valg);
    void skrivAlleStedInntekt();
    void seOmStedFinsOgOverforer();
    void seOmStedFinsOgNyGjenstand();
    bool finnGjenstand(int nr);
    void slettGjenstand(int nr);
    void skrivSted();
    void slettSted();
};







#endif