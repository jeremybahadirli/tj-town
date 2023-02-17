#include <iostream>
#include <fstream>
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
void ResetAll();
void ResetUser();
void LoadData();
void SaveData(string name, int quantity);
string Trim(string const& str);

const string currency = "TJ-BUCK";
const string winnerNameDefault = "Daniela";
const int winnerBucksDefault = 29;

string name = "";
int bucks = 0;
bool cheater = false;

string winnerName = "";
int winnerBucks = 0;

int lastRisk = 0;
int riskCount = 0;

int main()
{
    
    LoadData();
    WelcomeScreen();
    
    while (true) {
        MainMenu();
    }
}

void WelcomeScreen()
{
    char input[32];
    string cheatCode = "::TJISLIFE";
    string resetCode = "::RESETDATA";
    
    ClearScreen();
    cout << "---------------------------------------------" << endl;
    cout << "             Tj Town version 1.6.1" << endl;
    cout << "            Last update: 09/01/17" << endl << endl;
    cout << "   Created by Jeremy Bahadirli on 04/14/16" << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl << endl;
    cout << "Welcome to Tj Town!!" << endl << endl;
    cout << "The point of the game is to become the wealthiest man in Tj Town. It will not be" << endl;
    cout << "very difficult because there is only one citizen in the town and his name is . ." << endl;
    cout << "TJJTJTJTJTJTJTJTJTJTJ!!!!!!!!!!!!!!" << endl << endl;
    cout << "Just kidding, there are many people in the town. The wealthiest is " << endl;
    cout << winnerName << " with " << winnerBucks << " " << currency << "S. Good Luck." << endl << endl;
    cout << "You can go to the Farm to earn " << currency << "S, and head to the" << endl;
    cout << "Bank to cash in and inevitably lose." << endl << endl;
    cout << "Enter your name to begin: ";
    
    bool loop = true;
    while (loop == true) {
        cin.getline(input, sizeof(input));
        name = Trim(input);
        if (name.length() >= 2) {
            loop = false;
        }
    }
    
    if (name == cheatCode) {
        cheater = true;
        name = "Tj";
    } else if (name == resetCode) {
        SaveData(winnerNameDefault, winnerBucksDefault);
        exit(0);
    }
}

void ClearScreen()
{
    for (int i = 0; i < 50; i++) {
        cout << endl;
    }
}

void MainMenu()
{
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

void FarmMenu()
{
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

void Farm(int risk)
{
    
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

void Bank()
{
    ClearScreen();
    cout << "----------------" << endl << endl;
    cout << "      Bank" << endl << endl;
    cout << "----------------" << endl << endl << endl;
    cout << "Banker: You have " << bucks << " " << currency << "S." << endl;
    
    if (bucks > winnerBucks) {
        cout << "Congratulations! " << name << " is the richest man in Tj Town!";
        if (cheater == false) {
            SaveData(name, bucks);
        }
    } else {
        cout << "Sorry, " << name << " is the poorest man in Tj Town.";
    }
    cout << endl << endl;
    cout << "1. Try again (same user)" << endl;
    cout << "2. Return to Welcome Screen" << endl;
    cout << "3. Exit" << endl;
    cout << "Entry: ";
    char input = ' ';
    do {
        cin >> input;
    } while ((int) input < 49 || (int) input > 51);
    
    switch (input) {
        case '1':
            ResetUser();
            break;
        case '2':
            ResetAll();
            WelcomeScreen();
            break;
        case '3':
            exit(0);
    }
}

void ResetAll()
{
    ResetUser();
    name = "";
}

void ResetUser() {
    bucks = 0;
    int lastRisk = 0;
    int riskCount = 0;
}

void LoadData() {
    ifstream nameFile ("SaveData/Name.txt");
    getline(nameFile, winnerName);
    nameFile.close();
    
    ifstream buckFile ("SaveData/Quantity.txt");
    buckFile >> winnerBucks;
    buckFile.close();
}

void SaveData(string name, int quantity) {
    ofstream nameFile ("SaveData/Name.txt");
    nameFile << name;
    nameFile.close();
    
    ofstream buckFile ("SaveData/Quantity.txt");
    buckFile << quantity;
    buckFile.close();
}

string Trim(string const& str)
{
    if(str.empty()){
        return str;
    }
    
    size_t firstScan = str.find_first_not_of(' ');
    size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}
