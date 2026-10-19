
#ifndef __SYKKEL_H
#define __SYKKEL_H


#include "gjenstand.h"

#include <fstream>



/**
 * @class Sykkel
 * @brief en klasse med info om sykler
 */
class Sykkel : public Gjenstand {
  private:
    bool harTilhenger;               // har med tilhenger bak eller ei (til bagasje/sitteplass for mindre barn)


  public:
    Sykkel(int gjenstandNr):Gjenstand(gjenstandNr, sykkel){harTilhenger = 0;}
    void lesData();
    Sykkel(std::ifstream & inn);
    virtual void skrivData();
    virtual void skrivTilFil(std::ofstream & out);
};


#endif