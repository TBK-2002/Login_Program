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

using namespace std;

struct user
{
    int id;
    string name, username, password, email, mobile;
    user(int i, string u = " ", string p = " ", string e = " ", string m = " "){
        id = i;
        username = u;
        password = p;
        email = e;
        mobile = m;
    }
};

void read(), write(user user1), get_user(string& u), get_pass(string& p), get_email(string& e), get_mobile(string& m), register_new_user(), login(), change_pass(), write_all();
char action();
bool check_pass();
string encrypt(string p), decrypt(string p);
bool checklength(string p);
bool checkdigit(string p);
bool checklower(string p);
bool checkupper(string p);
bool checkspecial(string p);

int users_count, id, tries;
bool isLoggedIn = false;
vector<user> users;
const char BACKSPACE = 127;
const char RETURN = 10;