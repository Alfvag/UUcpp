#include <iostream> 
using namespace std; 

// Deklarera funktioner med lämpliga returtyper och parametrar
void skrivInfo();
int readOneNumber();
char lasOp();
void arrange(long int &a, long int &b);
int calculate(long int num1, long int num2, char op);
void writeResult(long int result);

int main() {  
    //Deklarera variabler 
    long int number1 = 0;
    long int number2 = 0;
    char op = '\0';
    long int answer = 0;

    skrivInfo(); 

    //Anropa readOneNumber två gånger till olika variabler för att få de två talen
    number1 = readOneNumber(); 

    number2 = readOneNumber(); 

    op = lasOp(); 

    arrange(number1, number2); 

    answer = calculate(number1, number2, op); 

    writeResult(answer); 

    return 0; 
}

void skrivInfo() {
    cout << "Mata in två tal samt en metod för beräkning:" << endl;
    cout << "a - Adderar alla tal i intervallet mellan dina två val" << endl;
    cout << "m - Multiplicerar alla tal i intervallet mellan dina två val" << endl;
    cout << "k - Kvadrerar och adderar summan av talen i ditt intervall" << endl;
}
    

//Läs in numret
int readOneNumber() {
    int tal = 0;
    
    cout << "Mata in ett tal: ";
    cin >> tal;
    
    return tal;
}

// Definera "tom" variabel och be om räknesättet
char lasOp() {
    char op = '\0';

    cout << "Metod: ";
    cin >> op; 

    return op;
}

//Sortera talen där nummer1/a ska vara minst och 2/b störst. Använder referensparameterar för att returnera två tal
void arrange(long int &a, long int &b) {
    int temp = 0;

    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
}

int calculate(long int num1, long int num2, char op) {
    int result = 0;
    int sum = 0;

    switch(op) {
        case 'a':
            // Om talen är samma så är resultatet bara ett av de talen
            if (num1 == num2) {
                result = num1;
            } else {
                // For-loop i intervallet där i adderas till sum
                for (int i = num1; i <= num2; i++) {
                    sum += i;
                }
                result = sum;
            }

            break;
        case 'm':
            for (int i = num1; i <= num2; i++) {
                // Då sum är definerat till 0 från början så sätter vi den till det första numret i intervallet innan vi multiplicerar med varje tal i intervallet
                if (i == num1) {
                    sum = num1;
                } else {
                    sum *= i;
                }
            }
            result = sum;
            break;
        case 'k':
            // Kvadrera i och lägg till i sum
            for (int i = num1; i <= num2; i++) {
                sum += (i * i);
            }

            result = sum;
            break;
    }

    return result;
}

void writeResult(long int answer) {
    cout << "Resultatet av beräkningen: " << answer << endl;
}