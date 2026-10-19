/**
 * @file funksjoner.cpp
 * 
 * @author Stine Kalleli
 * @brief 
 * @version 0.1
 * @date 19.03.2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */



#include "funksjoner.h"
#include <iostream>

using namespace std;

/**
 * Skriver ut menyen
 */
void skrivMeny(){
    
    cout << '\n' << "Følgende kommandoer er tilgjengelig:" << '\n';
    cout << " K  N" << '\n';
    cout << " K  A" << '\n';
    cout << " K  1  <knr>" << '\n';
    cout << " K  H  <knr>" << '\n';
    cout << " K  L  <knr>" << '\n';
    cout << "*K  S  <knr>" << '\n';
    cout << " S  N" << '\n';
    cout << " S  A" << '\n';
    cout << " S  1  <stedID>" << '\n';
    cout << " S  T" << '\n';
    cout << " S  I" << '\n';
    cout << " S  O" << '\n';
    cout << "*S  S  <stedID>" << '\n';
    cout << " G  N" << '\n';
    cout << " G  F  <gjenstandnr>" << '\n';
    cout << "*G  S  <gjenstandnr>" << '\n';
    cout << " Q - Quit / avslutt" << '\n';

};