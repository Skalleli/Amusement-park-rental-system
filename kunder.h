

#ifndef __KUNDER_H
#define __KUNDER_H


#include <list>
#include "kunde.h"



/**
 * @class Kunder
 * @brief en klasse med liste over alle kundene
 */
class Kunder  {
  private:
    int sisteNr;            //fortløpende økende automatisk nummerering av alle nye kunder
    std::list <Kunde*> kundeliste;          //sortert liste med de unikt nummererte kundene

  public:
    Kunder(){sisteNr = 0;}
    void nyKunder();   //lager ny kunde
    void skrivKunder();    //skriver alle kunder med deres data 
    void handling();
    void lesFraFil();
    void skrivTilFil();
    bool finnGjenstandKunder(int nr);
};







#endif