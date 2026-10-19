
#ifndef __STED_H
#define __STED_H


#include "tralle.h"
#include "sykkel.h"
#include "elsparkesykkel.h"
#include "LesData3.h"
#include "kunde.h"


/**
 * @class Sted
 * @brief en klasse som har info til ett sted
 */
class Sted  {
  private:
    std::string stedBeskrivelse;         //evt. stedets unike ID/navn, kort beskrivelse/forklaring av stedet
    std::string stedNavn;
    int stedTlfNr;                  //telefonnummer (for å kontakte stedet/kontoret), inntjente kroner
    int inntekt;
    std::vector <Tralle*> ledigTralle;                       //alle trallene som stedet for tiden har til utlån
    std::vector <Sykkel*> ledigSykkel;                       //alle syklene som stedet for tiden har til utlån
    std::vector <Elsparkesykkel*> ledigElsparkesykkel;       // alle elsparkesyklene som stedet har til utlån



  public:
    Sted(){};
    Sted(std::ifstream & inn);
    void nySted(std::string navnPaaSted);
    void skrivSted();
    void skrivStedInntekt();
    void nyGjenstand(int nr);
    void slettSted(Sted* tilSted);
    void laanGjenstand(Kunde* kundePeker);
    void laanTralle(Kunde* kundePeker);
    void laanSykkel(Kunde* kundePeker);
    void laanElsparkesykkel(Kunde* kundePeker);
    void leverGjenstand(Kunde* kundePeker);
    void skrivStedSomHarIgjen(type gjenstandType);
    void overforGjenstand(Sted* tilSted);
    void overforTralle(Sted* tilSted);
    void overforSykkel(Sted* tilSted);
    void overforElsparkesykkel(Sted* tilSted);
    void nyTralle(int nr);
    void nySykkel(int nr);
    void nyElsparkesykkel(int nr);
    std::string hentNavn();
    bool finnGjenstand(int nr);
    void slettGjenstand(int nr);
    void skrivTilFil(std::ofstream & out);
};







#endif