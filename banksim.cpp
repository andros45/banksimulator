/* 
Applikation: Banksimulator
Skapad av: Emelie Johansen
Skapad: 2021-12-05
Version: 1.0.0
*/

/*
Denna banksimulator simulerar en bank där användaren kan välja mellan fem olika funktioner.
Insättning, Uttag, Saldo, Räntebetalning och Avslut.

Programmet håller reda på saldot mellan de olika transaktionerna.

Räntebetalningen räknar ut hur många månader det tar innan ett önskat målsaldo uppnås
utifrån angiven ränta, aktuellt saldo och storlek på månadsinsättningen. 
*/

#include <iostream>

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

// Funktionen main() returnerar ett heltalsvärde (int)

int main () {

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
                    cin >> insBelopp;
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
                    cin >> insBelopp;
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
                cin >> malSaldo;
                cout << "\nHur mycket kan du sätta in varje månad?: ";
                cin >> mIns;
                cout << "\nAnge räntesats i procent: ";
                cin >> rSats;
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

/* 
Utvärdering

Banksimulatorn var intressant att utforma eftersom den innehåller så många olika delar.
Huvudmenyn med sina olika alternativ valde jag att göra med hjälp av en switch som
hanterar de olika funktionerna i simulatorn. Det gör att jag har fått en förståelse för
hur jag enkelt kan komplettera med ytterligare funktioner i framtida versioner av simulatorn.

Jag bedömer att användarvänligheten är hög eftersom alla menyval är självförklarande och att 
simulatorn hela tiden skriver ut information på skärmen åt användaren. 

Banksimulatorn innehåller flera verklighetstrogna funktioner som används i riktiga banker.
Funktioner som insättning, uttag och saldobesked finns på alla banker.
Att räkna ut antal år det tar att spara ihop till ett visst belopp var väldigt intressant för
mig eftersom jag då enkelt kan räkna på olika scenarion. 

På en riktig bank sparas saldot för varje kund även om programmet avslutas men i den här
simulatorn nollställs saldot vid varje avslut och den kan bara hantera en kund.
Framtida versioner av simulatorn skulle kunna be användaren att logga in och spara alla 
transaktioner i en fil som lagras på hårddisken.

Framtida versioner bör också kompletteras med robusta felkontroller som kontrollerar alla
inmatningar användaren gör innan variablarna används i simulatorn. Oväntade fel behöver
också fångas upp och hanteras på ett snyggt sätt så att informativa felmeddelanden skrivs
ut på skärmen.
*/