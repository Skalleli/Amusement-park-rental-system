#ifndef __TRALLE_H
#define __TRALLE_H



#include "gjenstand.h"

#include <fstream>


/**
 * @class Tralle
 * @brief en klasse med info om en tralle
 */
class Tralle : public Gjenstand {
  private:
    bool harDrasele;               // om er utstyrt med drasele/-stropp eller ei (i tillegg til drastaget i metall)
                        //(Tralle er en liten kassevogn med fire hjul. Oppi denne kan små barn sitte
                        //og/eller bagasjen (sekker, bagger, poser o.l.) ligge.)



  public:
    Tralle(int gjenstandNr):Gjenstand(gjenstandNr, tralle){harDrasele = 0;}
    void lesData();
    Tralle(std::ifstream & inn);
    virtual void skrivData();
    virtual void skrivTilFil(std::ofstream & out);
};


#endif