
#include "sykkel.h"
#include "LesData3.h"

#include <fstream>

using namespace std;



/**
 * kontruktor av sykkel
 * 
 * @param inn 
 */
Sykkel::Sykkel(ifstream & inn) : Gjenstand(inn, sykkel){
    inn >> harTilhenger;
}


/**
 * Leser data til sykkel
 * 
 */
void Sykkel::lesData(){
    char svar;
    svar = lesChar("Har sykkelen tilhenger (J/N): ");

    if (svar == 'J'){
        harTilhenger = 1;
    }
    else {harTilhenger = 0;}


}


/**
 * skriver data om sykkel
 * 
 */
void Sykkel::skrivData(){
    Gjenstand::skrivData();
    cout << harTilhenger;
    cout << '\n';
}


/**
 * skriver til fil om sykkel, tar med fra gjenstand
 * 
 * @param out 
 */
void Sykkel::skrivTilFil(ofstream &out){
    Gjenstand::skrivTilFil(out);
    out << harTilhenger << '\n';
}