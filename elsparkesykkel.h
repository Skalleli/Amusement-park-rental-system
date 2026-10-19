
#ifndef __ELSPARKESYKKEL_H
#define __ELSPARKESYKKEL_H

#include "gjenstand.h"

#include <fstream>



/**
 * @class Elsparkesykkel
 * @brief en klasse som har info til elsparkesykler
 */
class Elsparkesykkel : public Gjenstand {
  private:
    int antWatt;                // antall watt


  public:
    Elsparkesykkel(int gjenstandNr):Gjenstand(gjenstandNr, elsparkesykkel){antWatt = 0;}
    void lesData();
    Elsparkesykkel(std::ifstream & inn);
    virtual void skrivData();
    virtual void skrivTilFil(std::ofstream & out);
};




#endif