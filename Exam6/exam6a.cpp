#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
using namespace std;

const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

class Person {
    private:
        string namn;
        double betalat_andras; // ligger ute med totalt
        double skyldig;        // skyldig totalt

    public:
        Person() : namn(""), betalat_andras(0.0), skyldig(0.0) {}
        Person(const string &namn, double betalat_andras, double skyldig)
            : namn(namn), betalat_andras(betalat_andras), skyldig(skyldig) {}
        
        string hamtaNamn();
        double hamtaBetalat();
        double hamtaSkyldig();
        void skrivUt(ostream &os);
};

class Transaktion {
    private:
        string datum;
        string typ;
        string namn;
        double belopp;
        int antal_kompisar;
        string kompisar[MAX_PERSONER];

    public:
        Transaktion() {}
        ~Transaktion() {}
        string hamtaNamn();
        double hamtaBelopp();
        int hamtaAntalKompisar();
        bool finnsKompis(const string &namnet);
        bool lasIn(istream &is);
        void skrivUt(ostream &os);
        void skrivTitel(ostream &os);
}; 

class PersonLista {
    private:
        int antal_personer;
        Person personer[MAX_PERSONER];

    public:
        PersonLista() {}
        ~PersonLista() {}
        void laggTill(Person ny_person);
        void skrivUtOchFixa(ostream &os);
        double summaSkyldig();
        double summaBetalat();
        bool finnsPerson(const string& namn);
}; 

class TransaktionsLista {
    private:
        int antal_transaktioner;
        Transaktion transaktioner[MAX_TRANSAKTIONER];

    public:
        TransaktionsLista() {}
        ~TransaktionsLista() {}
        void lasIn(istream & is);
        void skrivUt(ostream & os);
        void laggTill(Transaktion & t);
        double totalKostnad();
        double liggerUteMed(const string &namnet);
        double arSkyldig(const string &namnet);
        PersonLista FixaPersoner();
}; 

int main()
{
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  std::ifstream is("resa.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
      cout << "5. Hur mycket ligger en viss person ute med?" << endl;
      cout << "6. Lista alla personer mm och FIXA" << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            {
              transaktioner.skrivUt(cout);
              break;
            }
          case 2:
            {
              Transaktion transaktion;
              cout << "Ange transaktion i följande format" << endl;
              transaktion.skrivTitel(cout);
              transaktion.lasIn(cin);
              transaktioner.laggTill(transaktion);
              break;
            }
          case 3:
            {
              cout << "Den totala kostnanden för resan var "
                   << transaktioner.totalKostnad() << endl;
              break;
            }
          case 4:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ar_skyldig = transaktioner.arSkyldig(namn);
              if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " är skyldig " << ar_skyldig << endl;
              break;
            }
          case 5:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ligger_ute_med = transaktioner.liggerUteMed(namn);
              if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.FixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

string Person::hamtaNamn() {
    return namn;
}

double Person::hamtaBetalat() {
    return betalat_andras;
}

double Person::hamtaSkyldig() {
    return skyldig;
}

// Formatera och skriv ut en persons data
void Person::skrivUt(ostream &os) {
    os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ". Skall ha " << std::to_string(betalat_andras - skyldig) << " från potten!" << endl;
}

string Transaktion::hamtaNamn() {
    return namn;
}

double Transaktion::hamtaBelopp() {
    return belopp;
}

int Transaktion::hamtaAntalKompisar() {
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet) {
    // Gå igenom arrayn av kompisar, returnera sant om där är en matchning
    for (int i = 0; i < antal_kompisar; i++) {
        if (kompisar[i] == namnet) {
            return true;
        }
    }

    return false;
}

bool Transaktion::lasIn(istream &is) {
    // Läs in de delarna av transaktionen vi är säkra på
    if (is >> datum >> typ >> namn >> belopp >> antal_kompisar) {
        // Om det är kompisar med i transaktionen så läser vi även in dem
        for (int i = 0; i < antal_kompisar; i++) {
            is >> kompisar[i];
        }
        return true;
    }
    // Returnera falskt om det av någon anledning inte går
    return false;
}


void Transaktion::skrivUt(ostream &os) {
    // Börja med att formatera det vi vet
    string lineToPrint = datum + " " + typ + " " + namn + " " + std::to_string(belopp) + " " + std::to_string(antal_kompisar) + " ";

    // Om det är kompisar så lägger vi öven till dem i det som ska ut
    if (antal_kompisar > 0) {
        for (int i = 0; i < antal_kompisar; i++) {
            lineToPrint += string(kompisar[i] + " ");
        }
    }

    // Skicka ut allt
    os << lineToPrint << endl;
}

void Transaktion::skrivTitel(ostream &os) {
    os << "Datum   Typ     Namn    Belopp  Antal och lista av kompisar" << endl;
}

void PersonLista::laggTill(Person ny_person) {
    // Lägg till en ny person och öka räknaren med ett
    if (antal_personer < MAX_PERSONER) { 
        personer[antal_personer] = ny_person;
        antal_personer++;
    }
}

void PersonLista::skrivUtOchFixa(ostream &os) {
    // SKriv ut för varje person
    for (int i = 0; i < antal_personer; i++) {
        personer[i].skrivUt(os);   
    }
}

double PersonLista::summaSkyldig() {
    double summaSkyldig = 0.0;

    // Gå igenom alla personer och summera skulderna
    for (int i = 0; i < antal_personer; i++) {
        summaSkyldig += personer[i].hamtaSkyldig();
    }
    return summaSkyldig;
}

double PersonLista::summaBetalat() {
    double summaBetalat = 0.0;

    // Gå igenom alla personer och gå igenom det de har betalat
    for (int i = 0; i < antal_personer; i++) {
        summaBetalat += personer[i].hamtaBetalat();
    }
    return summaBetalat;
}

bool PersonLista::finnsPerson(const string &namn) {
    // Iterera över alla personer, returnera sant när det finns en matchning, annars gå igenom hela och returnera falskt på slutet
    for (int i = 0; i < MAX_PERSONER; i++) {
        if (personer[i].hamtaNamn() == namn) {
            return true;
        }
    }
    return false;
}

void TransaktionsLista::lasIn(istream &is) {
    string line;

    // Läs in en rad från filen och skicka till Transaktion, öka på räknaren
    while (getline(is, line) && antal_transaktioner < MAX_TRANSAKTIONER) {
        std::istringstream iss(line);
        transaktioner[antal_transaktioner].lasIn(iss);
        antal_transaktioner++;
    }
}

void TransaktionsLista::skrivUt(ostream &os) {
    for (int i = 0; i < antal_transaktioner; i++) {
        // Iterera och skriv ut varje transaktion, skriv även ut rubrikerna om det är första loopen
        if (i == 0) {
            transaktioner->skrivTitel(os);
            transaktioner[i].skrivUt(os);
        } else {
            transaktioner[i].skrivUt(os);
        }
    }
}

void TransaktionsLista::laggTill(Transaktion &t) {
    // Lägg till ett objekt och öka räknaren
    if (antal_transaktioner < MAX_TRANSAKTIONER) {
        transaktioner[antal_transaktioner] = t;
        antal_transaktioner++;
    }
}

double TransaktionsLista::totalKostnad() {
    double totalKostnad = 0.0;

    // Plussa på för varje transakion
    for (int i = 0; i < antal_transaktioner; i++) {
        totalKostnad += transaktioner[i].hamtaBelopp();
    }
    return totalKostnad;
}

double TransaktionsLista::liggerUteMed(const string &namnet) {
    double liggerUteMed = 0.0;

    // Gå igenom alla transaktioner
    for (int i = 0; i < antal_transaktioner; i++) {
        int kompisar = transaktioner[i].hamtaAntalKompisar();
        // Ta bara de transaktionerna som personen i fråga har betalat för
        if (transaktioner[i].hamtaNamn() == namnet) {
            // Dela upp om det är kompisar med i transaktionen, annars ta hela själv
            if (kompisar > 0) {
                liggerUteMed += transaktioner[i].hamtaBelopp() * (double(kompisar) / (kompisar + 1));
            } else {
                liggerUteMed += transaktioner[i].hamtaBelopp();
            }
        }
    }

    return liggerUteMed;
}

double TransaktionsLista::arSkyldig(const string &namnet) {
    double skyldig = 0;

    for (int i = 0; i < antal_transaktioner; i++) {
        int kompisar = transaktioner[i].hamtaAntalKompisar();
        // Ta bara de transaktioner där det ska delas
        if (kompisar > 0) {
            if (transaktioner[i].finnsKompis(namnet)) {
                // Räkna ut andel
                skyldig += (transaktioner[i].hamtaBelopp() / double(kompisar + 1));
            }
        }
    }

    return skyldig;
}

PersonLista TransaktionsLista::FixaPersoner() {
    PersonLista personLista;

    // Gå igenom alla transaktioner
    for (int i = 0; i < antal_transaktioner; i++) {
        // Hämta datan från transaktionen
        Transaktion &transaktion = transaktioner[i];
        string namn = transaktion.hamtaNamn();
        double belopp = transaktion.hamtaBelopp();
        int antalKompisar = transaktion.hamtaAntalKompisar();

        // Kolla om personen inte finns, isåfall lägg till datan och skapa en ny person
        if (!personLista.finnsPerson(namn)) {
            double liggerUteMed = this->liggerUteMed(namn);
            double arSkyldig = this->arSkyldig(namn);
            Person nyPerson(namn, liggerUteMed, arSkyldig);
            personLista.laggTill(nyPerson);
        }

        for (int j = 0; j < antalKompisar; j++) {
            string kompisnamn = transaktion.hamtaNamn();
            if (!personLista.finnsPerson(kompisnamn)) {
                double liggerUteMed = this->liggerUteMed(kompisnamn);
                double arSkyldig = this->arSkyldig(kompisnamn);
                Person nyKompis(kompisnamn, liggerUteMed, arSkyldig);
                personLista.laggTill(nyKompis);
            }
        }
    }

    return personLista;
}