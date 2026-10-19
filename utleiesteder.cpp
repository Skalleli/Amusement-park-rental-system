/**
 * @file utleiesteder.cpp
 * @author Stine Kalleli
 * @brief 
 * @version 0.1
 * @date 17.03.2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "utleiesteder.h"
#include "sted.h"
#include "kunder.h"
#include "kunde.h"

#include <string>
#include <iostream>

using namespace std;

extern Utleiesteder gStedbase;
extern Kunder gKundebase;


/**
 * finner gjenstand i utleiesteder
 * 
 * @param nr 
 * @return true 
 * @return false 
 */
bool Utleiesteder::finnGjenstand(int nr){
    for (const auto& val : stedNavn) {

        if (val.second->finnGjenstand(nr)){
            return true;
        }
    }
    return false;

}



/**
 * Utforer alt, alle alternativene for sted og gjenstand blir utfort her
 * 
 * @param valg 
 */
void Utleiesteder::handling(char valg){

    int nr;
    string svar;
    type gjenstand;
    string tilSted;
    char    valg2,
            valg3;
    bool funnetISted;
    bool funnetIKunde;
    
    

    
    if(valg =='S'){
        valg2 = lesChar("\nKommando: ");
        switch(valg2)  {
            case 'N': nyUtleiested();               break;
            case 'A': skrivAlleSted();              break;
            case '1': skrivSted();
                                                    break;
            case 'T': skrivAlleStedInntekt();       break;  
            case 'I': cout << "Hvilke gjenstand ser du etter: "; getline(cin, svar);
                
                if (svar == "tralle") {
                    gjenstand = tralle;
                }
                else if (svar == "sykkel") {
                    gjenstand = sykkel;
                }
                else if (svar == "elsparkesykkel") {
                    gjenstand = elsparkesykkel;
                }
                else {
                    cout << "Ugyldig type\n";
                }


                for (const auto & val : stedNavn){               //range-based for løkke
                    val.second->skrivStedSomHarIgjen(gjenstand);
                }                                   break;  
            case 'O': seOmStedFinsOgOverforer();    break;
            case 'S': slettSted();
                                                    break;

            default:   cout << "Ugyldig kommando. Prøv igjen";      
                                                    break;
        }

    }

    else{
        valg2 = lesChar("\nKommando: ");
        switch(valg2)  {
            case 'N': seOmStedFinsOgNyGjenstand();  break;

            case 'F':
                nr = lesInt("Hvilket gjenstandnr: ", 1, sisteNr);

                

                funnetISted = gStedbase.finnGjenstand(nr);
                funnetIKunde = gKundebase.finnGjenstandKunder(nr); 

                if(!funnetISted){
                    cout << '\n' << "Ikke funnet i et sted";
                }
                if(!funnetIKunde){
                    cout << '\n' << "Ikke funnet i en kunde";
                }
                
                                                    break;
                            
            case 'S': nr = lesInt("Hvilken gjenstand vil du slette: ", 1, sisteNr);   
                valg3 = lesChar("Vil du virkelig gjore dette(J/N):");
                
                if(valg3 == 'J'){
                    
                    gStedbase.slettGjenstand(nr);
                }
                                                    break;




        default:   cout << "Ugyldig kommando. Prøv igjen";      
                                                    break;
        }
    

    }

}



/**
 * Leser fra fil
 * 
 */
void Utleiesteder::lesFraFil(){
    ifstream inn("STEDER.DTA");
    int antallSteder;
    Sted*  sted;
    
    inn >> sisteNr;
    inn >> antallSteder;
    for(int i = 0; i< antallSteder; i++){
        sted = new Sted(inn);
        stedNavn[sted->hentNavn()] = sted;
    }
    inn.close();
}


/**
 * Lager en ny gjenstand ett sted
 * 
 */
void Utleiesteder::nyGjenstandSted(){
    string svar;
    skrivNavnPaaSted();
    

    cout << "Hvilket sted vil du legge inn en ny gjenstand: ";
    getline(cin, svar);
    for(const auto & val : stedNavn){
        if (val.first == svar){
            sisteNr ++;
            val.second->nyGjenstand(sisteNr);
        }
    }
    cout << "Fant ikke stedet du leter etter. Prøv igjen.";


}


/**
 * Lager et nytt sted
 * 
 */
void Utleiesteder::nyUtleiested(){
    string navnPaaSted;
    cout << "Hva skal stedet hete: ";
    getline(cin, navnPaaSted);
    cout << '\n';
    stedNavn[navnPaaSted] = new Sted();          //i map-en på keyen stedNavn, legg inn peker til nytt Sted
    stedNavn[navnPaaSted]->nySted(navnPaaSted);

}


/**
 * Se om stedet finnes, og deretter laaner gjenstand derifra
 * 
 */
void Utleiesteder::seOmStedFinsOgLaaner(Kunde* kundePeker){
    string sted;
    cout << "Hvilke sted vil du laane fra: "; getline(cin, sted);
    auto it = stedNavn.find(sted);
    if(it != stedNavn.end()){
        it->second->laanGjenstand(kundePeker);
    }    

}


/**
 * Se om stedet finnes, og deretter leverer tilbake gjenstand dit
 * 
 * @param kundePeker 
 */
void Utleiesteder::seOmStedFinsOgLeverer(Kunde* kundePeker){
    string sted;
    cout << "Hvor vil du legge alle gjenstandene dine: "; getline(cin, sted);
    auto it = stedNavn.find(sted);
    if(it != stedNavn.end()){
        it->second->leverGjenstand(kundePeker);
    }
}


/**
 * Se om stedet finnes, og deretter opretter en ny gjenstand
 * 
 */
void Utleiesteder::seOmStedFinsOgNyGjenstand(){
    string sted;
    cout << "Hvor vil du lage den nye gjenstanden: ";
    getline(cin, sted);

    auto it = stedNavn.find(sted);
    if(it != stedNavn.end()){
        sisteNr++;
        it->second->nyGjenstand(sisteNr);
    }
    else{
        cout << "Det stedet finnes ikke";
    }
}


/**
 * Se om stedene finnes, og deretter overforer gjenstand fra sted til sted
 * 
 */
void Utleiesteder::seOmStedFinsOgOverforer(){
    string fraSted;
    string tilSted;

    cout << "Hvilke sted vil du flytte fra: "; getline(cin, fraSted);
    cout << '\n';
    auto fraIt = stedNavn.find(fraSted);
    if(fraIt != stedNavn.end()){
        cout << "Hvilke sted vil du flytte til: "; getline(cin, tilSted);
        auto tilIt = stedNavn.find(tilSted);
        if(tilIt != stedNavn.end()){

            fraIt->second->overforGjenstand(tilIt->second);
           
        }   
    }   

}


/**
 * Skriver alle stedene
 * 
 */
void Utleiesteder::skrivAlleSted(){

    for (const auto & val : stedNavn){               //range-based for løkke
        cout << '\t' << val.first << '\t'; 
        val.second->skrivSted();
    
    }
}


/**
 * Skriver alle stedene sine navn og inntekt
 * 
 */
void Utleiesteder::skrivAlleStedInntekt(){
    for (const auto & val : stedNavn){               //range-based for løkke
        cout << '\t' << val.first << '\t'; 
        val.second->skrivStedInntekt();
    
    }
}


/**
 * Skriver navn på stedene
 * 
 */
void Utleiesteder::skrivNavnPaaSted(){
    for (const auto & val : stedNavn){               //range-based for løkke
        cout << '\t' << val.first << '\t';

    }
}


/**
 * skriver alt om et sted
 * 
 */
void Utleiesteder::skrivSted(){
    string sted;
    cout << "Hvilket sted vil du se:: "; getline(cin, sted);
    auto it = stedNavn.find(sted);
    if(it != stedNavn.end()){
        it->second->skrivSted();
    }
}



/**
 * Skriver til fil
 * 
 */
void Utleiesteder::skrivTilFil(){
    int antallSteder = stedNavn.size();

    ofstream out("STEDER.DTA");
    out << sisteNr << '\n';
    out << antallSteder << '\n';
    for (const auto& val : stedNavn) {
        val.second->skrivTilFil(out);
    }

    out.close();

}


/**
 * sletter gjenstand
 * 
 * @param nr 
 */
void Utleiesteder::slettGjenstand(int nr) {

    for (const auto& val : stedNavn) {
        val.second->slettGjenstand(nr);
    }

    cout << "Hvis gjenstanden var hos en kunde, saa ble den ikke slettet.\n";
}


/**
 * sletter sted 
 * 
 */
void Utleiesteder::slettSted(){
    char valg;
    string sted;
    string tilSted;

    valg = lesChar("Vil du virkelig gjøre dette(J/N):");
    if (valg == 'J'){
        cout << "Hvilket sted vil du slette: "; getline(cin, sted);
        auto it2 = stedNavn.find(sted);
        if(it2 != stedNavn.end()){
            cout << "Hvilke sted vil du flytte til: "; getline(cin, tilSted);
            auto tilIt = stedNavn.find(tilSted);
                if(tilIt != stedNavn.end()){
                    it2->second->slettSted(tilIt->second);
                }

        }

        delete it2->second; 
        stedNavn.erase(sted);

    }


}