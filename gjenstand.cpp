/**
 * @file gjenstand.cpp
 * @author Stine Kalleli
 * @brief 
 * @version 0.1
 * @date 19.03.2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "gjenstand.h"
#include "enumer.h"
#include <fstream>

using namespace std;



/**
 * Leser inn alt om gjenstand
 * 
 * @param inn 
 */
Gjenstand::Gjenstand(ifstream & inn, type gjenstandType){
    typeGjenstand = gjenstandType;
    inn >> gjenstandNr;

}

int Gjenstand::hentGjenstandNr(){
    return gjenstandNr;   
}


/**
 * Henter typen gjenstand
 * 
 * @return type 
 */
type Gjenstand::hentTypeGjenstand(){

    return typeGjenstand;
}


void Gjenstand::skrivData(){
    cout << gjenstandNr;
    if(typeGjenstand == tralle){
        cout << "tralle";
        cout << '\n';
    }
    else if (typeGjenstand == sykkel){
        cout << "sykkel";
        cout << '\n';
    }
    else{
        cout << "elsparkesykkel";
        cout << '\n';
    }
}


/**
 * skriver gjenstand til fil, som brukes av de andre typene gjenstand
 * 
 * @param out 
 */
void Gjenstand::skrivTilFil(ofstream & out){
    out << gjenstandNr << '\n';
    
}


