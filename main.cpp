#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
using namespace std;

int saturationF(int input, int minNumber, int maxNumber){
if (minNumber>maxNumber){
    swap(minNumber, maxNumber);
}
input = max(input, minNumber);
input = min(input, maxNumber);
return input;
}


int main() {
    srand (time(NULL));
string INIfile = "PMA1.ini";

    int minNumber=1;
    int maxNumber=100;
    int amplitudeDisturbance = 10;
    bool saturation = false;
    string lgg = "fr";
string intro1 = "Plus ou moins, un classique de la programmation sur des entiers.\nPour commencer, on est entre ";
string intro2 = " et ";
string intro3 = ". \nDans cette version, il y a une pertubation d\'amplitude ";
string intro4 = ".\nC\'est votre tour :";
string errNumber = "Un nombre, svp !";
string itsmore = "Suite aux perturbations possibles, c\'est plus !";
string itsless = "Suite aux perturbations possibles, c\'est moins !";

    int numberToGuess = rand() % maxNumber + minNumber;
    clog << "         " << numberToGuess << endl;
    int tentative = 0;
    string tentativeS = "0";
    bool inputOk = true;
    int nbTentative = 0;
    cout << intro1;
    cout << minNumber << intro2 << maxNumber << intro3 << amplitudeDisturbance << intro4 << endl;
    do {
        do {
            inputOk = true; // Pour autre demande éventuelle.
            try {
                // cin >> tentative;
                getline(cin, tentativeS); // Pour éviter des bugs de non nombre.
                tentative = stoi(tentativeS);
                }
            catch (const std::invalid_argument& e) {
                cerr << errNumber << endl;
                inputOk = false;
                }
            }
        while (inputOk == false);

tentative = tentative - (amplitudeDisturbance/2) + (rand() % (amplitudeDisturbance));
clog << "                       " << tentative << endl;
if (saturation){
   tentative = saturationF(tentative, minNumber,maxNumber) ;
}
        if (numberToGuess > tentative) {
            cout << itsmore << endl;
         //   minNumber = max(tentative, minNumber);
            }
        if (numberToGuess < tentative) {
            cout << itsless << endl;
           // maxNumber = min(tentative, maxNumber);
            }
        nbTentative++;
        if (tentative != numberToGuess) {
         //   cout << "On est actuellement entre " << minNumber << " et " << maxNumber << "." << endl;
            }

        }
    while (tentative != numberToGuess);
    cout << "Bravo ! C\'est une belle victoire, avec seulement " << nbTentative << " tentative";
    if (nbTentative > 1) {
        cout << "s" ;
        }
    cout << "." << endl;
    return 0;
    }
