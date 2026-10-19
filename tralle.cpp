


#include "tralle.h"
#include "LesData3.h"

#include <fstream>

using namespace std;




/**
 * kontruktor for tralle
 * 
 * @param inn 
 */
Tralle::Tralle(ifstream & inn) : Gjenstand(inn, tralle){
    inn >> harDrasele;
}


/**
 * Leser data for tralle
 * 
 */
void Tralle::lesData(){
    char svar;

    svar = lesChar("Har trallen sele/stropp (J/N): ");

    if (svar == 'J'){
        harDrasele = 1;
    }
    else{harDrasele = 0;}

}


/**
 * skriv data om tralle
 * 
 */
void Tralle::skrivData(){
    Gjenstand::skrivData();
    cout << harDrasele;
    cout << '\n';
}


/**
 * skriver til fil om tralle
 * 
 * @param out 
 */
void Tralle::skrivTilFil(ofstream &out){
    Gjenstand::skrivTilFil(out);
    out << harDrasele << '\n';
}