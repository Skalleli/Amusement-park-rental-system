/**
 * @file sted.cpp
 * @author Stine Kalleli
 * @brief 
 * @version 0.1
 * @date 17.03.2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include <vector>
#include <fstream>

#include "sted.h"
#include "utleiesteder.h"
#include "LesData3.h"    
#include "gjenstand.h" 
#include "kunder.h"  
#include "kunde.h"
#include "enumer.h"
#include "tralle.h"
#include "sykkel.h"
#include "elsparkesykkel.h"
#include "conster.h"

using namespace std;



/**
 * sted kontruktor, hjelper med å lese inn info
 * 
 */
Sted::Sted(ifstream & inn){
    int tralleAntall;
    int sykkelAntall;
    int elsparkesykkelAntall;
    inn.ignore();
    getline(inn, stedBeskrivelse);
    getline(inn, stedNavn);
    inn >> stedTlfNr;
    inn >> inntekt;
    inn >> tralleAntall;
    for(int i = 0; i < tralleAntall; i++){
        Tralle* t = new Tralle(inn);
        ledigTralle.push_back(t);
    }
    inn >> sykkelAntall;
        for(int i = 0; i < sykkelAntall; i++){
        Sykkel* t = new Sykkel(inn);
        ledigSykkel.push_back(t);
    }
    inn >> elsparkesykkelAntall;
        for(int i = 0; i < elsparkesykkelAntall; i++){
        Elsparkesykkel* t = new Elsparkesykkel(inn);
        ledigElsparkesykkel.push_back(t);
    }

}

/**
 * finner gjenstand, leter gjennom traller, sykler og elsparkesykkler
 * 
 * @param nr 
 * @return true 
 * @return false 
 */
bool Sted::finnGjenstand(int nr) {
    bool funnet = false;


    for (int i = 0; i < ledigTralle.size(); i++) {
        if (ledigTralle[i]->hentNr() == nr) {
            cout << "Funnet: " << stedNavn << endl;
            funnet = true;
        }
    }

    for (int i = 0; i < ledigSykkel.size(); i++) {
        if (ledigSykkel[i]->hentNr() == nr) {
            cout << "Funnet: " << stedNavn << endl;
            funnet = true;
        }
    }

    for (int i = 0; i < ledigElsparkesykkel.size(); i++) {
        if (ledigElsparkesykkel[i]->hentNr() == nr) {
            cout << "Funnet: " << stedNavn << endl;
            funnet = true;
        }
    }

    return funnet;

}


/**
 * Henter sted navn 
 * 
 * @return string 
 */
string Sted::hentNavn(){
    return stedNavn;
}


/**
 * Laaner elsparkesykkler
 * 
 * @param kundePeker 
 */
void Sted::laanElsparkesykkel(Kunde* kundePeker){
    if(ledigTralle.empty()){
        cout << "Ingen ledige elsparkesykkler her naa.";
    }
    else{
        int antall = lesInt("Hvor mange elsparkesykkler vil du laane: ", 1, ledigElsparkesykkel.size());
        
        for(int i = 0; i < antall; i++){
            kundePeker->leggTilGjenstand(ledigSykkel.back());

            ledigSykkel.pop_back();
            inntekt+=PRISELSPARKESYKKEL;
        }
    }

}


/**
 * Bruker andre funksjoner til aa kunne laane alle typer gjenstander
 * 
 * @param kundePeker 
 */
void Sted::laanGjenstand(Kunde* kundePeker){
    char svar;
    svar = lesChar("Hva vil du laane(T/S/E): ");

    switch(svar)  {
      case 'T': laanTralle(kundePeker);           break; 
      case 'S': laanSykkel(kundePeker);           break;
      case 'E': laanElsparkesykkel(kundePeker);   break;

      default:                 break;
    }
  
}


/**
 * Laaner sykkler
 * 
 * @param kundePeker 
 */
void Sted::laanSykkel(Kunde* kundePeker){
    if(ledigTralle.empty()){
        cout << "Ingen ledige sykkler her nå.";
    }
    else{
        int antall = lesInt("Hvor mange sykkler vil du laane: ", 1, ledigSykkel.size());
        
        for(int i = 0; i < antall; i++){
            kundePeker->leggTilGjenstand(ledigSykkel.back());

            ledigSykkel.pop_back();
            inntekt+=PRISSYKKEL;
           
        }
    }


}


/**
 * Laaner traller
 * 
 * @param kundePeker 
 */
void Sted::laanTralle(Kunde* kundePeker){
    if(ledigTralle.empty()){
        cout << "Ingen ledige traller her nå.";
    }
    else{
        int antall = lesInt("Hvor mange traller vil du laane: ", 1, ledigTralle.size());
        
        for(int i = 0; i < antall; i++){
            kundePeker->leggTilGjenstand(ledigTralle.back());

            ledigTralle.pop_back();
            inntekt+=PRISTRALLE;
           
        }
    }
}


/**
 * Levere gjenstander
 * 
 * @param kundePeker 
 */
void Sted::leverGjenstand(Kunde* kundePeker){
    type gjenstandType;
    vector <Gjenstand*> kundensGjenstander;
    Gjenstand* gjenstand;
    kundensGjenstander = kundePeker->hentAlleGjenstander();


    for(int i = 0; i < kundensGjenstander.size(); i++){
        gjenstandType = kundensGjenstander[i]->hentTypeGjenstand();
        if(gjenstandType == tralle){
            gjenstand = kundensGjenstander[i];
            ledigTralle.push_back(dynamic_cast <Tralle*> (gjenstand));
        }
        else if(gjenstandType == sykkel){
            gjenstand = kundensGjenstander[i];
            ledigSykkel.push_back(dynamic_cast <Sykkel*> (gjenstand));

        }
        else{gjenstand = kundensGjenstander[i];
            ledigElsparkesykkel.push_back(dynamic_cast <Elsparkesykkel*> (gjenstand));    
        }
    };


    kundePeker->tomGjenstandVector();

}


/**
 * Lager ny elsparkesykkel
 * 
 * @param nr 
 */
void Sted::nyElsparkesykkel(int nr) {

    Elsparkesykkel* e = new Elsparkesykkel(nr);
    e->lesData();
    ledigElsparkesykkel.push_back(e);
}


/**
 * Bruker andre funksjoner til å lage alle typer gjenstander
 * 
 * @param nr 
 */
void Sted::nyGjenstand(int nr){
    char svar;
    do{
        svar = lesChar("Hvilken type gjenstand vil du lage (T/S/E)");

    }
    while(svar != 'T' && svar != 'S' && svar != 'E');
    
    switch(svar){
        case 'T': nyTralle(nr);         break;

        case 'S': nySykkel(nr);         break;

        case 'E': nyElsparkesykkel(nr); break;

        default:
    }

}


/**
 * Leser inn informasjon til nytt sted
 * 
 */
void Sted::nySted(string navnPaaSted){    
        
    cout << '\n' << "Beskrivelse: ";    getline(cin, stedBeskrivelse);
    stedTlfNr = lesInt("Telefonnummer: ", 11111111, 99999999);
    stedNavn = navnPaaSted;

    inntekt = 0;
    

}


/**
 * Lager ny sykkel
 * 
 * @param nr 
 */
void Sted::nySykkel(int nr) {

    Sykkel* s = new Sykkel(nr);
    s->lesData();
    ledigSykkel.push_back(s);
}


/**
 * Lager ny tralle
 * 
 * @param nr 
 */
void Sted::nyTralle(int nr) {
    
    Tralle* t = new Tralle(nr);
    t->lesData();
    ledigTralle.push_back(t);   
}


/**
 * Overforer elsparkesykler
 * 
 * @param tilSted 
 */
void Sted::overforElsparkesykkel(Sted* tilSted) {
    if (ledigElsparkesykkel.empty()) {
        cout << "Ingen ledige elsparkesykler her naa.";
    }
    else {
        int antall = lesInt("Hvor mange elsparkesykler vil du overfore: ", 1, ledigElsparkesykkel.size());

        for (int i = 0; i < antall; i++) {
            tilSted->ledigElsparkesykkel.push_back(ledigElsparkesykkel.back());
            ledigElsparkesykkel.pop_back();
        }
    }
}


/**
 * Bruker andre funksjoner til aa kunne overfore forskjellige gjenstander
 * 
 * @param tilSted 
 */
void Sted::overforGjenstand(Sted* tilSted) {
    char svar;
    svar = lesChar("Hva vil du overfore(T/S/E): ");


    switch(svar) {
        case 'T': overforTralle(tilSted);          break;
        case 'S': overforSykkel(tilSted);          break;
        case 'E': overforElsparkesykkel(tilSted);  break;
        default:                                   break;
    }

}


/**
 * Overforer sykler
 * 
 * @param tilSted 
 */
void Sted::overforSykkel(Sted* tilSted) {
    if (ledigSykkel.empty()) {
        cout << "Ingen ledige sykler her naa.";
    }
    else {
        int antall = lesInt("Hvor mange sykler vil du overfore: ", 1, ledigSykkel.size());

        for (int i = 0; i < antall; i++) {
            tilSted->ledigSykkel.push_back(ledigSykkel.back());
            ledigSykkel.pop_back();
        }
    }
}


/**
 * Overforer traller
 * 
 * @param tilSted 
 */
void Sted::overforTralle(Sted* tilSted){

    if (ledigTralle.empty()) {
        cout << "Ingen ledige traller her naa.";
    }
    else {
        int antall = lesInt("Hvor mange traller vil du overfore: ", 1, ledigTralle.size());

        for (int i = 0; i < antall; i++) {
            tilSted->ledigTralle.push_back(ledigTralle.back());
            ledigTralle.pop_back();
        }
    }
}


/**
 * Skriver ut all info om et sted
 */
void Sted::skrivSted(){
    cout << '\n' << "Stedets beskrivelse: " << stedBeskrivelse << '\n';
    cout << "Sted navn: " << stedNavn << '\n';
    cout << "Stedets telefonnummer: " << stedTlfNr << '\n';
    cout << "Stedets inntjening: " << inntekt << '\n';

    cout << "Antall traller til utleie: " << ledigTralle.size() << '\n';
    for(int i =0; i < ledigTralle.size(); i++){
        cout << ledigTralle[i]->hentGjenstandNr();
        cout << '\n';
        
    }
    cout << "Antall sykkler til utleie: " << ledigSykkel.size() << '\n';
    for(int i =0; i < ledigSykkel.size(); i++){
        cout << ledigSykkel[i]->hentGjenstandNr();
        cout << '\n';
        
    }
    cout << "Antall elsparkesykler til utleie: " << ledigElsparkesykkel.size() << '\n';
    for(int i =0; i < ledigElsparkesykkel.size(); i++){
        cout << ledigElsparkesykkel[i]->hentGjenstandNr();
        cout << '\n';
    }

    
}


/**
 * Skriver hva et sted heter og har tjent
 * 
 */
void Sted::skrivStedInntekt(){
    cout << '\n' << "Sted navn: " << stedNavn << "Inntekt: "<< inntekt;
}


/**
 * Skriver ut stedet som har ledig av noe en kunde onsker
 * 
 * @param gjenstandType 
 */
void Sted::skrivStedSomHarIgjen(type gjenstandType){
    int antall = 0;

    if (gjenstandType == tralle){
        antall = ledigTralle.size();
    }
    else if (gjenstandType == sykkel){
        antall = ledigSykkel.size();
    }
    else{antall = ledigElsparkesykkel.size();}

    if(antall > 0) {
        cout << '\n'<< stedNavn << " " << stedTlfNr << " " << "Antall ledige:" << antall;
    }
}


/**
 * skriver til fil om sted
 * 
 * @param out 
 */
void Sted::skrivTilFil(ofstream & out){
    
    out << stedBeskrivelse << '\n';
    out << stedNavn << '\n';
    out << stedTlfNr << '\n';
    out << inntekt << '\n';
    out << ledigTralle.size() << '\n';
    for(int i = 0; i < ledigTralle.size(); i++){
        ledigTralle[i]->skrivTilFil(out);
    }
    out << ledigSykkel.size() << '\n';
    for(int i = 0; i < ledigSykkel.size(); i++){
        ledigSykkel[i]->skrivTilFil(out);
    }
    out << ledigElsparkesykkel.size() << '\n';
    for(int i = 0; i < ledigElsparkesykkel.size(); i++){
        ledigElsparkesykkel[i]->skrivTilFil(out);
    }
}


/**
 * Sletter et sted
 * 
 * @param tilSted 
 */
void Sted::slettSted(Sted* tilSted){

    if (ledigTralle.empty() && ledigSykkel.empty() && ledigElsparkesykkel.empty()) {

    }
    else {
        for (int i = 0; i < ledigTralle.size(); i++) {
            tilSted->ledigTralle.push_back(ledigTralle.back());
            ledigTralle.pop_back(); 
        }
        for (int i = 0; i < ledigSykkel.size(); i++) {
            tilSted->ledigSykkel.push_back(ledigSykkel.back());
            ledigSykkel.pop_back(); 
        }
        for (int i = 0; i < ledigElsparkesykkel.size(); i++) {
            tilSted->ledigElsparkesykkel.push_back(ledigElsparkesykkel.back());
            ledigElsparkesykkel.pop_back(); 
        }
  
    }   

}


/**
 * slette gjenstand
 * 
 * @param nr 
 */
void Sted::slettGjenstand(int nr) {

    for (int i = 0; i < ledigTralle.size(); i++) {
        if (ledigTralle[i]->hentNr() == nr) {
            delete ledigTralle[i];
            ledigTralle.erase(ledigTralle.begin() + i);
            cout << "Slettet fra sted: " << stedNavn << endl;
        }
    }

    for (int i = 0; i < ledigSykkel.size(); i++) {
        if (ledigSykkel[i]->hentNr() == nr) {
            delete ledigSykkel[i];
            ledigSykkel.erase(ledigSykkel.begin() + i);
            cout << "Slettet fra sted: " << stedNavn << endl;
        }
    }

    for (int i = 0; i < ledigElsparkesykkel.size(); i++) {
        if (ledigElsparkesykkel[i]->hentNr() == nr) {
            delete ledigElsparkesykkel[i];
            ledigElsparkesykkel.erase(ledigElsparkesykkel.begin() + i);
            cout << "Slettet fra sted: " << stedNavn << endl;
        }
    }
}