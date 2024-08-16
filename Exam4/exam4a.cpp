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

void berakna_histogram_abs(string indata, int table[2][ANTAL_BOKSTAVER]);
void skriv_histogram_abs(int table[2][ANTAL_BOKSTAVER]);

//--------------------------------------------------------
// Huvudprogram:

int main() {
    // Deklarera variabler
    string rad;
    int alphabet[2][ANTAL_BOKSTAVER];

    // Fyll första raden med bokstavens ASCII värde och andra raden med antal förekomster (0)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {
            if (i == 0) {
                alphabet[i][j] = j + 97;
            } else {
                alphabet[i][j] = 0;
            }
        }
    }

    // Läs in en rad med text från tangentbordet
    cout << "Ge en rad med text:" << endl;
    getline(cin, rad);

    berakna_histogram_abs(rad, alphabet);

    skriv_histogram_abs(alphabet);

    return 0;
}

void berakna_histogram_abs(string indata, int table[2][ANTAL_BOKSTAVER]) {
    for (int i = 0; i < indata.length(); i++) {
        int currAscii = indata[i];
        // Kontrollera att tecknet är en bokstav för att utesluta allt utom a-z
        if (isalpha(currAscii)) {
            char c = indata[i];
            int lowerCase = tolower(c);
            // Subtrahera 97 från bokstavens ASCII värde då det ligger +97 från index ('a' == 97 och ska vara index 0)
            // Addera 1 till förekomsten där index är bokstaven
            table[1][lowerCase - 97] += 1;
        }
    }
}

void skriv_histogram_abs(int table[2][ANTAL_BOKSTAVER]) {
    int sum = 0;

    // Summera alla förekomster
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        sum += table[1][i];
    }

    cout << endl << "Resultat för bokstäverna A-Z" << endl << endl << "Totala antalet bokstäver: " << sum << endl << "Bokstavsfördelning:" << endl << endl;

    // Skric ut bokstav : förekomst, rad för rad
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        char letter = (table[0][i]);
        char upper = toupper(letter);
        cout << upper << ": " << table[1][i] << endl;
    }
}