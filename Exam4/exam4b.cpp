//
// Programskal till inlämningsuppgift 4 - deluppgift B
//
// Hanterar fallet med 26 bokstäver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

// Globala konstanter:

// Tips: Använd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// istället för värdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0] är frekvensen av
// bokstaven a för engelska. TOLK_HJALP[0][25] är frekvensen av
// bokstaven z för engelska.
// Arrayen är en GLOBAL KONSTANT och skall alltså ej skickas
// som parameter till den funktion som behöver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Använd exakt de funktionsnamn som finns nedan

void berakna_histogram_abs(string indata, int table[2][ANTAL_BOKSTAVER]);

void abs_till_rel(int abs[2][ANTAL_BOKSTAVER], double rel[2][ANTAL_BOKSTAVER], int &sum);

void plotta_histogram_rel(double rel[2][ANTAL_BOKSTAVER]);

void tolkning(double textData[2][ANTAL_BOKSTAVER], const double langRef[4][ANTAL_BOKSTAVER], int sum);

string namn_pa_fil();

string inlasning(string filename);

//--------------------------------------------------------
// Huvudprogram:

int main() {
    string fileName;
    string fileContents;
    int sum = 0;

    // Deklarera och fyll första raden med bokstavens ASCII värde och andra raden med antal förekomster (0)
    int alphabet[2][ANTAL_BOKSTAVER];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {
            if (i == 0) {
                alphabet[i][j] = j + 97;
            } else {
                alphabet[i][j] = 0;
            }
        }
    }

    // Deklarera och sätt alla förekomster till 0.0
    double alphabetRel[2][ANTAL_BOKSTAVER];

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        alphabetRel[1][i] = 0.0;
    }

    fileName = namn_pa_fil();

    fileContents = inlasning(fileName);

    berakna_histogram_abs(fileContents, alphabet);

    abs_till_rel(alphabet, alphabetRel, sum);

    tolkning(alphabetRel, TOLK_HJALP, sum);

    plotta_histogram_rel(alphabetRel);

    return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

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

void abs_till_rel(int abs[2][ANTAL_BOKSTAVER], double rel[2][ANTAL_BOKSTAVER], int &sum) {
    // Summera alla förekomster
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        sum += abs[1][i];
    }

    double sumDouble = sum;

    // Räkna ut relativt värde för varje bokstav, multiplicera med 100 för att få det i antal procent
    for (int i = 0; i< ANTAL_BOKSTAVER; i++) {
        rel[1][i] = 100 * ((double(abs[1][i]) / sumDouble));
    }
}

void plotta_histogram_rel(double rel[2][ANTAL_BOKSTAVER]) {
    cout << "Bokstavsfördelning:" << endl << endl;

    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        char bokstav = toupper(i + 97);

        cout << bokstav << " ";

        if (rel[1][i] != 0.0) {
            // Avrunda till närmsta 0,5%
            double rounded = round((rel[1][i]) * 2.0) / 2.0;
            // Räkna ut antalet * som ska representara förekomsten
            int count = (rounded / 0.5);
            // Konstruera och skriv ut en sträng med rätt antal *
            cout << string(count, '*');
        }

        cout << endl;
    }
}

void tolkning(double textData[2][ANTAL_BOKSTAVER], const double langRef[4][ANTAL_BOKSTAVER], int sum) {
    double sqrSum[ANTAL_SPRAK];
    double minVal = 100000.0;
    int indexBest = 0;
    string langs[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};

    // Beräkna kvadratskillnaden för varje språk
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {
            sqrSum[i] += pow((langRef[i][j] - textData[1][j]), 2.0);
        }
    }

    cout << endl << "Resultat för bokstäverna A-Z" << endl << endl;
    cout << "Totala antalet bokstäver: " << sum << endl;

    // Presentera respektive språks kvadratsumma
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        cout << langs[i] << " har kvadratsumma = " << sqrSum[i] << endl;
    }

    // Hitta minsta värdet bland kvadratsummorna
    for (int i = 0; i < 4; ++i) {
        if (sqrSum[i] < minVal) {
            minVal = sqrSum[i];
            indexBest = i;
        }
    }

    cout << "Det är mest troligt att språket är " << langs[indexBest] << endl << endl;
}

string namn_pa_fil() {
    string fileName;
    string extension = ".txt";

    // Be om filnamn
    cout << "Filnamn:" << endl;
    getline(cin, fileName);

    // Leta efter .txt ändelse
    size_t found = fileName.rfind(extension);

    // Lägg till .txt om det inte finns
    if (found == std::string::npos || found != fileName.length() - 4) {
        fileName += extension;
    }

    return fileName;
}

string inlasning(string filename) {
    string line;
    string contents;

    // Öppna fil
    ifstream file(filename);

    // Fel om filen inte finns    
    if (!file) {
        cout << "Error: Unable to open file!" << endl;
        exit( EXIT_FAILURE );
    }
    
    // Lägg till varje rad i filen till en sträng
    while (getline(file, line)) {
        contents += line;
    }

    file.close();

    return contents;
}

// -------------------------------------------------------
// Rapport om uppgiften