// FCI – Programming 1 – 2022 - Assignment 4
// Program Name: loginprogram.cpp
// Last Modification Date: 4/5/2022
// Author 1: Nour El-Din Ahmed Hussein - 20210430 - Group A - s5
// Author 2: Mohanad Hisham El-Tahawy - 20210413 - Group A - s5
// Author 3: Nour Omar - 20210434 - Group A - s5
// Teaching Assistant: Hagar Ali
// Purpose: Login program.

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <regex>
#include "login-functions.cpp"

using namespace std;

int main(){
    read();
    char input;
    while(input != '4'){
        input = action(); // Letting the user choose the action he wants to do.
        tries = 0;
        switch (input)
        {
        case '1':
            register_new_user();
            break;
        
        case '2':
            login();
            break;
        
        case '3':
            change_pass();
            break;
        
        case '4':
            cout << "Thanks for using our program. \n";
            break;

        default:
            cout << "Invalid input! \n";
            break;
        }
    }
    return 0;
}

