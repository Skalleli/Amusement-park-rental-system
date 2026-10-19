
#include "elsparkesykkel.h"
#include "LesData3.h"
#include "conster.h"

#include <fstream>

using namespace std;

/**
 * Leser inn antall med watt til elsparkesykkel
 * 
 */
void Elsparkesykkel::lesData(){
    
    antWatt = lesInt("Hvor mange watt har elsparkesykkelen: ", MINWATT, MAXWATT);

}


/**
 * kontruktor for Elsparkesykkel
 * 
 * @param inn 
 */
Elsparkesykkel::Elsparkesykkel(ifstream & inn) : Gjenstand(inn, elsparkesykkel){
    inn >> antWatt;
}


/**
 * skriver data om elsparkesykkel, tar ogsaa med data fra gjenstand
 * 
 */
void Elsparkesykkel::skrivData(){
    Gjenstand::skrivData();
    cout << antWatt;
    cout << '\n';
    
}

/**
 * skriver til fil om elsparkesykkel, ogsaa fra gjenstand
 * 
 * @param out 
 */
void Elsparkesykkel::skrivTilFil(ofstream & out){
    Gjenstand::skrivTilFil(out);
    out << antWatt << '\n';
}