
#ifndef __GJENSTAND_H
#define __GJENSTAND_H


#include <iostream>
#include "enumer.h"
#include <fstream>







/**
 * @class Gjenstand
 * @brief en klasse som gir info til gjenstandene
 */
class Gjenstand  {
  private:
    int gjenstandNr;                // et unikt gjenstandsnummer
    type typeGjenstand;     
                    // for å representere hvilken subklasse vi egentlig har med å gjøre
                    //(Brukes bl.a. ved K L når gjenstander skal legges over i rett vector på stedet.)
                    //dette skal skrives i enum filen


  public:
    Gjenstand(int nr, type gjenstandType){gjenstandNr = nr; typeGjenstand = gjenstandType;};   //mereeee ting
    Gjenstand(std::ifstream & inn, type gjenstandType);
    type hentTypeGjenstand();
    virtual void lesData() = 0;
    int hentNr() const { return gjenstandNr; }
    virtual void skrivData();
    virtual void skrivTilFil(std::ofstream & out);
    int hentGjenstandNr();

    
};




#endif