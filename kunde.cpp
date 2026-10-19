/**
 * @file kunde.cpp
 * @author Stine Kalleli
 * @brief 
 * @version 0.1
 * @date 15.03.2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include <fstream>

#include "kunde.h"
#include "kunder.h"
#include "LesData3.h"  
#include "tralle.h"
#include "sykkel.h"
#include "elsparkesykkel.h"

using namespace std;




Kunde::Kunde(ifstream & inn){
    int gjenstandAntall;
    char type;

    inn >> kundeNr;
    inn >> mobilNr;
    inn.ignore(); getline(inn, navn);


    inn >> gjenstandAntall;
    for(int i = 0; i < gjenstandAntall; i++){   
        inn >> type;

        if(type == 'T'){
            Tralle* t = new Tralle(inn);
            leideGjenstander.push_back(t);
        }
        else if(type == 'S'){
            Sykkel* t = new Sykkel(inn);
            leideGjenstander.push_back(t);
        }
        else{Elsparkesykkel* t = new Elsparkesykkel(inn);
            leideGjenstander.push_back(t);}

    }
 
}


/**
 * Returnerer leideGjenstander
 * 
 * @return vector <Gjenstand*> 
 */
vector <Gjenstand*> Kunde::hentAlleGjenstander(){
    return leideGjenstander;
}


/**
 * Finner gjenstand i kunde
 * 
 * @param nr 
 * @return true 
 * @return false 
 */
bool Kunde::finnGjenstand(int nr) {
    bool funnet = false;

    for (int i = 0; i < leideGjenstander.size(); i++) {
        if (leideGjenstander[i]->hentNr() == nr) {
            cout << "Funnet hos kunde: " << navn << endl;
            funnet = true;
        }
    }
    return funnet;
}


/**
 * Henter kundenummer
 * 
 * @return int 
 */
int Kunde::hentKundeNr(){
    return kundeNr;
}


/**
 * Legger til gjenstand
 * 
 * @param gjenstandPeker 
 */
void Kunde::leggTilGjenstand(Gjenstand* gjenstandPeker){
    leideGjenstander.push_back(gjenstandPeker);
}


/**
 * Leser inn informasjonen til en ny kunde
 * 
 * @param sisteNr 
 */
 void Kunde::nyKunde(const int sisteNr){

    kundeNr = sisteNr;
    mobilNr = lesInt("Mobilnummer: ", 11111111, 99999999);
    cout << "Navn: ";     getline(cin, navn);
   

 }

/**
 * Skriver ut informasjon om en kunde
 * 
 */
void Kunde::skrivKunde(){

    cout << '\n' << "Kunde nr. " << kundeNr << " ";
    cout << "Navn: " << navn << " ";
    cout << "Mobilnummer: " << mobilNr << " "; 
    cout << "Kundes leide gjenstander: " << leideGjenstander.size() << '\n'; 

}

/**
 * Skriver ut informasjon om en kunde og om gjenstandene til kunden
 * 
 */
void Kunde::skrivKundeOgGjenstander(){
    skrivKunde();
    for(int i = 0; i < leideGjenstander.size(); i++){
        leideGjenstander[i]->skrivData();
    }
}


/**
 * skriver kunde til fil
 * 
 * @param out 
 */
void Kunde::skrivTilFil(ofstream &out){
    out << kundeNr << '\n';
    out << mobilNr << '\n';
    out << navn << '\n';
    out << leideGjenstander.size() << '\n';
    for(int i =0; i < leideGjenstander.size(); i++){
        if(leideGjenstander[i]->hentTypeGjenstand() == tralle){
            out << 'T' << '\n';
        }
        else if(leideGjenstander[i]->hentTypeGjenstand() == sykkel){
            out << 'S' << '\n';
        }
        else {
            out << 'E' << '\n';
        }
        leideGjenstander[i]->skrivTilFil(out);
    }
    
}


/**
 * Tommer vectoren med leide gjenstander
 * 
 */
void Kunde::tomGjenstandVector(){
    leideGjenstander.clear();
}