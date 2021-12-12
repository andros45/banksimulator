/*
Denna banksimulator simulerar en bank där användaren kan välja mellan fem olika funktioner.
Insättning, Uttag, Saldo, Räntebetalning och Avslut.

Programmet håller reda på saldot mellan de olika transaktionerna.

Räntebetalningen räknar ut hur många månader det tar innan ett önskat målsaldo uppnås
utifrån angiven ränta, aktuellt saldo och storlek på månadsinsättningen. 
*/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>

using namespace std;

// Skapa variabel för menyvalet. Typen char räcker eftersom den bara ska lagra ett tecken

char menyVal;

// Skapa variabler för insatt belopp, uttaget belopp, månadsinsättning och räntesats
// Typen double är vald för att kunna hantera stora tal med decimaler

double insBelopp = 0, uttagsBelopp = 0;
double mIns, rSats;

// Skapa variabel som håller antalet år vi måste spara för att uppnå ett målsaldo
// Typen int är vald eftersom variabeln ska innehålla antalet hela år

int antalAr = 0;

// Skapa variabler för saldo och målsaldo. Skapa även en variabel för att hålla ett tillfälligt saldo
// som kan användas i beräkningarna.
// Typen double är vald för att kunna hantera stora tal med decimaler 

double tempSaldo = 0, saldo = 0, malSaldo;

// Variabel för att hålla en tillfällig sträng för att kontrollera vad användaren har matat in

string tempString;

// Funktion för att kontrollera om inmatat värde är en siffra

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
    return true;
}

// Funktion för att hantera interrupt från användaren
void signal_callback_handler(int signum) {
   cout << "\n\nJaså minsann! Du tryckte CTRL+C och skickade signal nr: " << signum << "\n\n";
   exit(signum);
}

// Funktionen main() returnerar ett heltalsvärde (int)

int main () {

    // Registrera signalhanteraren och hantera CTRL+C (SIGINT)
    signal(SIGINT, signal_callback_handler);

    // While loop för att hantera huvudmenyn
    // Så länge användaren inte väljer att avsluta kommer huvudmenyn att skrivas ut på nytt

    while (menyVal != 'A') {

        // Rensa skärmen

        cout << "\033[2J\033[1;1H";
        cout << "\n";

        // Skriv ut huvudmeny

        cout << "[I]nsättning\n\n";
        cout << "[U]ttag\n\n";
        cout << "[S]aldo\n\n";
        cout << "[R]äntebetalning\n\n";
        cout << "[A]vsluta\n\n";

        // Läs in användarens menyval och lagra svaret i en variabel

        cout << "\n\nAnge menyval: ";
        cin >> tempString;

        // Kontrollera så att endast ett tecken angess

        if(tempString.length() != 1) {
            cout << "Ogiltigt val! Endast ett tecken får anges! I, U, S, R eller A är tillåtna!";
            menyVal = 'x';
        } else {
            menyVal = tempString[0];
        }

        // En switch för att hantera alla de olika menyvalen

        switch (menyVal) {

            // Om användaren väljer insättning skriver vi ut aktuellt saldo och 
            // ber användaren att ange beloppet som ska sättas in. Det nya saldot
            // skrivs ut på skärmen för att bekräfta insättningen.

            case 'I': case 'i':
                cout << "\n\nAktuellt saldo är: ";
                cout << saldo;
                cout << "\n\nAnge belopp att sätta in: ";
                cin >> tempString;
                if (check_number(tempString))
                    insBelopp = stoi(tempString);
                else {
                    cout << "Du måste ange belopp med siffror och utan decimaler!";
                    cout << "\n\nTryck 0 för att komma vidare\n";
                    cin >> tempString;
                    break;
                }
                saldo = saldo + insBelopp;
                cout << "\nDitt saldo är nu: ";
                cout << saldo;
                cout << "\n\nTryck 0 för att komma vidare\n";
                cin >> tempString;
                break;

            // Om användaren väljer uttag skriver vi ut aktuellt saldo och 
            // ber användaren att ange beloppet som ska tas ut. Det nya saldot
            // skrivs ut på skärmen för att bekräfta uttaget.

            case 'U': case 'u':
                cout << "\n\nAktuellt saldo är: ";
                cout << saldo;
                cout << "\n\nAnge belopp att ta ut: ";
                cin >> tempString;
                if (check_number(tempString))
                    uttagsBelopp = stoi(tempString);
                else {
                    cout << "Du måste ange belopp med siffror och utan decimaler!";
                    cout << "\n\nTryck 0 för att komma vidare\n";
                    cin >> tempString;
                    break;
                }
                saldo = saldo - uttagsBelopp;
                cout << "\nDitt saldo är nu: ";
                cout << saldo;
                cout << "\n\nTryck 0 för att komma vidare\n";
                cin >> tempString;
                break;

            // Om användaren väljer saldo skriver vi ut det aktuella saldot. 

            case 'S': case 's':
                cout << "\nDitt saldo är: ";
                cout << saldo;
                cout << "\n\nTryck 0 för att komma vidare\n";
                cin >> tempString;
                break;   

            // Om användaren väljer räntebetalning frågar vi efter ett antal 
            // olika parametrar och räknar därefter ut hur lång tid det tar
            // att nå önskat målsaldo.

            case 'R': case 'r':
                cout << "\nHur mycket pengar är ditt mål att ha på kontot?: ";
                cin >> tempString;
                if (check_number(tempString))
                    malSaldo = stoi(tempString);
                else {
                    cout << "Du måste ange belopp med siffror och utan decimaler!";
                    cout << "\n\nTryck 0 för att komma vidare\n";
                    cin >> tempString;
                    break;
                }
                cout << "\nHur mycket kan du sätta in varje månad?: ";
                cin >> tempString;
                if (check_number(tempString))
                    mIns = stoi(tempString);
                else {
                    cout << "Du måste ange belopp med siffror och utan decimaler!";
                    cout << "\n\nTryck 0 för att komma vidare\n";
                    cin >> tempString;
                    break;
                }
                cout << "\nAnge räntesats i procent: ";
                cin >> tempString;
                if (check_number(tempString))
                    rSats = stoi(tempString);
                else {
                    cout << "Du måste ange belopp med siffror och utan decimaler!";
                    cout << "\n\nTryck 0 för att komma vidare\n";
                    cin >> tempString;
                    break;
                }
                cout << "\nDitt nuvarande saldo är: ";
                cout << saldo;
                tempSaldo = saldo;

                // Här används formeln för att räkna ut hur många år det tar
                // att uppnå önskat målsaldo.

                while (tempSaldo < malSaldo) {
                        tempSaldo = (tempSaldo * (1 + rSats / 100) + (mIns * 12));
                        antalAr++;
                }
                cout << "\nDu kommer att uppnå ditt målsaldo efter " << antalAr << " år";
                cout << "\nDitt saldo efter " << antalAr << " år är " << tempSaldo;
                cout << "\n\nTryck 0 för att komma vidare\n";
                cin >> tempString;
                break;

            // Om användaren väljer att avsluta tackar vi för användningen och
            // avslutar hela programmet.

            case 'A': case 'a':
                cout << "\n\nTack för att du använde banksimulatorn!\n\n";
                return 0;   

            // Om användaren anger ett ogiltigt val skriver vi ut ett felmeddelande och
            // användaren skickas tillbaka till huvudmenyn. 

            default:
                cout << "\n\nOgiltigt menyval! Försök igen";
                cout << "\n\nTryck 0 för att komma vidare\n";
                cin >> tempString;
                break;
                
            

        }
    }

    // Returnera alltid siffran 0
    // Framtida versioner kan tänkas returnera andra siffror 
    // beroende på vad som händer i programmet, t.ex. felkoder

    return 0;
}