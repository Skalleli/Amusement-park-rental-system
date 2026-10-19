
/**
 * 
 */

#include <iostream>

#include "kunder.h"
#include "kunde.h"
#include "LesData3.h"
#include "utleiesteder.h"

using namespace std;


extern Utleiesteder gStedbase;


/**
 * Finner gjenstand i alle kunder
 * 
 * @param nr 
 * @return true 
 * @return false 
 */
bool Kunder::finnGjenstandKunder(int nr) {
    for (auto it = kundeliste.begin(); it != kundeliste.end(); it++) {
        if((*it)->finnGjenstand(nr)){
            return true;
        }
    }
    return false;
    
}


/**
 * Denne gjør alt for kunde menyen, alle valgene som tas der blir sendt hit
 * 
 */
void Kunder::handling(){
    char valg;
    int kundeNr;
    Kunde* kundePeker;
    valg = lesChar("\nKommando: ");
    switch(valg)  {
        case 'N': nyKunder();           break;
        case 'A': skrivKunder();        break;
        case '1': kundeNr = lesInt("Hvilke kunde nr vil du se: ", 1, kundeliste.size());
            for (auto kundeIt = kundeliste.begin(); kundeIt  != kundeliste.end(); kundeIt++){
                if ((*kundeIt)->hentKundeNr() == kundeNr){
                    (*kundeIt)->skrivKundeOgGjenstander();
                }
            }
                                        break;
        case 'H': kundeNr = lesInt("Hvilke kunde vil du hente gjenstander til: ", 1, kundeliste.size());
            for (auto kundeIt = kundeliste.begin(); kundeIt  != kundeliste.end(); kundeIt++){
                if ((*kundeIt)->hentKundeNr() == kundeNr){
                    kundePeker = (*kundeIt);
                }
            }
            gStedbase.skrivNavnPaaSted();
            gStedbase.seOmStedFinsOgLaaner(kundePeker);

            
                                        break;
        case 'L': kundeNr = lesInt("Hvilket nummer har kunden som skal levere tilbake: ", 1, kundeliste.size());    break;
            for (auto kundeIt = kundeliste.begin(); kundeIt  != kundeliste.end(); kundeIt++){
                if ((*kundeIt)->hentKundeNr() == kundeNr){
                    kundePeker = (*kundeIt);
                    gStedbase.skrivNavnPaaSted();
                    gStedbase.seOmStedFinsOgLeverer(kundePeker);
                    //levere tilbake alt denne kunden har tilbake til sted
                }
            }
        case 'S':     
            
        
            kundeNr = lesInt("Hvilken kunde vil du slette: ", 1, kundeliste.size());
            for (auto kundeIt = kundeliste.begin(); kundeIt  != kundeliste.end(); kundeIt++){
                if ((*kundeIt)->hentKundeNr() == kundeNr){
                    kundePeker = (*kundeIt);
                }
            }

            valg = lesChar("Er du helt sikker på at du vil slette kunden (J/N): ");
            if (valg == 'J'){
                gStedbase.seOmStedFinsOgLeverer(kundePeker);   
            
                delete kundePeker;
                kundeliste.remove(kundePeker);
            }


            
            
            
            break;  //slette kunde



    default:   cout << "Ugyldig kommando. Prøv igjen";      break;
    }
    

}



/**
 * Leser fra fil
 * 
 */
void Kunder::lesFraFil(){
    ifstream inn("KUNDER.DTA");
    int antallKunder;
    Kunde* kunde;
    
    inn >> sisteNr;
    inn >> antallKunder;
    for(int i = 0; i< antallKunder; i++){
        kunde = new Kunde(inn);
        kundeliste.push_back(kunde);
    }
    inn.close();
}


/**
 * Lager nye kunder, og fyller inn informasjonen til ny kunde
 * 
 */
void Kunder::nyKunder() {

    sisteNr += 1;
    cout << "Dette er kunde nr. " << sisteNr << '\n';

    Kunde* nyKunder;
    nyKunder = new Kunde;
    nyKunder->nyKunde(sisteNr);
    kundeliste.push_back(nyKunder);

}


/**
 * Skriver ut kunder, og stopper på 20
 * 
 */
void Kunder::skrivKunder(){
    int teller = 0;

    for (auto kundeIt = kundeliste.begin(); kundeIt != kundeliste.end(); kundeIt++){
        (*kundeIt)->skrivKunde();           // /iterator kundeIt peker på vector, som peker på et kundeobjekt
                                            // Bruker * for å hente ut det vector pekeren peker på, altså kunde objektet@
        teller++;

        if(teller==20){
            getchar();
        }
    }

}


/**
 * Skriver til fil
 * 
 */
void Kunder::skrivTilFil(){
    ofstream out("KUNDER.DTA");
    
    out << sisteNr << '\n';
    out << kundeliste.size() << '\n';
    for (auto kundeIt = kundeliste.begin(); kundeIt != kundeliste.end(); kundeIt++){
        (*kundeIt)->skrivTilFil(out);         
    }
    out.close();

}