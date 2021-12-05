#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;

int saturationF(int numberSaturation, int &minNumber, int &maxNumber) {
    if (minNumber>maxNumber) {
        swap(minNumber, maxNumber);
        }
    numberSaturation = max(numberSaturation, minNumber);
    numberSaturation = min(numberSaturation, maxNumber);
    return numberSaturation;
    }



int main() {
    srand (time(NULL));
    string cfgFile = "PMA1.cfg";
    string errFile1 =  "Impossible to open the file ";
    string errFile2 =  "!";
    int minNumber=0;
    int maxNumber=100;
    bool saturation = false;
    string lgg = "en";
    int amplitudeDisturbance = 10;
    cin.clear();
    ifstream ReadCfg ( cfgFile.c_str(), ios::in );
    if ( !ReadCfg ) {
        cerr << errFile1 << cfgFile << errFile2 << endl;
        }
    else {
        string line;
        while ( getline ( ReadCfg, line ) ) {
            if ( line.substr ( 0, 4 ) == "lgg=" ) {
                lgg =   line.substr (4,line.size()-5); // End of line character.
                }
            if ( line.substr ( 0, 10 ) == "minNumber=" ) {
                minNumber= stoi(line.substr (10));
                }
            if ( line.substr ( 0, 10 ) == "maxNumber=" ) {
                maxNumber= stoi(line.substr (10));
                }
            if ( line.substr ( 0, 21 ) == "amplitudeDisturbance=" ) {
                amplitudeDisturbance= stoi(line.substr (21));
                }
            if ( line.substr ( 0, 10 ) == "minNumber=" ) {
                minNumber= stoi(line.substr (10));
                }
            if ( line.substr ( 0, 15 ) == "saturation=true" ) { // End of line character.
                saturation=true;
                }
            if (  line.substr ( 0, 15 ) == "saturation=false" ) {
                saturation=false;
                }
            }
        ReadCfg.close();
        }

    amplitudeDisturbance = saturationF(amplitudeDisturbance, minNumber, maxNumber); // Mainely to swap maxNumber and minNumber, if needed.

    // Will be corrected, if file will be readable:
    string intro0 = "More or less, a classic of integer programming.";
    string intro1 = "First, we are between";
    string intro2 = "and";
    string intro3 = "In this version, there is a pertubation:";
    string intro4 = "of amplitude, to make it more fun. Your proposal, please?";
    string errNumber = "A whole number, please!";
    string itsMore = "Because of the possible disturbances, it's more!";
    string itsLess = "Because of the possible disturbances, it's less!";
    string congratulations1 = "Congratulations! It's a magnificent victory against the pertubation, with just one single attempt!";
    string congratulations2a = "Well done! It's a good victory against the pertubations, with only";
    string congratulations2b = "attempts!";

    string lggFile = lgg + ".lgg";
    ifstream ReadLgg ( lggFile.c_str(), ios::in );
    if ( !ReadLgg ) {
        cerr << errFile1 + lggFile + errFile2 << endl;
        }
    else {
        string line;
        while ( getline ( ReadLgg, line ) ) {
            if ( line.substr ( 0, 7 ) == "intro0=" ) {
                intro0 =   line.substr (7,line.size()-8); // End of line character.
                }
            if ( line.substr ( 0, 7 ) == "intro1=" ) {
                intro1 =   line.substr (7,line.size()-8); // End of line character.
                }
            if ( line.substr ( 0, 7 ) == "intro2=" ) {
                intro2 =   line.substr (7,line.size()-8); // End of line character.
                }
            if ( line.substr ( 0, 7 ) == "intro3=" ) {
                intro3 =   line.substr (7,line.size()-8); // End of line character.
                }
            if ( line.substr ( 0, 7 ) == "intro4=" ) {
                intro4 =   line.substr (7,line.size()-8); // End of line character.
                }
            if ( line.substr ( 0, 8 ) == "itsMore=" ) {
                itsMore =   line.substr (8,line.size()-9); // End of line character.
                }
            if ( line.substr ( 0, 8 ) == "itsLess=" ) {
                itsLess =   line.substr (8,line.size()-9); // End of line character.
                }
            if ( line.substr ( 0, 17 ) == "congratulations1=" ) {
                congratulations1 = line.substr (17,line.size()-18); // End of line character.
                }
            if ( line.substr ( 0, 18 ) == "congratulations2a=" ) {
                congratulations2a = line.substr (18,line.size()-19); // End of line character.
                }
            if ( line.substr ( 0, 18 ) == "congratulations2b=" ) {
                congratulations2b = line.substr (18,line.size()-19); // End of line character.
                }
            }
        ReadLgg.close();
        }
    int numberToGuess = rand() % maxNumber + minNumber;
    int tentative = 0;
    string tentativeS = "0";
    bool inputOk = true;
    int nbTentative = 0;
    cout  << intro0<< endl;
    cout << intro1;
    cout << " " << minNumber << " " << intro2 << " " << maxNumber <<"."<< endl;
    cout <<  intro3 << " " << amplitudeDisturbance << intro4 << endl;
    do {
        do {
            inputOk = true; // To ask later, maybe.
            try {
                getline(cin, tentativeS); // To avoid bug of "not a number".
                tentative = stoi(tentativeS);
                }
            catch (const std::invalid_argument& e) {
                cerr << errNumber << endl;
                inputOk = false;
                }
            }
        while (inputOk == false);

        if (amplitudeDisturbance!=0) {
            tentative = tentative - (amplitudeDisturbance/2) + (rand() % (amplitudeDisturbance));
            }
        if (saturation) {
            tentative = saturationF(tentative, minNumber, maxNumber) ;
            }
        if (numberToGuess > tentative) {
            cout << itsMore << endl;
            }
        if (numberToGuess < tentative) {
            cout << itsLess << endl;
            }
        nbTentative++;
        }
    while (tentative != numberToGuess);

    if (nbTentative == 1) {
        cout << congratulations1;
        }
    else {
    cout << congratulations2a << " " << nbTentative << " " << congratulations2b << endl;
}
    return 0;
    }
