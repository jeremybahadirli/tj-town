#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

void WelcomeScreen();
void ClearScreen();
void MainMenu();
void FarmMenu();
void Farm(int risk);
void Bank();
void GameOver(string message);

const string currency = "TJ-BUCK";

int bucks = 0;
int daniBucks = 29;
bool cheater = false;

int lastRisk = 0;
int riskCount = 0;

int main(void)
{
    WelcomeScreen();
    MainMenu();
}

void WelcomeScreen() {
    string input = "";
    string inputCheck = "SILLY";
    string cheatCode = "TJISLIFE";

    ClearScreen();
    cout << "Tj Town version 1.5" << endl;
    cout << "Created by Jeremy Bahadirli on 04/14/16" << endl << endl << endl << endl;
    cout << "Welcome to Tj Town!!" << endl << endl;
    cout << "The point of the game is to become the wealthiest man in Tj Town. It will not be";
    cout << "very difficult because there is only one citizen in the town and his name is . ." << endl;
    cout << "TJJTJTJTJTJTJTJTJTJTJ!!!!!!!!!!!!!!" << endl << endl;
    cout << "Just kidding, there are two people in the town and the other person is Daniela" << endl;
    cout << "(whose dog is named Doggo) and she has " << daniBucks << " " << currency << "S. Good Luck." << endl << endl;
    cout << "You can go to the Farm to earn " << currency << "S, and head to the" << endl;
    cout << "Bank to cash in and inevitably lose." << endl << endl;
    cout << "Type \"" << inputCheck << "\" to begin." << endl << endl;

    bool loop = true;

    while (loop == true) {

        cin >> input;

        if (input == inputCheck) {
            loop = false;
        } else if (input == cheatCode) {
            cheater = true;
            loop = false;
        } else {
            GameOver("You suck.");
    WelcomeScreen();
        loop = false;
        }
    }
}

void ClearScreen() {
    for (int i = 0; i < 50; i++) {
        cout << endl;
    }
}

void MainMenu() {
        while (true) {

        char input = ' ';

        ClearScreen();
        cout << "----------------" << endl << endl;
        cout << " TJ Town Square" << endl << endl;
        cout << "----------------" << endl << endl << endl;
        cout << "1. Farm" << endl;
        cout << "2. Bank" << endl;
        cout << "Entry: ";

        do {
            cin >> input;
        } while ((int) input < 49 || (int) input > 50);

        switch (input) {
            case '1':
                FarmMenu();
                break;
            case '2':
                Bank();
                break;
        }
    }
}

void FarmMenu() {
    char input = ' ';
    bool failedInput = false;

    ClearScreen();
    cout << "----------------" << endl << endl;
    cout << "      Farm" << endl << endl;
    cout << "----------------" << endl << endl << endl;
    cout << "1. High Risk" << endl;
    cout << "2. Medium Risk" << endl;
    cout << "3. Low Risk" << endl;
    cout << "Entry: ";

    do {
        cin >> input;
        if (riskCount >= 5 && (int) input == lastRisk) {
            cout << "Too many repeated risks." << endl;
            failedInput = true;
        } else {
            failedInput = false;
        }
    } while ((int) input < 49 || (int) input > 51 || failedInput == true);

    if (input == lastRisk) {
        riskCount++;
    } else {
        riskCount = 0;
    }

    lastRisk = input;

    switch (input) {
        case '1':
            Farm(1);
            break;
        case '2':
            Farm(2);
            break;
        case '3':
            Farm(3);
            break;
    }
}

void Farm(int risk) {

    int maxPrize = 0;
    int maxAnswer = 0;

    switch (risk) {
        case 1:
            maxPrize = 50;
            maxAnswer = 7;
            break;
        case 2:
            maxPrize = 15;
            maxAnswer = 4;
            break;
        case 3:
            maxPrize = 5;
            maxAnswer = 2;
            break;
    }

    srand(time(NULL));

    int input;
    int value = rand() % maxPrize + 1;
    int answer = rand() % maxAnswer + 1;
    string temp;

    cout << "Guess a number from 1 - " << maxAnswer << ": ";

    do {
        cin >> input;
    } while (input < 1 || input > maxAnswer);

    if (input == answer || cheater == true) {
        bucks += value;
        cout << "You won " << value << " " << currency;
        if (value > 1)
            cout << "S";
        cout << "." << endl;
    } else {
        bucks -= value;
        cout << "You lost " << value << " " << currency;
        if (value > 1)
            cout << "S";
        cout << ". The answer was " << answer << "." << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(2000));
}

void Bank() {
    ClearScreen();
    cout << "----------------" << endl << endl;
    cout << "      Bank" << endl << endl;
    cout << "----------------" << endl << endl << endl;
    cout << "Banker: You have " << bucks << " " << currency << "S." << endl;

    if (bucks > daniBucks) {
        GameOver("Banker: Congratulations, you are the richest man in Tj Town!\nBucks: " + to_string(bucks));
    } else {
        GameOver("Banker: Sorry, you are the poorest man in Tj Town.\nBucks: " + to_string(bucks));
    }
}

void GameOver(string message) {
    bucks = 0;
    lastRisk = 0;
    riskCount = 0;

    int input = 0;
    ClearScreen();
    cout << message << endl << endl;
    cout << "1. Try again" << endl;
    cout << "2. Exit" << endl;
    cout << "Entry: ";
    do {
        cin >> input;
    } while (input < 1 || input > 2);

    if (input == 2) {
        exit(0);
    }
}
