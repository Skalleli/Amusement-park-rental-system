

#ifndef __KUNDE_H
#define __KUNDE_H


#include <vector>
#include <string>
#include "gjenstand.h"



/**
 * @class Kunde
 * @brief en klasse med info om hver enkelt kunde
 */
class Kunde  {
  private:
    int kundeNr;                        //kundens unike nummer (sortert på dette), mobilnummer
    int mobilNr;
    std::string navn;                        // navn
    std::vector <Gjenstand*> leideGjenstander;        //usortert vector med nåværende leide gjenstander 

  public:
    Kunde(){kundeNr = mobilNr = 0; navn = "";}
    Kunde(std::ifstream & inn);
    void nyKunde(const int sisteNr);   
    void skrivKunde();
    void skrivKundeOgGjenstander();      
    int hentKundeNr();
    void leggTilGjenstand(Gjenstand*);
    std::vector <Gjenstand*> hentAlleGjenstander();
    void tomGjenstandVector();
    bool finnGjenstand(int nr);
    void skrivTilFil(std::ofstream & out);
};





#endif