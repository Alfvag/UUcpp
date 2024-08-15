//
// Programskal till inlämningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokstäver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;


// Använd gärna denna globala konstant i programmet
// i stället för värdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan

void berakna_histogram_abs();
void skriv_histogram_abs();

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  string rad;

  // Läs in en rad med text från tangentbordet
  cout << "In:" << endl;
  getline(cin, rad);

  cout << rad << endl;
  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.  
  
 

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

void berakna_histogram_abs(string indata) {
    int alphabet[2][ANTAL_BOKSTAVER];

    for (int i = 0; i < indata.length(); i++) {
        
    }
}

void skriv_histogram_abs() {
}

  