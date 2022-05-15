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
#include "login.h"

using namespace std;

void read(){
    int id, i = 0;
    string u, p, e, m;
    fstream data_file;
    data_file.open("users_data.txt", ios::in);
    while(!data_file.eof()){
        if (i % 4 == 0){
            id = i/4;
            getline(data_file, u);
        } //making the first line for the user
        else if (i % 4 == 1){
            getline(data_file, p);
        } //making second line for password
        else if (i % 4 == 2){
            getline(data_file, e);
        } //making third line for email
        else if (i % 4 == 3){
            getline(data_file, m);
            users.push_back(user(id, u, decrypt(p), e, m));
        } //making fourth line for mobile
        i++;
    }
    users_count = i / 4; //giving the user an ID
    data_file.close();
}

char action(){
    char input;
    cout << "Please choose one of the following actions: \n"
         << "1 - Register new user. \n"
         << "2 - Login. \n"
         << "3 - Change password. \n"
         << "4 - Exit. \n";
    cin >> input;
    return input;
}

void register_new_user(){
    string u, p, e, m;
    get_user(u);
    get_pass(p);
    get_email(e);
    get_mobile(m);
    users.push_back(user(users_count, u, p, e, m));
    write(users[users_count]);
    cout << "Your account has been created succesfully your id is: " << users_count << endl;
    users_count++;
} //taking from the user all the information to make a new account for him

// void get_name(string& n){
//     cout << "Please enter your name: ";
//     cin.ignore(256, '\n');
//     getline(cin, n);
//     regex valid_name("[a-zA-Z-]+");
//     if (!(regex_match(n,valid_name))){
//         cout << "Please enter a valid name that contains characters and '-' only " << endl;
//         get_name(n);
//     }
// }

void get_user(string& u){
    cout << "Please choose your username: ";
    cin >> u;
    cin.ignore(256, '\n');
    for(int i = 0; i < users_count; i++){
        if(u == users[i].username){
            cout << "This username does already exist, try again.\n";
            get_user(u);
            break;
        } //choosing for the user a name the didn't exist before
    }
    regex valid_name("[a-zA-Z-]+");
    if (!(regex_match(u,valid_name))){
        cout << "Please enter a valid name that contains characters and '-' only " << endl;
        get_user(u);
    } //validation of the name
}

void get_pass(string& p){
    char ch;
    string again;
    cout << "Please choose a password (it has to contain upper case, lower case, digit and special characters): ";
    while((ch = getch()) != RETURN){ //if he presses "Enter" the loop stops"
        if(ch == BACKSPACE){
            if(p.length() != 0){
                cout << "\b \b";
                p.resize(p.length()-1);
            } //if he enters backspace it deletes what last thing was written but first it needs to check that there's a character written
        }
        else{
            p+= ch;
            cout << '*';
        } //the password stores the character and put '*' instead of it on the screen
    }
    if (checklength(p) && checkdigit(p) && checklower(p) && checkupper(p) && checkspecial(p)){
        cout << "\nEnter your password again: ";
        while((ch = getch()) != RETURN){
            if(ch == BACKSPACE){
                if(again.length() != 0){
                    cout << "\b \b";
                    again.resize(again.length()-1);
                }
            }
            else{
                again+= ch;
                cout << '*';
            }
        }
        cout << endl;
        if(p != again){
            cout << "\nPassword does not match, Please try again.\n";
            p = "";
            get_pass(p);
        }
    }
    else{
        cout << "Please try another password\n";
        p = "";
        get_pass(p);
    }
}

void get_email(string& e){
    cout << "\nPlease enter your email: ";
    cin >> e;
    cin.ignore(256, '\n');
    for(int i = 0; i < users_count; i++){
        if(e == users[i].email){
            cout << "This email does already exist, try again.\n";
            get_user(e);
            break;
        }
    }
    regex valid_email("([\\w!#$%&'*+/=?^_`{|}~-]+[\\w!#$%&'.*+/=?^_`{|}~-]*[\\w!#$%&'*+/=?^_`{|}~-]+)@[\\w]+[\\w-]*(\\.[\\w-]+)+[\\w]+");
    if(regex_match(e,valid_email) == true){
        cout << "Succesfull Email !! " << endl;
    } //validation of email
    else{
        cout << "Please enter a valid email ";
        get_email(e);
    }
}

void get_mobile(string& m){
    cout << "Please enter your mobile: ";
    cin >> m;
    regex valid_mobile("[0][1][0|1|2|5][0-9]{8}+");
    if (regex_match(m,valid_mobile) == true)
    {
        cout << "successful phone number";
    }
    else
    {
        cout << "invalid phone number ";
        get_mobile(m);
    }
}

void write(user user1){
    fstream data_file("users_data.txt", ios::app);
    data_file << user1.username << '\n';
    string pass = encrypt(user1.password);
    data_file << pass << '\n';
    data_file << user1.email << '\n';
    data_file << user1.mobile << '\n';
	data_file.close();
} //write function is used while registering new user to write all his info in the file


string encrypt(string p){
    string enc = "";
    for(char c: p){
        int x = c - 'A';
        x = (5 * x + 8) % 26;
        enc+= (char) x + 'A';
    }
    return enc;
} //applying aphine cipher

string decrypt(string p){
    string dec = "";
    for(char c: p){
        int y = c - 'A';
        y = 21 * (y - 8);
        y = ((y % 26) + 26) % 26;
        dec+= (char) y + 'A';
    }
    return p;
} //applying aphine cipher

void login(){
    isLoggedIn = false;
    char ch;
    while(!isLoggedIn){
        string p = "";
        cout << "Please enter your ID: ";
        cin >> ch;
        id = ch - '0'; //turning the characters to integer
        cin.ignore(256, '\n');
        if(id >= users_count){
            cout << "There is no registered user with this ID.\n";
        } //checking if the user entered correct id and didn't exceed the users counter
        else{
            if(check_pass()){
                cout << "Login Succesful\n";
                isLoggedIn = true;
            }
            else{
                break;
            }
        }
    }
}

void change_pass(){
    string p;
    cout << "Please login first.\n";
    login();
    if(isLoggedIn && check_pass()){
        get_pass(p);
        users[id].password = p;
        write_all();
    } //clearing the password from the file and entering new one
}

bool check_pass(){
    char ch;
    string p;
    cout << "Please enter your password: ";
    while((ch = getch()) != RETURN){
        if(ch == BACKSPACE){
            if(p.length() != 0){
                cout << "\b \b";
                p.resize(p.length()-1);
            }
        }
        else{
            p+= ch;
            cout << '*';
        }
    }
    cout << endl;
    if(p == users[id].password){
        return true;
    }
    else{
        cout << "\nIcorrect password please try again.\n";
        tries++;
        if(tries == 3){
            cout << "You are denied to access system\n";
            return false;
        }
        return check_pass();
    }
}

void write_all(){
    fstream data_file("users_data.txt", ios::out);
    for(int i = 0; i < users_count; i++){
        data_file << users[i].username << '\n';
        string pass = encrypt(users[i].password);
        data_file << pass << '\n';
        data_file << users[i].email << '\n';
        data_file << users[i].mobile << '\n';
    }
	data_file.close();
} //writing all the file again with the same info. just changing the password


bool checklength(string p)
{
    bool isLong = p.size() >= 6;
    if(!isLong){
        cout << "Your password has to be at least 6 characters.\n";
    }
    return isLong;
}

bool checkdigit(string p)
{
    int i;
    int len = p.size();
    for (i = 0; i < len - 1; i++)
    {
        if (isdigit(p[i]))
        {
            return true;
        }
    }
    cout << "Your password has to contain at least one digit.\n";
    return false;
}

bool checklower(string p)
{
    int i;
    int len = p.size();
    for (i = 0; i < len - 1; i++)
    {
        if (islower(p[i]))
        {
            return true;
        }
    }
    cout << "Your password has to contain at least one lower case character.\n";
    return false;
}

bool checkupper(string p)
{
    int i;
    int len = p.size();
    for (i = 0; i < len - 1; i++)
    {
        if (islower(p[i]))
        {
            return true;
        }
    }
    cout << "Your password has to contain at least one upper case character.\n";
    return false;
}

bool checkspecial(string p)
{
    regex valid_special("[!@#$%^&*/*-+=]+");
    bool isSpecial = regex_search(p, valid_special);
    if(!isSpecial){
        cout << "Your password has to contain at least one special character.\n";
    }
    return isSpecial;
}